%{
extern int yylex (void);
void yyerror(char *s);
#include <string.h>
#include <stdio.h>
#include <glib.h>
#include "sql.h"
int strreplace(char * str, const char * source, const char * dest, int max);
%}

%union {
	int intval;
	double floatval;
	char strval[256];
	char charval;
	int subtok;
}
	
%token <strval> NAME
%token <strval> STRING
%token <floatval> INTNUM

	/* operators */

%left OR
%left AND
%left NOT
%left <intval> COMPARISON /* == <> < > <= >= */
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

	/* literal keyword tokens */

%token ADD ALTER ASC BY BLOCK_SIZE
%token CHARACTER COLUMN COMMIT CREATE
%token DATABASE DELETE DESC DOUBLE DROP
%token FOREIGN FROM
%token GROUP INDICATOR INSERT INTEGER INTO
%token KEY LANGUAGE NULLX
%token ORDER PRIMARY PROCEDURE
%token PUBLIC REFERENCES RENAME ROLLBACK SELECT SET
%token SQLCODE TABLE TO
%token UNIQUE UPDATE USE VALUES WHERE WORK

%type <charval> '+' '-' '*' '/' '(' ')'
%type <strval> database_name table_name column column_ref data_type
%type <strval> search_condition scalar_exp atom	literal	select_exp
%type <strval> column_def_opt
%%

sql_list:
		sql ';'	 
	|	sql_list sql ';' 
	;

sql:	
		USE database_name								{ cur_sql->type = SQL_USE_DB; }
	|	CREATE DATABASE database_name block_size_def	{ cur_sql->type = SQL_CREATE_DB; }
	|	DROP DATABASE database_name						{ cur_sql->type = SQL_DROP_DB; }
	|	DROP TABLE table_name							{ g_ptr_array_add(cur_sql->table_set, strdup($3));
															cur_sql->type = SQL_DROP_TB; }
	|	ALTER TABLE table_name alter_operation			{ g_ptr_array_add(cur_sql->table_set, strdup($3)); }
	|	base_table_def									{ cur_sql->type = SQL_CREATE_TB; }
	;
	
database_name:
	    NAME					{ g_ptr_array_add(cur_sql->database_set, strdup($1)); }
	;

alter_operation:
		ADD column data_type
	|	DROP COLUMN column
	|	ALTER COLUMN column data_type
	|	RENAME TO table_name							{ cur_sql->type = SQL_RENAME_TB;
															g_ptr_array_add(cur_sql->value_set, strdup($3)); }
	|	RENAME column TO column							{ cur_sql->type = SQL_RENAME_COL;
															g_ptr_array_add(cur_sql->value_set, strdup($2));
															g_ptr_array_add(cur_sql->value_set, strdup($4)); }
	;
	
	/* 创建表 */
base_table_def:
		CREATE TABLE table_name '(' base_table_element_commalist ')' {
			g_ptr_array_add(cur_sql->table_set, strdup($3));
			cur_sql->column_set = cur_sql->cur_col_set;
			cur_sql->cur_col_set = NULL;
		}
	;
	
block_size_def:
		/* empty */
	| 	BLOCK_SIZE '=' INTNUM	{ char tmp[1024]; sprintf(tmp, "%d", $3);
									g_ptr_array_add(cur_sql->value_set, strdup(tmp)); }
	;

base_table_element_commalist:
		column_def
	|	base_table_element_commalist ',' column_def
	;
	
    /* 字段定义 */
column_def:
		column data_type column_def_opt_list {
			cur_sql->col_def_set[cur_sql->cur_col_set->len] = cur_sql->cur_col_def;

			cur_sql->cur_col_def = g_ptr_array_sized_new(4);
			g_ptr_array_set_free_func(cur_sql->cur_col_def, myg_char_strdup_destroy);

			g_ptr_array_add(cur_sql->cur_col_set, strdup($1));
			g_ptr_array_add(cur_sql->col_data_def, strdup($2));
		}
	;

column_def_opt_list:
		/* empty */
	|	column_def_opt_list column_def_opt			{ g_ptr_array_add(cur_sql->cur_col_def, strdup($2)); }
	;

