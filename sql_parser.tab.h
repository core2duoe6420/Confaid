
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
/* Put the tokens into the symbol table, so that GDB and other debuggers
   know about them.  */
enum yytokentype {
    NAME = 258,
    STRING = 259,
    INTNUM = 260,
    OR = 261,
    AND = 262,
    NOT = 263,
    COMPARISON = 264,
    UMINUS = 265,
    ADD = 266,
    ALTER = 267,
    ASC = 268,
    BY = 269,
    BLOCK_SIZE = 270,
    CHARACTER = 271,
    COLUMN = 272,
    COMMIT = 273,
    CREATE = 274,
    DATABASE = 275,
    DELETE = 276,
    DESC = 277,
    DOUBLE = 278,
    DROP = 279,
    FOREIGN = 280,
    FROM = 281,
    GROUP = 282,
    INDICATOR = 283,
    INSERT = 284,
    INTEGER = 285,
    INTO = 286,
    KEY = 287,
    LANGUAGE = 288,
    NULLX = 289,
    ORDER = 290,
    PRIMARY = 291,
    PROCEDURE = 292,
    PUBLIC = 293,
    REFERENCES = 294,
    RENAME = 295,
    ROLLBACK = 296,
    SELECT = 297,
    SET = 298,
    SQLCODE = 299,
    TABLE = 300,
    TO = 301,
    UNIQUE = 302,
    UPDATE = 303,
    USE = 304,
    VALUES = 305,
    WHERE = 306,
    WORK = 307
};
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE {

    /* Line 1676 of yacc.c  */
#line 11 "sql_parser.y"

    int intval;
    double floatval;
    char strval[256];
    char charval;
    int subtok;



    /* Line 1676 of yacc.c  */
#line 114 "sql_parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


