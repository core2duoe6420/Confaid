%{

#ifndef __LINUX__

#pragma comment(lib, "yld.lib")
#pragma comment(lib, "ylmtd.lib")
#define YY_NO_UNISTD_H
#include <io.h>

#endif


#include "sql.h"

#include "sql_parser.tab.h"
#include <string.h>
#include <math.h>

int lineno = 1;
void yyerror(char *s);

	/* macro to save the text and return a token */
#define TOK(id_name) { return id_name; }
%}
%s SQL
%%

	/* literal keyword tokens */

<SQL>ADD		TOK(ADD)
<SQL>ALTER		TOK(ALTER)
<SQL>AND		TOK(AND)
<SQL>ASC		TOK(ASC)
<SQL>BY			TOK(BY)
<SQL>BLOCK_SIZE		TOK(BLOCK_SIZE)
<SQL>CHAR(ACTER)?	TOK(CHARACTER)
<SQL>COLUMN		TOK(COLUMN)
<SQL>COMMIT		TOK(COMMIT)
<SQL>CREATE		TOK(CREATE)
<SQL>DATABASE		TOK(DATABASE)
<SQL>DELETE		TOK(DELETE)
<SQL>DESC		TOK(DESC)
<SQL>DOUBLE		TOK(DOUBLE)
<SQL>DROP		TOK(DROP)
<SQL>FOREIGN		TOK(FOREIGN)
<SQL>FROM		TOK(FROM)
<SQL>GROUP		TOK(GROUP)
<SQL>INDICATOR		TOK(INDICATOR)
<SQL>INSERT		TOK(INSERT)
<SQL>INT(EGER)?		TOK(INTEGER)
<SQL>INTO		TOK(INTO)
<SQL>KEY		TOK(KEY)
<SQL>LANGUAGE		TOK(LANGUAGE)
<SQL>NOT		TOK(NOT)
<SQL>NULL		TOK(NULLX)
<SQL>OR			TOK(OR)
<SQL>ORDER		TOK(ORDER)
<SQL>PRIMARY		TOK(PRIMARY)
<SQL>PROCEDURE		TOK(PROCEDURE)
<SQL>PUBLIC		TOK(PUBLIC)
<SQL>REFERENCES		TOK(REFERENCES)
<SQL>RENAME		TOK(RENAME)
<SQL>ROLLBACK		TOK(ROLLBACK)
<SQL>SELECT		TOK(SELECT)
<SQL>SET		TOK(SET)
<SQL>SQLCODE		TOK(SQLCODE)
<SQL>TABLE		TOK(TABLE)
<SQL>TO			TOK(TO)
<SQL>UNIQUE		TOK(UNIQUE)
<SQL>UPDATE		TOK(UPDATE)
<SQL>USE		TOK(USE)
<SQL>VALUES		TOK(VALUES)
<SQL>WHERE		TOK(WHERE)
<SQL>WORK		TOK(WORK)

	/* punctuation */

<SQL>"==" 	{ yylval.intval = 1; TOK(COMPARISON); }
<SQL>"<>" 	{ yylval.intval = 6; TOK(COMPARISON); }
<SQL>"<"	{ yylval.intval = 4; TOK(COMPARISON); }
<SQL>">"	{ yylval.intval = 2; TOK(COMPARISON); }
<SQL>"<="	{ yylval.intval = 5; TOK(COMPARISON); }
<SQL>">="	{ yylval.intval = 3; TOK(COMPARISON); }

<SQL>[-+*/=(),.;]	{ yylval.charval = yytext[0]; TOK(yytext[0]); } 

	/* names */
<SQL>[A-Za-z][A-Za-z0-9_]*	{ strcpy(yylval.strval, yytext); TOK(NAME); }

	/* numbers */

<SQL>[-+]?[0-9]+	|
<SQL>[-+]?[0-9]+"."[0-9]* |
<SQL>"."[0-9]*		{ yylval.floatval = atof(yytext); TOK(INTNUM); }

	/* strings */

<SQL>\'[^'\n]*'	 { strcpy(yylval.strval, yytext); TOK(STRING); }
		
<SQL>'[^'\n]*$	{ yyerror("Unterminated string"); }

<SQL>\n		{ lineno++; }
\n		{ lineno++; ECHO; }

<SQL>[ \t\r]+	;	/* white space */

<SQL>"--".*	;	/* comment */

.		ECHO;	/* random non-SQL text */
%%

void yyerror(char *s)
{
	int n = 0;
	n = sprintf(cur_sql->info + cur_sql->info_offset, "%d: %s at %s\n", lineno, s, yytext);
	cur_sql->info_offset += n;
}

void un_sql()
{
	BEGIN INITIAL;
}

void start_sql()
{
	BEGIN SQL;
}