column_def_opt:
		NOT NULLX									{ sprintf($$, "NOTNULL"); }			
	|	UNIQUE										{ sprintf($$, "UNIQUE"); }
	|	PRIMARY KEY									{ sprintf($$, "PRIMARYKEY"); }
	|	FOREIGN KEY REFERENCES NAME '(' column ')'	{ sprintf($$, "FOREIGNKEY %s.%s", $4, $6); }
	;


column_commalist:
		column										{ g_ptr_array_add(cur_sql->cur_col_set, strdup($1)); }
	|	column_commalist ',' column					{ g_ptr_array_add(cur_sql->cur_col_set, strdup($3)); }
	;

opt_column_commalist:
		/* empty */
	|	'(' column_commalist ')'
	;
	
opt_order_by_clause:
		/* empty */
	|	ORDER BY column_ref opt_asc_desc
	;

opt_asc_desc:
		/* empty */
	|	ASC
	|	DESC
	;

	/* 操作语句 */
sql:	manipulative_statement
	;

manipulative_statement:
		commit_statement
	|	delete_statement_searched					{ cur_sql->type = SQL_DELETE; }
	|	insert_statement							{ cur_sql->type = SQL_INSERT; }
	|	rollback_statement
	|	select_statement							{ cur_sql->type = SQL_SELECT; }
	|	update_statement_searched					{ cur_sql->type = SQL_UPDATE; }
	;

commit_statement:
		COMMIT WORK
	;

delete_statement_searched:
		DELETE FROM table_name opt_where_clause		 { g_ptr_array_add(cur_sql->table_set, strdup($3)); }
	;

insert_statement:
		INSERT INTO table_name opt_column_commalist values_or_query_spec {
			g_ptr_array_add(cur_sql->table_set, strdup($3));
			cur_sql->column_set = cur_sql->cur_col_set;
			cur_sql->cur_col_set = g_ptr_array_sized_new(8);
			g_ptr_array_set_free_func(cur_sql->cur_col_set, myg_char_strdup_destroy);
		}
	;

values_or_query_spec:
		VALUES '(' insert_atom_commalist ')'
	;

insert_atom_commalist:
		insert_atom
	|	insert_atom_commalist ',' insert_atom
	;

insert_atom:
		atom								{ g_ptr_array_add(cur_sql->value_set, strdup($1)); }		
	|	NULLX								{ g_ptr_array_add(cur_sql->value_set, NULL); }
	;

rollback_statement:
		ROLLBACK WORK
	;

select_statement:
		SELECT selection table_exp
	;

assignment_commalist:
		assignment
	|	assignment_commalist ',' assignment
	;

assignment:
		column '=' scalar_exp  {
			//update语句列引用和scalar_exp中的列引用同时规约，不能使用cur_col_set
			if(cur_sql->column_set == NULL) {
				cur_sql->column_set = g_ptr_array_sized_new(2);
				g_ptr_array_set_free_func(cur_sql->column_set, myg_char_strdup_destroy);
			}
			g_ptr_array_add(cur_sql->column_set, strdup($1));
			cur_sql->exp_refcol_set[cur_sql->expression_set->len] = cur_sql->cur_col_set;

			struct expression * exp;
			exp = expression_new_instance($3);
			g_ptr_array_add(cur_sql->expression_set, exp);

			cur_sql->cur_col_set = g_ptr_array_sized_new(2);
			g_ptr_array_set_free_func(cur_sql->cur_col_set, myg_char_strdup_destroy);
		}
	|	column '=' NULLX {
			if(cur_sql->column_set == NULL) {
				cur_sql->column_set = g_ptr_array_sized_new(2);
				g_ptr_array_set_free_func(cur_sql->column_set, myg_char_strdup_destroy);
			}
			g_ptr_array_add(cur_sql->column_set, strdup($1));
			cur_sql->exp_refcol_set[cur_sql->expression_set->len] = NULL;
			g_ptr_array_add(cur_sql->expression_set, NULL);
		} 
	;

update_statement_searched:
		UPDATE table_name SET assignment_commalist opt_where_clause {
			g_ptr_array_add(cur_sql->table_set, strdup($2));
		}
	;

opt_where_clause:
		/* empty */
	|	where_clause
	;

