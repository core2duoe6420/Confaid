
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "sql_parser.y"

extern int yylex(void);
void yyerror(char *s);
#include <string.h>
#include <stdio.h>
#include <glib.h>
#include "sql.h"
int strreplace(char * str, const char * source, const char * dest, int max);


/* Line 189 of yacc.c  */
#line 84 "sql_parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

    /* Line 214 of yacc.c  */
#line 11 "sql_parser.y"

    int intval;
    double floatval;
    char strval[256];
    char charval;
    int subtok;



    /* Line 214 of yacc.c  */
#line 182 "sql_parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 194 "sql_parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID(int yyi)
#else
static int
YYID(yyi)
int yyi;
#endif
{
    return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
/* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
/* The OS might guarantee only one guard page at the bottom of the stack,
   and a page size can be as small as 4096 bytes.  So we cannot safely
   invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
   to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc(YYSIZE_T);  /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free(void *);  /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc {
    yytype_int16 yyss_alloc;
    YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  40
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   189

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNRULES -- Number of states.  */
#define YYNSTATES  191

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] = {
    0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    57,    58,    12,    10,    61,    11,    62,    13,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,    59,
    2,    60,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
    5,     6,     7,     8,     9,    14,    15,    16,    17,    18,
    19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
    29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
    39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
    49,    50,    51,    52,    53,    54,    55,    56
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] = {
    0,     0,     3,     6,    10,    13,    18,    22,    26,    31,
    33,    35,    39,    43,    48,    52,    57,    64,    65,    69,
    71,    75,    79,    80,    83,    86,    88,    91,    99,   101,
    105,   106,   110,   111,   116,   117,   119,   121,   123,   125,
    127,   129,   131,   133,   135,   138,   143,   149,   154,   156,
    160,   162,   164,   167,   171,   173,   177,   181,   185,   191,
    192,   194,   196,   198,   203,   206,   208,   212,   215,   216,
    220,   222,   226,   230,   234,   237,   241,   243,   245,   249,
    253,   257,   261,   265,   267,   269,   273,   275,   279,   281,
    283,   285,   287,   289,   293,   295,   299,   304,   306,   308
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] = {
    64,     0,    -1,    65,    59,    -1,    64,    65,    59,    -1,
    53,    66,    -1,    23,    24,    66,    69,    -1,    28,    24,
    66,    -1,    28,    49,   106,    -1,    16,    49,   106,    67,
    -1,    68,    -1,     3,    -1,    15,   109,   108,    -1,    28,
    21,   109,    -1,    16,    21,   109,   108,    -1,    44,    50,
    106,    -1,    44,   109,    50,   109,    -1,    23,    49,   106,
    57,    70,    58,    -1,    -1,    19,    60,     5,    -1,    71,
    -1,    70,    61,    71,    -1,   109,   108,    72,    -1,    -1,
    72,    73,    -1,     8,    38,    -1,    51,    -1,    40,    36,
    -1,    29,    36,    43,     3,    57,   109,    58,    -1,   109,
    -1,    74,    61,   109,    -1,    -1,    57,    74,    58,    -1,
    -1,    39,    18,   107,    77,    -1,    -1,    17,    -1,    26,
    -1,    78,    -1,    79,    -1,    80,    -1,    81,    -1,    85,
    -1,    86,    -1,    89,    -1,    22,    56,    -1,    25,    30,
    106,    90,    -1,    33,    35,   106,    75,    82,    -1,    54,
    57,    83,    58,    -1,    84,    -1,    83,    61,    84,    -1,
    104,    -1,    38,    -1,    45,    56,    -1,    46,    91,    92,
    -1,    88,    -1,    87,    61,    88,    -1,   109,    60,   101,
    -1,   109,    60,    38,    -1,    52,   106,    47,    87,    90,
    -1,    -1,    95,    -1,   102,    -1,    12,    -1,    93,    90,
    96,    76,    -1,    30,    94,    -1,   106,    -1,    94,    61,
    106,    -1,    55,    98,    -1,    -1,    31,    18,    97,    -1,
    107,    -1,    97,    61,   107,    -1,    98,     6,    98,    -1,
    98,     7,    98,    -1,     8,    98,    -1,    57,    98,    58,
    -1,    99,    -1,   100,    -1,   101,     9,   101,    -1,   101,
    10,   101,    -1,   101,    11,   101,    -1,   101,    12,   101,
    -1,   101,    13,   101,    -1,   104,    -1,   107,    -1,    57,
    101,    58,    -1,   103,    -1,   102,    61,   103,    -1,   107,
    -1,   105,    -1,     4,    -1,     5,    -1,     3,    -1,     3,
    62,     3,    -1,     3,    -1,     3,    62,     3,    -1,    20,
    57,     5,    58,    -1,    34,    -1,    27,    -1,     3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] = {
    0,    53,    53,    54,    58,    59,    60,    61,    62,    63,
    67,    71,    72,    73,    74,    75,    80,    87,    89,    94,
    95,   100,   111,   113,   117,   118,   119,   120,   125,   126,
    129,   131,   134,   136,   139,   141,   142,   146,   150,   151,
    152,   153,   154,   155,   159,   163,   167,   176,   180,   181,
    185,   186,   190,   194,   198,   199,   203,   219,   231,   236,
    238,   242,   247,   256,   263,   267,   268,   272,   275,   277,
    281,   282,   287,   288,   289,   290,   291,   296,   301,   315,
    316,   317,   318,   319,   320,   321,   325,   326,   330,   334,
    338,   339,   345,   346,   350,   351,   356,   357,   358,   364
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] = {
    "$end", "error", "$undefined", "NAME", "STRING", "INTNUM", "OR", "AND",
    "NOT", "COMPARISON", "'+'", "'-'", "'*'", "'/'", "UMINUS", "ADD",
    "ALTER", "ASC", "BY", "BLOCK_SIZE", "CHARACTER", "COLUMN", "COMMIT",
    "CREATE", "DATABASE", "DELETE", "DESC", "DOUBLE", "DROP", "FOREIGN",
    "FROM", "GROUP", "INDICATOR", "INSERT", "INTEGER", "INTO", "KEY",
    "LANGUAGE", "NULLX", "ORDER", "PRIMARY", "PROCEDURE", "PUBLIC",
    "REFERENCES", "RENAME", "ROLLBACK", "SELECT", "SET", "SQLCODE", "TABLE",
    "TO", "UNIQUE", "UPDATE", "USE", "VALUES", "WHERE", "WORK", "'('", "')'",
    "';'", "'='", "','", "'.'", "$accept", "sql_list", "sql",
    "database_name", "alter_operation", "base_table_def", "block_size_def",
    "base_table_element_commalist", "column_def", "column_def_opt_list",
    "column_def_opt", "column_commalist", "opt_column_commalist",
    "opt_order_by_clause", "opt_asc_desc", "manipulative_statement",
    "commit_statement", "delete_statement_searched", "insert_statement",
    "values_or_query_spec", "insert_atom_commalist", "insert_atom",
    "rollback_statement", "select_statement", "assignment_commalist",
    "assignment", "update_statement_searched", "opt_where_clause",
    "selection", "table_exp", "from_clause", "table_ref_commalist",
    "where_clause", "opt_group_by_clause", "column_ref_commalist",
    "search_condition", "predicate", "comparison_predicate", "scalar_exp",
    "select_exp_commalist", "select_exp", "atom", "literal", "table_name",
    "column_ref", "data_type", "column", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] = {
    0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
    43,    45,    42,    47,   265,   266,   267,   268,   269,   270,
    271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
    281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
    291,   292,   293,   294,   295,   296,   297,   298,   299,   300,
    301,   302,   303,   304,   305,   306,   307,    40,    41,    59,
    61,    44,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] = {
    0,    63,    64,    64,    65,    65,    65,    65,    65,    65,
    66,    67,    67,    67,    67,    67,    68,    69,    69,    70,
    70,    71,    72,    72,    73,    73,    73,    73,    74,    74,
    75,    75,    76,    76,    77,    77,    77,    65,    78,    78,
    78,    78,    78,    78,    79,    80,    81,    82,    83,    83,
    84,    84,    85,    86,    87,    87,    88,    88,    89,    90,
    90,    91,    91,    92,    93,    94,    94,    95,    96,    96,
    97,    97,    98,    98,    98,    98,    98,    99,   100,   101,
    101,   101,   101,   101,   101,   101,   102,   102,   103,   104,
    105,   105,   106,   106,   107,   107,   108,   108,   108,   109
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] = {
    0,     2,     2,     3,     2,     4,     3,     3,     4,     1,
    1,     3,     3,     4,     3,     4,     6,     0,     3,     1,
    3,     3,     0,     2,     2,     1,     2,     7,     1,     3,
    0,     3,     0,     4,     0,     1,     1,     1,     1,     1,
    1,     1,     1,     1,     2,     4,     5,     4,     1,     3,
    1,     1,     2,     3,     1,     3,     3,     3,     5,     0,
    1,     1,     1,     4,     2,     1,     3,     2,     0,     3,
    1,     3,     3,     3,     2,     3,     1,     1,     3,     3,
    3,     3,     3,     1,     1,     3,     1,     3,     1,     1,
    1,     1,     1,     3,     1,     3,     4,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] = {
    0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    0,     0,     0,     9,    37,    38,    39,    40,    41,    42,
    43,     0,    44,     0,     0,     0,     0,     0,     0,    52,
    94,    62,     0,    61,    86,    88,    92,     0,    10,     4,
    1,     0,     2,     0,    17,     0,    59,     6,     7,    30,
    0,     0,    53,    59,     0,     0,     0,     3,     0,     0,
    0,     0,     8,     0,     5,     0,     0,    45,    60,     0,
    0,    95,    64,    65,    68,    87,    93,    99,    59,    54,
    0,     0,     0,     0,     0,     0,     0,     0,    19,     0,
    90,    91,     0,     0,    67,    76,    77,     0,    83,    89,
    84,     0,    28,     0,    46,     0,     0,    32,     0,    58,
    0,     0,    98,    97,    11,     0,    12,    14,     0,    18,
    16,     0,    22,    74,     0,     0,     0,     0,     0,     0,
    0,     0,     0,    31,     0,     0,    66,     0,     0,    63,
    55,    57,     0,    56,     0,    13,    15,    20,    21,    75,
    85,    72,    73,    78,    79,    80,    81,    82,    29,    51,
    0,    48,    50,    69,    70,     0,     0,     0,     0,     0,
    0,    25,    23,    47,     0,     0,    34,    96,    24,     0,
    26,    49,    71,    35,    36,    33,     0,     0,     0,     0,
    27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] = {
    -1,    11,    12,    39,    62,    13,    64,    87,    88,   148,
    172,   101,    70,   139,   185,    14,    15,    16,    17,   104,
    160,   161,    18,    19,    78,    79,    20,    67,    32,    52,
    53,    72,    68,   107,   163,    94,    95,    96,    97,    33,
    34,    98,    99,    37,   100,   114,    80
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -131
static const yytype_int16 yypact[] = {
    82,   -47,    -9,     7,    38,    54,    66,    52,    33,   109,
    110,    37,    67,  -131,  -131,  -131,  -131,  -131,  -131,  -131,
    -131,   109,  -131,   110,   109,   109,   110,   109,   109,  -131,
    13,  -131,   102,    84,  -131,  -131,    86,    99,  -131,  -131,
    -131,    88,  -131,    56,   130,    93,    96,  -131,  -131,    95,
    150,   109,  -131,    96,   151,   152,   153,  -131,   153,   137,
    138,     8,  -131,   100,  -131,   153,    10,  -131,  -131,   153,
    107,  -131,   101,  -131,   132,  -131,  -131,  -131,   -23,  -131,
    104,    89,   153,   153,   109,   115,   161,    60,  -131,    89,
    -131,  -131,    10,    10,    28,  -131,  -131,   127,  -131,  -131,
    -131,    64,  -131,   111,  -131,   109,   154,   134,   153,  -131,
    16,   112,  -131,  -131,  -131,    89,  -131,  -131,   153,  -131,
    -131,   153,  -131,  -131,    21,    30,    10,    10,    19,    19,
    19,    19,    19,  -131,   153,    25,  -131,   151,   156,  -131,
    -131,  -131,    19,   131,   165,  -131,  -131,  -131,    40,  -131,
    -131,   164,  -131,   131,     4,     4,  -131,  -131,  -131,  -131,
    72,  -131,  -131,   114,  -131,   151,    39,   118,   139,   142,
    143,  -131,  -131,  -131,    25,   151,    85,  -131,  -131,   140,
    -131,  -131,  -131,  -131,  -131,  -131,   177,   124,   153,   126,
    -131
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] = {
    -131,  -131,   171,    91,  -131,  -131,  -131,  -131,    65,  -131,
    -131,  -131,  -131,  -131,  -131,  -131,  -131,  -131,  -131,  -131,
    -131,    11,  -131,  -131,  -131,    79,  -131,    46,  -131,  -131,
    -131,  -131,  -131,  -131,  -131,    -7,  -131,  -131,   -36,  -131,
    135,  -130,  -131,   -18,    -8,   -34,   -57
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] = {
    35,    81,    21,    43,    85,   162,    45,    46,    89,    48,
    49,    77,   102,    30,    90,    91,   131,   132,    92,    30,
    90,    91,    30,    90,    91,   115,   116,   126,   127,    90,
    91,    23,    66,    73,   126,   127,    30,    40,   108,   128,
    129,   130,   131,   132,   162,    31,    35,    22,   168,   129,
    130,   131,   132,     1,   141,   122,    24,   125,    84,     2,
    3,   146,     4,   159,    89,     5,   117,    93,    25,   169,
    6,    58,    59,   142,   143,    50,   142,   158,    26,   149,
    170,   145,     7,     8,    60,   123,   124,   136,   150,     9,
    10,   171,   153,   154,   155,   156,   157,   150,     1,    74,
    61,    28,   183,    27,     2,     3,   166,     4,    29,   111,
    5,   184,    36,    38,    44,     6,   112,    47,   120,   151,
    152,   121,   133,   113,   109,   134,    42,     7,     8,   164,
    173,   189,    51,   174,     9,    10,   128,   129,   130,   131,
    132,   129,   130,   131,   132,    54,    56,    57,    55,    63,
    65,    66,    69,    71,    30,    76,    77,   176,    82,    83,
    86,   103,   105,   106,   110,   118,   119,   182,   135,   144,
    167,   127,   137,   138,   165,   175,   177,   178,   179,   180,
    187,   188,    41,   186,   190,   181,   147,   140,     0,    75
};

static const yytype_int16 yycheck[] = {
    8,    58,    49,    21,    61,   135,    24,    25,    65,    27,
    28,     3,    69,     3,     4,     5,    12,    13,     8,     3,
    4,     5,     3,     4,     5,    82,    83,     6,     7,     4,
    5,    24,    55,    51,     6,     7,     3,     0,    61,     9,
    10,    11,    12,    13,   174,    12,    54,    56,     8,    10,
    11,    12,    13,    16,    38,    89,    49,    93,    50,    22,
    23,   118,    25,    38,   121,    28,    84,    57,    30,    29,
    33,    15,    16,    57,   110,    62,    57,   134,    24,    58,
    40,   115,    45,    46,    28,    92,    93,   105,    58,    52,
    53,    51,   128,   129,   130,   131,   132,    58,    16,    53,
    44,    35,    17,    49,    22,    23,   142,    25,    56,    20,
    28,    26,     3,     3,    23,    33,    27,    26,    58,   126,
    127,    61,    58,    34,    78,    61,    59,    45,    46,   137,
    58,   188,    30,    61,    52,    53,     9,    10,    11,    12,
    13,    10,    11,    12,    13,    61,    47,    59,    62,    19,
    57,    55,    57,     3,     3,     3,     3,   165,    21,    21,
    60,    54,    61,    31,    60,    50,     5,   175,    57,    57,
    5,     7,    18,    39,    18,    61,    58,    38,    36,    36,
    3,    57,    11,    43,    58,   174,   121,   108,    -1,    54
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] = {
    0,    16,    22,    23,    25,    28,    33,    45,    46,    52,
    53,    64,    65,    68,    78,    79,    80,    81,    85,    86,
    89,    49,    56,    24,    49,    30,    24,    49,    35,    56,
    3,    12,    91,   102,   103,   107,     3,   106,     3,    66,
    0,    65,    59,   106,    66,   106,   106,    66,   106,   106,
    62,    30,    92,    93,    61,    62,    47,    59,    15,    16,
    28,    44,    67,    19,    69,    57,    55,    90,    95,    57,
    75,     3,    94,   106,    90,   103,     3,     3,    87,    88,
    109,   109,    21,    21,    50,   109,    60,    70,    71,   109,
    4,     5,     8,    57,    98,    99,   100,   101,   104,   105,
    107,    74,   109,    54,    82,    61,    31,    96,    61,    90,
    60,    20,    27,    34,   108,   109,   109,   106,    50,     5,
    58,    61,   108,    98,    98,   101,     6,     7,     9,    10,
    11,    12,    13,    58,    61,    57,   106,    18,    39,    76,
    88,    38,    57,   101,    57,   108,   109,    71,    72,    58,
    58,    98,    98,   101,   101,   101,   101,   101,   109,    38,
    83,    84,   104,    97,   107,    18,   101,     5,     8,    29,
    40,    51,    73,    58,    61,    61,   107,    58,    38,    36,
    36,    84,   107,    17,    26,    77,    43,     3,    57,   109,
    58
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print(FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print(yyoutput, yytype, yyvaluep)
FILE *yyoutput;
int yytype;
YYSTYPE const * const yyvaluep;
#endif
{
    if(!yyvaluep)
        return;
# ifdef YYPRINT
    if(yytype < YYNTOKENS)
        YYPRINT(yyoutput, yytoknum[yytype], *yyvaluep);
# else
    YYUSE(yyoutput);
# endif
    switch(yytype) {
    default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print(FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print(yyoutput, yytype, yyvaluep)
FILE *yyoutput;
int yytype;
YYSTYPE const * const yyvaluep;
#endif
{
    if(yytype < YYNTOKENS)
        YYFPRINTF(yyoutput, "token %s (", yytname[yytype]);
    else
        YYFPRINTF(yyoutput, "nterm %s (", yytname[yytype]);

    yy_symbol_value_print(yyoutput, yytype, yyvaluep);
    YYFPRINTF(yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print(yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print(yybottom, yytop)
yytype_int16 *yybottom;
yytype_int16 *yytop;
#endif
{
    YYFPRINTF(stderr, "Stack now");
    for(; yybottom <= yytop; yybottom++) {
        int yybot = *yybottom;
        YYFPRINTF(stderr, " %d", yybot);
    }
    YYFPRINTF(stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print(YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print(yyvsp, yyrule)
YYSTYPE *yyvsp;
int yyrule;
#endif
{
    int yynrhs = yyr2[yyrule];
    int yyi;
    unsigned long int yylno = yyrline[yyrule];
    YYFPRINTF(stderr, "Reducing stack by rule %d (line %lu):\n",
              yyrule - 1, yylno);
    /* The symbols being reduced.  */
    for(yyi = 0; yyi < yynrhs; yyi++) {
        YYFPRINTF(stderr, "   $%d = ", yyi + 1);
        yy_symbol_print(stderr, yyrhs[yyprhs[yyrule] + yyi],
                        &(yyvsp[(yyi + 1) - (yynrhs)])
                       );
        YYFPRINTF(stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen(const char *yystr)
#else
static YYSIZE_T
yystrlen(yystr)
const char *yystr;
#endif
{
    YYSIZE_T yylen;
    for(yylen = 0; yystr[yylen]; yylen++)
        continue;
    return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy(char *yydest, const char *yysrc)
#else
static char *
yystpcpy(yydest, yysrc)
char *yydest;
const char *yysrc;
#endif
{
    char *yyd = yydest;
    const char *yys = yysrc;

    while((*yyd++ = *yys++) != '\0')
        continue;

    return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr(char *yyres, const char *yystr)
{
    if(*yystr == '"') {
        YYSIZE_T yyn = 0;
        char const *yyp = yystr;

        for(;;)
            switch(*++yyp) {
            case '\'':
            case ',':
                goto do_not_strip_quotes;

            case '\\':
                if(*++yyp != '\\')
                    goto do_not_strip_quotes;
                /* Fall through.  */
            default:
                if(yyres)
                    yyres[yyn] = *yyp;
                yyn++;
                break;

            case '"':
                if(yyres)
                    yyres[yyn] = '\0';
                return yyn;
            }
do_not_strip_quotes:
        ;
    }

    if(! yyres)
        return yystrlen(yystr);

    return yystpcpy(yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error(char *yyresult, int yystate, int yychar)
{
    int yyn = yypact[yystate];

    if(!(YYPACT_NINF < yyn && yyn <= YYLAST))
        return 0;
    else {
        int yytype = YYTRANSLATE(yychar);
        YYSIZE_T yysize0 = yytnamerr(0, yytname[yytype]);
        YYSIZE_T yysize = yysize0;
        YYSIZE_T yysize1;
        int yysize_overflow = 0;
        enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
        char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
        int yyx;

# if 0
        /* This is so xgettext sees the translatable formats that are
        constructed on the fly.  */
        YY_("syntax error, unexpected %s");
        YY_("syntax error, unexpected %s, expecting %s");
        YY_("syntax error, unexpected %s, expecting %s or %s");
        YY_("syntax error, unexpected %s, expecting %s or %s or %s");
        YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
        char *yyfmt;
        char const *yyf;
        static char const yyunexpected[] = "syntax error, unexpected %s";
        static char const yyexpecting[] = ", expecting %s";
        static char const yyor[] = " or %s";
        char yyformat[sizeof yyunexpected
                      + sizeof yyexpecting - 1
                      + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
                         * (sizeof yyor - 1))];
        char const *yyprefix = yyexpecting;

        /* Start YYX at -YYN if negative to avoid negative indexes in
        YYCHECK.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;

        /* Stay within bounds of both yycheck and yytname.  */
        int yychecklim = YYLAST - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        int yycount = 1;

        yyarg[0] = yytname[yytype];
        yyfmt = yystpcpy(yyformat, yyunexpected);

        for(yyx = yyxbegin; yyx < yyxend; ++yyx)
            if(yycheck[yyx + yyn] == yyx && yyx != YYTERROR) {
                if(yycount == YYERROR_VERBOSE_ARGS_MAXIMUM) {
                    yycount = 1;
                    yysize = yysize0;
                    yyformat[sizeof yyunexpected - 1] = '\0';
                    break;
                }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr(0, yytname[yyx]);
                yysize_overflow |= (yysize1 < yysize);
                yysize = yysize1;
                yyfmt = yystpcpy(yyfmt, yyprefix);
                yyprefix = yyor;
            }

        yyf = YY_(yyformat);
        yysize1 = yysize + yystrlen(yyf);
        yysize_overflow |= (yysize1 < yysize);
        yysize = yysize1;

        if(yysize_overflow)
            return YYSIZE_MAXIMUM;

        if(yyresult) {
            /* Avoid sprintf, as that infringes on the user's name space.
               Don't have undefined behavior even if the translation
               produced a string with the wrong number of "%s"s.  */
            char *yyp = yyresult;
            int yyi = 0;
            while((*yyp = *yyf) != '\0') {
                if(*yyp == '%' && yyf[1] == 's' && yyi < yycount) {
                    yyp += yytnamerr(yyp, yyarg[yyi++]);
                    yyf += 2;
                } else {
                    yyp++;
                    yyf++;
                }
            }
        }
        return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct(const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct(yymsg, yytype, yyvaluep)
const char *yymsg;
int yytype;
YYSTYPE *yyvaluep;
#endif
{
    YYUSE(yyvaluep);

    if(!yymsg)
        yymsg = "Deleting";
    YY_SYMBOL_PRINT(yymsg, yytype, yyvaluep, yylocationp);

    switch(yytype) {

    default:
        break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse(void *YYPARSE_PARAM);
#else
int yyparse();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse(void);
#else
int yyparse();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse(void *YYPARSE_PARAM)
#else
int
yyparse(YYPARSE_PARAM)
void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse(void)
#else
int
yyparse()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

    int yyn;
    int yyresult;
    /* Lookahead token as an internal (translated) token number.  */
    int yytoken;
    /* The variables used to return semantic value and location from the
       action routines.  */
    YYSTYPE yyval;

#if YYERROR_VERBOSE
    /* Buffer for error messages, and its allocated size.  */
    char yymsgbuf[128];
    char *yymsg = yymsgbuf;
    YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

    /* The number of symbols on the RHS of the reduced rule.
       Keep to zero when no symbol should be popped.  */
    int yylen = 0;

    yytoken = 0;
    yyss = yyssa;
    yyvs = yyvsa;
    yystacksize = YYINITDEPTH;

    YYDPRINTF((stderr, "Starting parse\n"));

    yystate = 0;
    yyerrstatus = 0;
    yynerrs = 0;
    yychar = YYEMPTY; /* Cause a token to be read.  */

    /* Initialize stack pointers.
       Waste one element of value and location stack
       so that they stay on the same level as the state stack.
       The wasted elements are never initialized.  */
    yyssp = yyss;
    yyvsp = yyvs;

    goto yysetstate;

    /*------------------------------------------------------------.
    | yynewstate -- Push a new state, which is found in yystate.  |
    `------------------------------------------------------------*/
yynewstate:
    /* In all cases, when you get here, the value and location stacks
       have just been pushed.  So pushing a state here evens the stacks.  */
    yyssp++;

yysetstate:
    *yyssp = yystate;

    if(yyss + yystacksize - 1 <= yyssp) {
        /* Get the current used size of the three stacks, in elements.  */
        YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
        {
            /* Give user a chance to reallocate the stack.  Use copies of
               these so that the &'s don't force the real ones into
               memory.  */
            YYSTYPE *yyvs1 = yyvs;
            yytype_int16 *yyss1 = yyss;

            /* Each stack pointer address is followed by the size of the
               data in use in that stack, in bytes.  This used to be a
               conditional around just the two extra args, but that might
               be undefined if yyoverflow is a macro.  */
            yyoverflow(YY_("memory exhausted"),
                       &yyss1, yysize * sizeof(*yyssp),
                       &yyvs1, yysize * sizeof(*yyvsp),
                       &yystacksize);

            yyss = yyss1;
            yyvs = yyvs1;
        }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
        goto yyexhaustedlab;
# else
        /* Extend the stack our own way.  */
        if(YYMAXDEPTH <= yystacksize)
            goto yyexhaustedlab;
        yystacksize *= 2;
        if(YYMAXDEPTH < yystacksize)
            yystacksize = YYMAXDEPTH;

        {
            yytype_int16 *yyss1 = yyss;
            union yyalloc *yyptr =
                        (union yyalloc *) YYSTACK_ALLOC(YYSTACK_BYTES(yystacksize));
            if(! yyptr)
                goto yyexhaustedlab;
            YYSTACK_RELOCATE(yyss_alloc, yyss);
            YYSTACK_RELOCATE(yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
            if(yyss1 != yyssa)
                YYSTACK_FREE(yyss1);
        }
# endif
#endif /* no yyoverflow */

        yyssp = yyss + yysize - 1;
        yyvsp = yyvs + yysize - 1;

        YYDPRINTF((stderr, "Stack size increased to %lu\n",
                   (unsigned long int) yystacksize));

        if(yyss + yystacksize - 1 <= yyssp)
            YYABORT;
    }

    YYDPRINTF((stderr, "Entering state %d\n", yystate));

    if(yystate == YYFINAL)
        YYACCEPT;

    goto yybackup;

    /*-----------.
    | yybackup.  |
    `-----------*/
yybackup:

    /* Do appropriate processing given the current state.  Read a
       lookahead token if we need one and don't already have one.  */

    /* First try to decide what to do without reference to lookahead token.  */
    yyn = yypact[yystate];
    if(yyn == YYPACT_NINF)
        goto yydefault;

    /* Not known => get a lookahead token if don't already have one.  */

    /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
    if(yychar == YYEMPTY) {
        YYDPRINTF((stderr, "Reading a token: "));
        yychar = YYLEX;
    }

    if(yychar <= YYEOF) {
        yychar = yytoken = YYEOF;
        YYDPRINTF((stderr, "Now at end of input.\n"));
    } else {
        yytoken = YYTRANSLATE(yychar);
        YY_SYMBOL_PRINT("Next token is", yytoken, &yylval, &yylloc);
    }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if(yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
        goto yydefault;
    yyn = yytable[yyn];
    if(yyn <= 0) {
        if(yyn == 0 || yyn == YYTABLE_NINF)
            goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
    }

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if(yyerrstatus)
        yyerrstatus--;

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the shifted token.  */
    yychar = YYEMPTY;

    yystate = yyn;
    *++yyvsp = yylval;

    goto yynewstate;


    /*-----------------------------------------------------------.
    | yydefault -- do the default action for the current state.  |
    `-----------------------------------------------------------*/
yydefault:
    yyn = yydefact[yystate];
    if(yyn == 0)
        goto yyerrlab;
    goto yyreduce;


    /*-----------------------------.
    | yyreduce -- Do a reduction.  |
    `-----------------------------*/
yyreduce:
    /* yyn is the number of a rule to reduce with.  */
    yylen = yyr2[yyn];

    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  Assigning to YYVAL
       unconditionally makes the parser a bit smaller, and it avoids a
       GCC warning that YYVAL may be used uninitialized.  */
    yyval = yyvsp[1 - yylen];


    YY_REDUCE_PRINT(yyn);
    switch(yyn) {
    case 4:

        /* Line 1455 of yacc.c  */
#line 58 "sql_parser.y"
    { cur_sql->type = SQL_USE_DB; ;}
    break;

    case 5:

        /* Line 1455 of yacc.c  */
#line 59 "sql_parser.y"
    { cur_sql->type = SQL_CREATE_DB; ;}
    break;

    case 6:

        /* Line 1455 of yacc.c  */
#line 60 "sql_parser.y"
    { cur_sql->type = SQL_DROP_DB; ;}
    break;

    case 9:

        /* Line 1455 of yacc.c  */
#line 63 "sql_parser.y"
    { cur_sql->type = SQL_CREATE_TB; ;}
    break;

    case 10:

        /* Line 1455 of yacc.c  */
#line 67 "sql_parser.y"
    { g_ptr_array_add(cur_sql->database_set, strdup((yyvsp[(1) - (1)].strval))); ;}
    break;

    case 16:

        /* Line 1455 of yacc.c  */
#line 80 "sql_parser.y"
    {
        g_ptr_array_add(cur_sql->table_set, strdup((yyvsp[(3) - (6)].strval)));
        cur_sql->column_set = cur_sql->cur_col_set;
        cur_sql->cur_col_set = NULL;
        ;
    }
    break;

    case 18:

        /* Line 1455 of yacc.c  */
#line 89 "sql_parser.y"
    {
        char tmp[1024];
        sprintf(tmp, "%d", (yyvsp[(3) - (3)].floatval));
        g_ptr_array_add(cur_sql->value_set, strdup(tmp)); ;
    }
    break;

    case 21:

        /* Line 1455 of yacc.c  */
#line 100 "sql_parser.y"
    {
        cur_sql->col_def_set[cur_sql->cur_col_set->len] = cur_sql->cur_col_def;

        cur_sql->cur_col_def = g_ptr_array_sized_new(4);
        g_ptr_array_set_free_func(cur_sql->cur_col_def, myg_char_strdup_destroy);

        g_ptr_array_add(cur_sql->cur_col_set, strdup((yyvsp[(1) - (3)].strval)));
        g_ptr_array_add(cur_sql->col_data_def, strdup((yyvsp[(2) - (3)].strval)));
        ;
    }
    break;

    case 23:

        /* Line 1455 of yacc.c  */
#line 113 "sql_parser.y"
    { g_ptr_array_add(cur_sql->cur_col_def, strdup((yyvsp[(2) - (2)].strval))); ;}
    break;

    case 24:

        /* Line 1455 of yacc.c  */
#line 117 "sql_parser.y"
    { sprintf((yyval.strval), "NOTNULL"); ;}
    break;

    case 25:

        /* Line 1455 of yacc.c  */
#line 118 "sql_parser.y"
    { sprintf((yyval.strval), "UNIQUE"); ;}
    break;

    case 26:

        /* Line 1455 of yacc.c  */
#line 119 "sql_parser.y"
    { sprintf((yyval.strval), "PRIMARYKEY"); ;}
    break;

    case 27:

        /* Line 1455 of yacc.c  */
#line 120 "sql_parser.y"
    { sprintf((yyval.strval), "FOREIGNKEY %s.%s", (yyvsp[(4) - (7)].strval), (yyvsp[(6) - (7)].strval)); ;}
    break;

    case 28:

        /* Line 1455 of yacc.c  */
#line 125 "sql_parser.y"
    { g_ptr_array_add(cur_sql->cur_col_set, strdup((yyvsp[(1) - (1)].strval))); ;}
    break;

    case 29:

        /* Line 1455 of yacc.c  */
#line 126 "sql_parser.y"
    { g_ptr_array_add(cur_sql->cur_col_set, strdup((yyvsp[(3) - (3)].strval))); ;}
    break;

    case 39:

        /* Line 1455 of yacc.c  */
#line 151 "sql_parser.y"
    { cur_sql->type = SQL_DELETE; ;}
    break;

    case 40:

        /* Line 1455 of yacc.c  */
#line 152 "sql_parser.y"
    { cur_sql->type = SQL_INSERT; ;}
    break;

    case 42:

        /* Line 1455 of yacc.c  */
#line 154 "sql_parser.y"
    { cur_sql->type = SQL_SELECT; ;}
    break;

    case 43:

        /* Line 1455 of yacc.c  */
#line 155 "sql_parser.y"
    { cur_sql->type = SQL_UPDATE; ;}
    break;

    case 45:

        /* Line 1455 of yacc.c  */
#line 163 "sql_parser.y"
    { g_ptr_array_add(cur_sql->table_set, strdup((yyvsp[(3) - (4)].strval))); ;}
    break;

    case 46:

        /* Line 1455 of yacc.c  */
#line 167 "sql_parser.y"
    {
        g_ptr_array_add(cur_sql->table_set, strdup((yyvsp[(3) - (5)].strval)));
        cur_sql->column_set = cur_sql->cur_col_set;
        cur_sql->cur_col_set = g_ptr_array_sized_new(8);
        g_ptr_array_set_free_func(cur_sql->cur_col_set, myg_char_strdup_destroy);
        ;
    }
    break;

    case 50:

        /* Line 1455 of yacc.c  */
#line 185 "sql_parser.y"
    { g_ptr_array_add(cur_sql->value_set, strdup((yyvsp[(1) - (1)].strval))); ;}
    break;

    case 51:

        /* Line 1455 of yacc.c  */
#line 186 "sql_parser.y"
    { g_ptr_array_add(cur_sql->value_set, NULL); ;}
    break;

    case 56:

        /* Line 1455 of yacc.c  */
#line 203 "sql_parser.y"
    {
        //update语句列引用和scalar_exp中的列引用同时规约，不能使用cur_col_set
        if(cur_sql->column_set == NULL) {
            cur_sql->column_set = g_ptr_array_sized_new(2);
            g_ptr_array_set_free_func(cur_sql->column_set, myg_char_strdup_destroy);
        }
        g_ptr_array_add(cur_sql->column_set, strdup((yyvsp[(1) - (3)].strval)));
        cur_sql->exp_refcol_set[cur_sql->expression_set->len] = cur_sql->cur_col_set;

        struct expression * exp;
        exp = expression_new_instance((yyvsp[(3) - (3)].strval));
        g_ptr_array_add(cur_sql->expression_set, exp);

        cur_sql->cur_col_set = g_ptr_array_sized_new(2);
        g_ptr_array_set_free_func(cur_sql->cur_col_set, myg_char_strdup_destroy);
        ;
    }
    break;

    case 57:

        /* Line 1455 of yacc.c  */
#line 219 "sql_parser.y"
    {
        if(cur_sql->column_set == NULL) {
            cur_sql->column_set = g_ptr_array_sized_new(2);
            g_ptr_array_set_free_func(cur_sql->column_set, myg_char_strdup_destroy);
        }
        g_ptr_array_add(cur_sql->column_set, strdup((yyvsp[(1) - (3)].strval)));
        cur_sql->exp_refcol_set[cur_sql->expression_set->len] = NULL;
        g_ptr_array_add(cur_sql->expression_set, NULL);
        ;
    }
    break;

    case 58:

        /* Line 1455 of yacc.c  */
#line 231 "sql_parser.y"
    {
        g_ptr_array_add(cur_sql->table_set, strdup((yyvsp[(2) - (5)].strval)));
        ;
    }
    break;

    case 61:

        /* Line 1455 of yacc.c  */
#line 242 "sql_parser.y"
    {
        cur_sql->column_set = cur_sql->cur_col_set;
        cur_sql->cur_col_set = g_ptr_array_sized_new(8);
        g_ptr_array_set_free_func(cur_sql->cur_col_set, myg_char_strdup_destroy);
        ;
    }
    break;

    case 62:

        /* Line 1455 of yacc.c  */
#line 247 "sql_parser.y"
    {
        g_ptr_array_add(cur_sql->cur_col_set, strdup("*"));
        cur_sql->column_set = cur_sql->cur_col_set;
        cur_sql->cur_col_set = g_ptr_array_sized_new(8);
        g_ptr_array_set_free_func(cur_sql->cur_col_set, myg_char_strdup_destroy);
        ;
    }
    break;

    case 65:

        /* Line 1455 of yacc.c  */
#line 267 "sql_parser.y"
    { g_ptr_array_add(cur_sql->table_set, strdup((yyvsp[(1) - (1)].strval))); ;}
    break;

    case 66:

        /* Line 1455 of yacc.c  */
#line 268 "sql_parser.y"
    { g_ptr_array_add(cur_sql->table_set, strdup((yyvsp[(3) - (3)].strval))); ;}
    break;

    case 67:

        /* Line 1455 of yacc.c  */
#line 272 "sql_parser.y"
    { strcpy(cur_sql->cond_formula, (yyvsp[(2) - (2)].strval)); ;}
    break;

    case 72:

        /* Line 1455 of yacc.c  */
#line 287 "sql_parser.y"
    { sprintf((yyval.strval), "%s+%s", (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval)); ;}
    break;

    case 73:

        /* Line 1455 of yacc.c  */
#line 288 "sql_parser.y"
    { sprintf((yyval.strval), "%s*%s", (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval)); ;}
    break;

    case 74:

        /* Line 1455 of yacc.c  */
#line 289 "sql_parser.y"
    { sprintf((yyval.strval), "~%s", (yyvsp[(2) - (2)].strval)); ;}
    break;

    case 75:

        /* Line 1455 of yacc.c  */
#line 290 "sql_parser.y"
    { sprintf((yyval.strval), "(%s)", (yyvsp[(2) - (3)].strval)); ;}
    break;

    case 76:

        /* Line 1455 of yacc.c  */
#line 291 "sql_parser.y"
    { sprintf((yyval.strval), "c"); ;}
    break;

    case 78:

        /* Line 1455 of yacc.c  */
#line 301 "sql_parser.y"
    {
        cur_sql->cond_refcol_set[cur_sql->condition_set->len] = cur_sql->cur_col_set;

        struct condition * cond;
        cond = condition_new_instance((yyvsp[(2) - (3)].intval), (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval));
        g_ptr_array_add(cur_sql->condition_set, cond);

        cur_sql->cur_col_set = g_ptr_array_sized_new(8);
        g_ptr_array_set_free_func(cur_sql->cur_col_set, myg_char_strdup_destroy);
        ;
    }
    break;

    case 79:

        /* Line 1455 of yacc.c  */
#line 315 "sql_parser.y"
    { sprintf((yyval.strval), "%s+%s", (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval)); ;}
    break;

    case 80:

        /* Line 1455 of yacc.c  */
#line 316 "sql_parser.y"
    { sprintf((yyval.strval), "%s-%s", (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval)); ;}
    break;

    case 81:

        /* Line 1455 of yacc.c  */
#line 317 "sql_parser.y"
    { sprintf((yyval.strval), "%s*%s", (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval)); ;}
    break;

    case 82:

        /* Line 1455 of yacc.c  */
#line 318 "sql_parser.y"
    { sprintf((yyval.strval), "%s/%s", (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval)); ;}
    break;

    case 83:

        /* Line 1455 of yacc.c  */
#line 319 "sql_parser.y"
    { sprintf((yyval.strval), "%s", (yyvsp[(1) - (1)].strval)); ;}
    break;

    case 84:

        /* Line 1455 of yacc.c  */
#line 320 "sql_parser.y"
    { sprintf((yyval.strval), "%s", (yyvsp[(1) - (1)].strval)); g_ptr_array_add(cur_sql->cur_col_set, strdup((yyvsp[(1) - (1)].strval))); ;}
    break;

    case 85:

        /* Line 1455 of yacc.c  */
#line 321 "sql_parser.y"
    { sprintf((yyval.strval), "(%s)", (yyvsp[(2) - (3)].strval)); ;}
    break;

    case 88:

        /* Line 1455 of yacc.c  */
#line 330 "sql_parser.y"
    { g_ptr_array_add(cur_sql->cur_col_set, strdup((yyvsp[(1) - (1)].strval))); ;}
    break;

    case 89:

        /* Line 1455 of yacc.c  */
#line 334 "sql_parser.y"
    { sprintf((yyval.strval), "%s", (yyvsp[(1) - (1)].strval)); ;}
    break;

    case 90:

        /* Line 1455 of yacc.c  */
#line 338 "sql_parser.y"
    { sprintf((yyval.strval), "%s", (yyvsp[(1) - (1)].strval)); strreplace((yyval.strval), "'", "", 256); ;}
    break;

    case 91:

        /* Line 1455 of yacc.c  */
#line 339 "sql_parser.y"
    { sprintf((yyval.strval), "%lf", (yyvsp[(1) - (1)].floatval)); ;}
    break;

    case 92:

        /* Line 1455 of yacc.c  */
#line 345 "sql_parser.y"
    { sprintf((yyval.strval), "%s", (yyvsp[(1) - (1)].strval)); ;}
    break;

    case 93:

        /* Line 1455 of yacc.c  */
#line 346 "sql_parser.y"
    { sprintf((yyval.strval), "%s.%s", (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval)); ;}
    break;

    case 94:

        /* Line 1455 of yacc.c  */
#line 350 "sql_parser.y"
    { sprintf((yyval.strval), "%s", (yyvsp[(1) - (1)].strval)); ;}
    break;

    case 95:

        /* Line 1455 of yacc.c  */
#line 351 "sql_parser.y"
    { sprintf((yyval.strval), "%s.%s", (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval)); ;}
    break;

    case 96:

        /* Line 1455 of yacc.c  */
#line 356 "sql_parser.y"
    { sprintf((yyval.strval), "%lf", (yyvsp[(3) - (4)].floatval)); ;}
    break;

    case 97:

        /* Line 1455 of yacc.c  */
#line 357 "sql_parser.y"
    { sprintf((yyval.strval), "-1"); ;}
    break;

    case 98:

        /* Line 1455 of yacc.c  */
#line 358 "sql_parser.y"
    { sprintf((yyval.strval), "-2"); ;}
    break;

    case 99:

        /* Line 1455 of yacc.c  */
#line 364 "sql_parser.y"
    { sprintf((yyval.strval), "%s", (yyvsp[(1) - (1)].strval)); ;}
    break;



    /* Line 1455 of yacc.c  */
#line 2022 "sql_parser.tab.c"
    default:
        break;
    }
    YY_SYMBOL_PRINT("-> $$ =", yyr1[yyn], &yyval, &yyloc);

    YYPOPSTACK(yylen);
    yylen = 0;
    YY_STACK_PRINT(yyss, yyssp);

    *++yyvsp = yyval;

    /* Now `shift' the result of the reduction.  Determine what state
       that goes to, based on the state we popped back to and the rule
       number reduced by.  */

    yyn = yyr1[yyn];

    yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
    if(0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
        yystate = yytable[yystate];
    else
        yystate = yydefgoto[yyn - YYNTOKENS];

    goto yynewstate;


    /*------------------------------------.
    | yyerrlab -- here on detecting error |
    `------------------------------------*/
yyerrlab:
    /* If not already recovering from an error, report this error.  */
    if(!yyerrstatus) {
        ++yynerrs;
#if ! YYERROR_VERBOSE
        yyerror(YY_("syntax error"));
#else
        {
            YYSIZE_T yysize = yysyntax_error(0, yystate, yychar);
            if(yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM) {
                YYSIZE_T yyalloc = 2 * yysize;
                if(!(yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
                    yyalloc = YYSTACK_ALLOC_MAXIMUM;
                if(yymsg != yymsgbuf)
                    YYSTACK_FREE(yymsg);
                yymsg = (char *) YYSTACK_ALLOC(yyalloc);
                if(yymsg)
                    yymsg_alloc = yyalloc;
                else {
                    yymsg = yymsgbuf;
                    yymsg_alloc = sizeof yymsgbuf;
                }
            }

            if(0 < yysize && yysize <= yymsg_alloc) {
                (void) yysyntax_error(yymsg, yystate, yychar);
                yyerror(yymsg);
            } else {
                yyerror(YY_("syntax error"));
                if(yysize != 0)
                    goto yyexhaustedlab;
            }
        }
#endif
    }



    if(yyerrstatus == 3) {
        /* If just tried and failed to reuse lookahead token after an
        error, discard it.  */

        if(yychar <= YYEOF) {
            /* Return failure if at end of input.  */
            if(yychar == YYEOF)
                YYABORT;
        } else {
            yydestruct("Error: discarding",
                       yytoken, &yylval);
            yychar = YYEMPTY;
        }
    }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


    /*---------------------------------------------------.
    | yyerrorlab -- error raised explicitly by YYERROR.  |
    `---------------------------------------------------*/
yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if(/*CONSTCOND*/ 0)
        goto yyerrorlab;

    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    YYPOPSTACK(yylen);
    yylen = 0;
    YY_STACK_PRINT(yyss, yyssp);
    yystate = *yyssp;
    goto yyerrlab1;


    /*-------------------------------------------------------------.
    | yyerrlab1 -- common code for both syntax error and YYERROR.  |
    `-------------------------------------------------------------*/
yyerrlab1:
    yyerrstatus = 3;	/* Each real token shifted decrements this.  */

    for(;;) {
        yyn = yypact[yystate];
        if(yyn != YYPACT_NINF) {
            yyn += YYTERROR;
            if(0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR) {
                yyn = yytable[yyn];
                if(0 < yyn)
                    break;
            }
        }

        /* Pop the current state because it cannot handle the error token.  */
        if(yyssp == yyss)
            YYABORT;


        yydestruct("Error: popping",
                   yystos[yystate], yyvsp);
        YYPOPSTACK(1);
        yystate = *yyssp;
        YY_STACK_PRINT(yyss, yyssp);
    }

    *++yyvsp = yylval;


    /* Shift the error token.  */
    YY_SYMBOL_PRINT("Shifting", yystos[yyn], yyvsp, yylsp);

    yystate = yyn;
    goto yynewstate;


    /*-------------------------------------.
    | yyacceptlab -- YYACCEPT comes here.  |
    `-------------------------------------*/
yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /*-----------------------------------.
    | yyabortlab -- YYABORT comes here.  |
    `-----------------------------------*/
yyabortlab:
    yyresult = 1;
    goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
    /*-------------------------------------------------.
    | yyexhaustedlab -- memory exhaustion comes here.  |
    `-------------------------------------------------*/
yyexhaustedlab:
    yyerror(YY_("memory exhausted"));
    yyresult = 2;
    /* Fall through.  */
#endif

yyreturn:
    if(yychar != YYEMPTY)
        yydestruct("Cleanup: discarding lookahead",
                   yytoken, &yylval);
    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    YYPOPSTACK(yylen);
    YY_STACK_PRINT(yyss, yyssp);
    while(yyssp != yyss) {
        yydestruct("Cleanup: popping",
                   yystos[*yyssp], yyvsp);
        YYPOPSTACK(1);
    }
#ifndef yyoverflow
    if(yyss != yyssa)
        YYSTACK_FREE(yyss);
#endif
#if YYERROR_VERBOSE
    if(yymsg != yymsgbuf)
        YYSTACK_FREE(yymsg);
#endif
    /* Make sure YYID is used.  */
    return YYID(yyresult);
}



/* Line 1675 of yacc.c  */
#line 366 "sql_parser.y"


