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
%type <strval> database_name table_name column column_ref
%type <strval> search_condition scalar_exp atom	literal	select_exp
%%

sql_list:
		sql ';'	 
	|	sql_list sql ';' 
	;

sql:	
		USE database_name 
	|	CREATE DATABASE database_name
	|	DROP DATABASE database_name
	|	DROP TABLE table_name
	|	ALTER TABLE table_name alter_operation
	|	base_table_def
	;
	
database_name:
	    NAME 
	;

alter_operation:
		ADD column data_type
	|	DROP COLUMN column
	|	ALTER COLUMN column data_type
	|	RENAME TO table_name
	|	RENAME column TO column
	;
	
	/* 创建表 */
base_table_def:
		CREATE TABLE table_name block_size_def '(' base_table_element_commalist ')'
	;
	
block_size_def:
		/* empty */
	| 	BLOCK_SIZE '=' INTNUM 
	;

base_table_element_commalist:
		base_table_element
	|	base_table_element_commalist ',' base_table_element
	;

base_table_element:
		column_def
	|	table_constraint_def
	;
	
    /* 字段定义 */
column_def:
		column data_type column_def_opt_list
	;

column_def_opt_list:
		/* empty */
	|	column_def_opt_list column_def_opt
	;

column_def_opt:
		NOT NULLX
	|	NOT NULLX UNIQUE
	|	NOT NULLX PRIMARY KEY
	;

table_constraint_def:
		UNIQUE '(' column_commalist ')'
	|	PRIMARY KEY '(' column_commalist ')'
	|	FOREIGN KEY '(' column_commalist ')'
			REFERENCES table_name '(' column_commalist ')'
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
		CHARACTER
	|	CHARACTER '(' INTNUM ')'
	|	INTEGER
	|	DOUBLE
	;

	/* the various things you can name */

column:		
		NAME								{ sprintf($$, "%s", $1); }
	;
%%