selection:
		select_exp_commalist {
			cur_sql->column_set = cur_sql->cur_col_set;
			cur_sql->cur_col_set = g_ptr_array_sized_new(8);
			g_ptr_array_set_free_func(cur_sql->cur_col_set, myg_char_strdup_destroy);
		}
	|	'*'	{
			g_ptr_array_add(cur_sql->cur_col_set, strdup("*")); 
			cur_sql->column_set = cur_sql->cur_col_set;
			cur_sql->cur_col_set = g_ptr_array_sized_new(8);
			g_ptr_array_set_free_func(cur_sql->cur_col_set, myg_char_strdup_destroy);
		}
	;

table_exp:
		from_clause
		opt_where_clause
		opt_group_by_clause
		opt_order_by_clause
	;

from_clause:
		FROM table_ref_commalist
	;

table_ref_commalist:
		table_name								{ g_ptr_array_add(cur_sql->table_set, strdup($1)); }
	|	table_ref_commalist ',' table_name		{ g_ptr_array_add(cur_sql->table_set, strdup($3)); }
	;

where_clause:
		WHERE search_condition					{ strcpy(cur_sql->cond_formula, $2); }
	;

opt_group_by_clause:
		/* empty */
	|	GROUP BY column_ref_commalist
	;

column_ref_commalist:
		column_ref
	|	column_ref_commalist ',' column_ref
	;

	/* 查询条件 */
search_condition:
		search_condition OR search_condition	{ sprintf($$, "%s+%s", $1, $3); }
	|	search_condition AND search_condition	{ sprintf($$, "%s*%s", $1, $3); }
	|	NOT search_condition					{ sprintf($$, "~%s", $2); }
	|	'(' search_condition ')'				{ sprintf($$, "(%s)", $2); }
	|	predicate								{ sprintf($$, "c"); }
	;
	
    /* 断言，谓语 */
predicate:
		comparison_predicate
	;
	
    /* 比较谓语 */
comparison_predicate:
		scalar_exp COMPARISON scalar_exp {
			cur_sql->cond_refcol_set[cur_sql->condition_set->len] = cur_sql->cur_col_set;

			struct condition * cond;
			cond = condition_new_instance($2, $1, $3);
			g_ptr_array_add(cur_sql->condition_set, cond);

			cur_sql->cur_col_set = g_ptr_array_sized_new(8);
			g_ptr_array_set_free_func(cur_sql->cur_col_set, myg_char_strdup_destroy);
		}
	;

	/* 标量表达式 */
scalar_exp:
		scalar_exp '+' scalar_exp			{ sprintf($$, "%s+%s", $1, $3); }
	|	scalar_exp '-' scalar_exp 			{ sprintf($$, "%s-%s", $1, $3); }
	|	scalar_exp '*' scalar_exp 			{ sprintf($$, "%s*%s", $1, $3); }
	|	scalar_exp '/' scalar_exp 			{ sprintf($$, "%s/%s", $1, $3); }
	|	atom								{ sprintf($$, "%s", $1); }
	|	column_ref							{ sprintf($$, "%s", $1); g_ptr_array_add(cur_sql->cur_col_set, strdup($1)); }
	|	'(' scalar_exp ')'					{ sprintf($$, "(%s)", $2); }
	;

select_exp_commalist:
		select_exp							
	|	select_exp_commalist ',' select_exp
	;

select_exp:	
		column_ref							{ g_ptr_array_add(cur_sql->cur_col_set, strdup($1)); }
	;
	
atom:
		literal								{ sprintf($$,"%s", $1); }
	;

literal:
		STRING								{ sprintf($$, "%s", $1); strreplace($$, "'", "", 256); }
	|	INTNUM								{ sprintf($$, "%lf", $1); }
	;

	/* miscellaneous */

table_name:
		NAME								{ sprintf($$, "%s", $1); }
	|	NAME '.' NAME						{ sprintf($$, "%s.%s", $1, $3); }
	;

column_ref:
		NAME								{ sprintf($$, "%s", $1); }
	|	NAME '.' NAME						{ sprintf($$, "%s.%s", $1, $3); }
	;

	/* 数据类型 支持INT DOUBLE CHAR三种*/
data_type:
		CHARACTER '(' INTNUM ')'			{ sprintf($$, "%lf", $3); }
	|	INTEGER								{ sprintf($$, "-1"); }
	|	DOUBLE								{ sprintf($$, "-2"); }
	;

	/* the various things you can name */

column:		
		NAME								{ sprintf($$, "%s", $1); }
	;
%%
