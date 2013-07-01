
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

extern int yylex (void);
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
typedef union YYSTYPE
{

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
YYID (int yyi)
#else
static int
YYID (yyi)
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
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
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
#define YYLAST   206

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNRULES -- Number of states.  */
#define YYNSTATES  205

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
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
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,    10,    13,    17,    21,    25,    30,
      32,    34,    38,    42,    47,    51,    56,    64,    65,    69,
      71,    75,    77,    79,    83,    84,    87,    90,    94,    99,
     104,   110,   121,   123,   127,   128,   132,   133,   138,   139,
     141,   143,   145,   147,   149,   151,   153,   155,   157,   160,
     165,   171,   176,   178,   182,   184,   186,   189,   193,   195,
     199,   203,   207,   213,   214,   216,   218,   220,   225,   228,
     230,   234,   237,   238,   242,   244,   248,   252,   256,   259,
     263,   265,   267,   271,   275,   279,   283,   287,   289,   291,
     295,   297,   301,   303,   305,   307,   309,   311,   315,   317,
     321,   323,   328,   330,   332
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      64,     0,    -1,    65,    59,    -1,    64,    65,    59,    -1,
      53,    66,    -1,    23,    24,    66,    -1,    28,    24,    66,
      -1,    28,    49,   108,    -1,    16,    49,   108,    67,    -1,
      68,    -1,     3,    -1,    15,   111,   110,    -1,    28,    21,
     111,    -1,    16,    21,   111,   110,    -1,    44,    50,   108,
      -1,    44,   111,    50,   111,    -1,    23,    49,   108,    69,
      57,    70,    58,    -1,    -1,    19,    60,     5,    -1,    71,
      -1,    70,    61,    71,    -1,    72,    -1,    75,    -1,   111,
     110,    73,    -1,    -1,    73,    74,    -1,     8,    38,    -1,
       8,    38,    51,    -1,     8,    38,    40,    36,    -1,    51,
      57,    76,    58,    -1,    40,    36,    57,    76,    58,    -1,
      29,    36,    57,    76,    58,    43,   108,    57,    76,    58,
      -1,   111,    -1,    76,    61,   111,    -1,    -1,    57,    76,
      58,    -1,    -1,    39,    18,   109,    79,    -1,    -1,    17,
      -1,    26,    -1,    80,    -1,    81,    -1,    82,    -1,    83,
      -1,    87,    -1,    88,    -1,    91,    -1,    22,    56,    -1,
      25,    30,   108,    92,    -1,    33,    35,   108,    77,    84,
      -1,    54,    57,    85,    58,    -1,    86,    -1,    85,    61,
      86,    -1,   106,    -1,    38,    -1,    45,    56,    -1,    46,
      93,    94,    -1,    90,    -1,    89,    61,    90,    -1,   111,
      60,   103,    -1,   111,    60,    38,    -1,    52,   108,    47,
      89,    92,    -1,    -1,    97,    -1,   104,    -1,    12,    -1,
      95,    92,    98,    78,    -1,    30,    96,    -1,   108,    -1,
      96,    61,   108,    -1,    55,   100,    -1,    -1,    31,    18,
      99,    -1,   109,    -1,    99,    61,   109,    -1,   100,     6,
     100,    -1,   100,     7,   100,    -1,     8,   100,    -1,    57,
     100,    58,    -1,   101,    -1,   102,    -1,   103,     9,   103,
      -1,   103,    10,   103,    -1,   103,    11,   103,    -1,   103,
      12,   103,    -1,   103,    13,   103,    -1,   106,    -1,   109,
      -1,    57,   103,    58,    -1,   105,    -1,   104,    61,   105,
      -1,   109,    -1,   107,    -1,     4,    -1,     5,    -1,     3,
      -1,     3,    62,     3,    -1,     3,    -1,     3,    62,     3,
      -1,    20,    -1,    20,    57,     5,    58,    -1,    34,    -1,
      27,    -1,     3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    52,    52,    53,    57,    58,    59,    60,    61,    62,
      66,    70,    71,    72,    73,    74,    79,    82,    84,    88,
      89,    93,    94,    99,   102,   104,   108,   109,   110,   114,
     115,   116,   121,   122,   125,   127,   130,   132,   135,   137,
     138,   142,   146,   147,   148,   149,   150,   151,   155,   159,
     163,   172,   176,   177,   181,   182,   186,   190,   194,   195,
     199,   215,   227,   232,   234,   238,   243,   252,   259,   263,
     264,   268,   271,   273,   277,   278,   283,   284,   285,   286,
     287,   292,   297,   311,   312,   313,   314,   315,   316,   317,
     321,   322,   326,   330,   334,   335,   341,   342,   346,   347,
     352,   353,   354,   355,   361
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
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
  "base_table_element_commalist", "base_table_element", "column_def",
  "column_def_opt_list", "column_def_opt", "table_constraint_def",
  "column_commalist", "opt_column_commalist", "opt_order_by_clause",
  "opt_asc_desc", "manipulative_statement", "commit_statement",
  "delete_statement_searched", "insert_statement", "values_or_query_spec",
  "insert_atom_commalist", "insert_atom", "rollback_statement",
  "select_statement", "assignment_commalist", "assignment",
  "update_statement_searched", "opt_where_clause", "selection",
  "table_exp", "from_clause", "table_ref_commalist", "where_clause",
  "opt_group_by_clause", "column_ref_commalist", "search_condition",
  "predicate", "comparison_predicate", "scalar_exp",
  "select_exp_commalist", "select_exp", "atom", "literal", "table_name",
  "column_ref", "data_type", "column", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
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
static const yytype_uint8 yyr1[] =
{
       0,    63,    64,    64,    65,    65,    65,    65,    65,    65,
      66,    67,    67,    67,    67,    67,    68,    69,    69,    70,
      70,    71,    71,    72,    73,    73,    74,    74,    74,    75,
      75,    75,    76,    76,    77,    77,    78,    78,    79,    79,
      79,    65,    80,    80,    80,    80,    80,    80,    81,    82,
      83,    84,    85,    85,    86,    86,    87,    88,    89,    89,
      90,    90,    91,    92,    92,    93,    93,    94,    95,    96,
      96,    97,    98,    98,    99,    99,   100,   100,   100,   100,
     100,   101,   102,   103,   103,   103,   103,   103,   103,   103,
     104,   104,   105,   106,   107,   107,   108,   108,   109,   109,
     110,   110,   110,   110,   111
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     2,     3,     3,     3,     4,     1,
       1,     3,     3,     4,     3,     4,     7,     0,     3,     1,
       3,     1,     1,     3,     0,     2,     2,     3,     4,     4,
       5,    10,     1,     3,     0,     3,     0,     4,     0,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     4,
       5,     4,     1,     3,     1,     1,     2,     3,     1,     3,
       3,     3,     5,     0,     1,     1,     1,     4,     2,     1,
       3,     2,     0,     3,     1,     3,     3,     3,     2,     3,
       1,     1,     3,     3,     3,     3,     3,     1,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     3,     1,     3,
       1,     4,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     9,    41,    42,    43,    44,    45,    46,
      47,     0,    48,     0,     0,     0,     0,     0,     0,    56,
      98,    66,     0,    65,    90,    92,    96,     0,    10,     4,
       1,     0,     2,     0,     5,    17,    63,     6,     7,    34,
       0,     0,    57,    63,     0,     0,     0,     3,     0,     0,
       0,     0,     8,     0,     0,     0,    49,    64,     0,     0,
      99,    68,    69,    72,    91,    97,   104,    63,    58,     0,
       0,     0,     0,     0,     0,     0,     0,    94,    95,     0,
       0,    71,    80,    81,     0,    87,    93,    88,     0,    32,
       0,    50,     0,     0,    36,     0,    62,     0,   100,   103,
     102,    11,     0,    12,    14,     0,    18,     0,     0,     0,
       0,    19,    21,    22,     0,    78,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    35,     0,     0,    70,     0,
       0,    67,    59,    61,     0,    60,     0,    13,    15,     0,
       0,     0,    16,     0,    24,    79,    89,    76,    77,    82,
      83,    84,    85,    86,    33,    55,     0,    52,    54,    73,
      74,     0,     0,     0,     0,     0,     0,    20,    23,    51,
       0,     0,    38,   101,     0,     0,    29,     0,    25,    53,
      75,    39,    40,    37,     0,    30,    26,     0,     0,    27,
       0,    28,     0,     0,    31
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    11,    12,    39,    62,    13,    64,   120,   121,   122,
     178,   188,   123,    98,    69,   141,   193,    14,    15,    16,
      17,   101,   166,   167,    18,    19,    77,    78,    20,    66,
      32,    52,    53,    71,    67,   104,   169,    91,    92,    93,
      94,    33,    34,    95,    96,    37,    97,   111,    99
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -121
static const yytype_int16 yypact[] =
{
      88,   -17,     8,   -10,    41,    11,    16,    30,   103,    73,
     104,    50,    55,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,    73,  -121,   104,    73,    73,   104,    73,    73,  -121,
      47,  -121,    90,    74,  -121,  -121,    75,    97,  -121,  -121,
    -121,   106,  -121,    21,  -121,   143,   108,  -121,  -121,   109,
     164,    73,  -121,   108,   165,   166,   167,  -121,   167,   150,
     151,     2,  -121,   113,   118,    12,  -121,  -121,   167,   123,
    -121,   117,  -121,   148,  -121,  -121,  -121,    57,  -121,   120,
      67,   167,   167,    73,   131,   177,    19,  -121,  -121,    12,
      12,   124,  -121,  -121,   116,  -121,  -121,  -121,    61,  -121,
     126,  -121,    73,   168,   145,   167,  -121,    20,   128,  -121,
    -121,  -121,    67,  -121,  -121,   167,  -121,   152,   153,   133,
      78,  -121,  -121,  -121,    67,  -121,     5,    80,    12,    12,
      23,    23,    23,    23,    23,  -121,   167,    36,  -121,   165,
     169,  -121,  -121,  -121,    23,   136,   186,  -121,  -121,   137,
     138,   167,  -121,    19,  -121,  -121,  -121,   185,  -121,   136,
     130,   130,  -121,  -121,  -121,  -121,    92,  -121,  -121,   132,
    -121,   165,    87,   139,   167,   167,    93,  -121,   188,  -121,
      36,   165,    91,  -121,    94,    98,  -121,   160,  -121,  -121,
    -121,  -121,  -121,  -121,   156,  -121,    28,    73,   170,  -121,
     144,  -121,   167,    99,  -121
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -121,  -121,   189,   135,  -121,  -121,  -121,  -121,    49,  -121,
    -121,  -121,  -121,  -120,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,    24,  -121,  -121,  -121,   100,  -121,   -24,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,    -5,  -121,  -121,
     -88,  -121,   149,  -119,  -121,   -21,    -7,  -103,   -48
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      43,    35,   127,    45,    46,    76,    48,    49,    79,   147,
      80,   128,   129,    84,    23,    30,    87,    88,   168,   145,
      89,   154,    76,    30,    87,    88,    30,    87,    88,    73,
      72,   176,    21,   112,   113,    26,    58,    59,   124,    24,
      87,    88,   159,   160,   161,   162,   163,    35,   117,    60,
      40,    28,    83,   106,   184,   185,   172,    79,   143,   118,
      27,   168,   114,   155,    22,    61,     1,   148,   198,    90,
     119,    25,     2,     3,   165,     4,    36,   144,     5,   199,
     144,   138,   203,     6,   125,   126,    29,   108,   164,   130,
     131,   132,   133,   134,   109,     7,     8,   131,   132,   133,
     134,   110,     9,    10,     1,   124,    30,    38,   191,    50,
       2,     3,    65,     4,    42,    31,     5,   192,   105,   135,
      51,     6,   136,   157,   158,   130,   131,   132,   133,   134,
     128,   129,   170,     7,     8,    54,   152,    55,   156,   153,
       9,    10,   133,   134,    56,   156,   131,   132,   133,   134,
     179,   186,   194,   180,   136,   136,   195,   204,    44,   136,
     136,    47,    63,    65,   182,    57,    68,    70,    30,    75,
      76,    81,    82,    85,   190,    86,   200,   100,   102,   103,
     107,   115,   116,   137,   140,   146,   139,   171,   149,   150,
     151,   173,   129,   181,   174,   175,   187,   183,   196,   197,
      41,   202,   177,    74,   189,   142,   201
};

static const yytype_uint8 yycheck[] =
{
      21,     8,    90,    24,    25,     3,    27,    28,    56,   112,
      58,     6,     7,    61,    24,     3,     4,     5,   137,   107,
       8,   124,     3,     3,     4,     5,     3,     4,     5,    53,
      51,   151,    49,    81,    82,    24,    15,    16,    86,    49,
       4,     5,   130,   131,   132,   133,   134,    54,    29,    28,
       0,    35,    50,    77,   174,   175,   144,   105,    38,    40,
      49,   180,    83,    58,    56,    44,    16,   115,    40,    57,
      51,    30,    22,    23,    38,    25,     3,    57,    28,    51,
      57,   102,   202,    33,    89,    90,    56,    20,   136,     9,
      10,    11,    12,    13,    27,    45,    46,    10,    11,    12,
      13,    34,    52,    53,    16,   153,     3,     3,    17,    62,
      22,    23,    55,    25,    59,    12,    28,    26,    61,    58,
      30,    33,    61,   128,   129,     9,    10,    11,    12,    13,
       6,     7,   139,    45,    46,    61,    58,    62,    58,    61,
      52,    53,    12,    13,    47,    58,    10,    11,    12,    13,
      58,    58,    58,    61,    61,    61,    58,    58,    23,    61,
      61,    26,    19,    55,   171,    59,    57,     3,     3,     3,
       3,    21,    21,    60,   181,    57,   197,    54,    61,    31,
      60,    50,     5,    57,    39,    57,    18,    18,    36,    36,
      57,     5,     7,    61,    57,    57,     8,    58,    38,    43,
      11,    57,   153,    54,   180,   105,    36
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    16,    22,    23,    25,    28,    33,    45,    46,    52,
      53,    64,    65,    68,    80,    81,    82,    83,    87,    88,
      91,    49,    56,    24,    49,    30,    24,    49,    35,    56,
       3,    12,    93,   104,   105,   109,     3,   108,     3,    66,
       0,    65,    59,   108,    66,   108,   108,    66,   108,   108,
      62,    30,    94,    95,    61,    62,    47,    59,    15,    16,
      28,    44,    67,    19,    69,    55,    92,    97,    57,    77,
       3,    96,   108,    92,   105,     3,     3,    89,    90,   111,
     111,    21,    21,    50,   111,    60,    57,     4,     5,     8,
      57,   100,   101,   102,   103,   106,   107,   109,    76,   111,
      54,    84,    61,    31,    98,    61,    92,    60,    20,    27,
      34,   110,   111,   111,   108,    50,     5,    29,    40,    51,
      70,    71,    72,    75,   111,   100,   100,   103,     6,     7,
       9,    10,    11,    12,    13,    58,    61,    57,   108,    18,
      39,    78,    90,    38,    57,   103,    57,   110,   111,    36,
      36,    57,    58,    61,   110,    58,    58,   100,   100,   103,
     103,   103,   103,   103,   111,    38,    85,    86,   106,    99,
     109,    18,   103,     5,    57,    57,    76,    71,    73,    58,
      61,    61,   109,    58,    76,    76,    58,     8,    74,    86,
     109,    17,    26,    79,    58,    58,    38,    43,    40,    51,
     108,    36,    57,    76,    58
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
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
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
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
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
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
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
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
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
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
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

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

  YYDPRINTF ((stderr, "Starting parse\n"));

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

  if (yyss + yystacksize - 1 <= yyssp)
    {
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
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

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
  if (yyn == 0)
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
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 32:

/* Line 1455 of yacc.c  */
#line 121 "sql_parser.y"
    { g_ptr_array_add(cur_sql->cur_col_set, strdup((yyvsp[(1) - (1)].strval))); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 122 "sql_parser.y"
    { g_ptr_array_add(cur_sql->cur_col_set, strdup((yyvsp[(3) - (3)].strval))); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 147 "sql_parser.y"
    { cur_sql->type = SQL_DELETE; ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 148 "sql_parser.y"
    { cur_sql->type = SQL_INSERT; ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 150 "sql_parser.y"
    { cur_sql->type = SQL_SELECT; ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 151 "sql_parser.y"
    { cur_sql->type = SQL_UPDATE; ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 159 "sql_parser.y"
    { g_ptr_array_add(cur_sql->table_set, strdup((yyvsp[(3) - (4)].strval))); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 163 "sql_parser.y"
    {
			g_ptr_array_add(cur_sql->table_set, strdup((yyvsp[(3) - (5)].strval)));
			cur_sql->column_set = cur_sql->cur_col_set;
			cur_sql->cur_col_set = g_ptr_array_sized_new(8);
			g_ptr_array_set_free_func(cur_sql->cur_col_set, myg_char_strdup_destroy);
		;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 181 "sql_parser.y"
    { g_ptr_array_add(cur_sql->value_set, strdup((yyvsp[(1) - (1)].strval))); ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 182 "sql_parser.y"
    { g_ptr_array_add(cur_sql->value_set, NULL); ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 199 "sql_parser.y"
    {
			//update��������ú�scalar_exp�е�������ͬʱ��Լ������ʹ��cur_col_set
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
		;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 215 "sql_parser.y"
    {
			if(cur_sql->column_set == NULL) {
				cur_sql->column_set = g_ptr_array_sized_new(2);
				g_ptr_array_set_free_func(cur_sql->column_set, myg_char_strdup_destroy);
			}
			g_ptr_array_add(cur_sql->column_set, strdup((yyvsp[(1) - (3)].strval)));
			cur_sql->exp_refcol_set[cur_sql->expression_set->len] = NULL;
			g_ptr_array_add(cur_sql->expression_set, NULL);
		;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 227 "sql_parser.y"
    {
			g_ptr_array_add(cur_sql->table_set, strdup((yyvsp[(2) - (5)].strval)));
		;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 238 "sql_parser.y"
    {
			cur_sql->column_set = cur_sql->cur_col_set;
			cur_sql->cur_col_set = g_ptr_array_sized_new(8);
			g_ptr_array_set_free_func(cur_sql->cur_col_set, myg_char_strdup_destroy);
		;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 243 "sql_parser.y"
    {
			g_ptr_array_add(cur_sql->cur_col_set, strdup("*")); 
			cur_sql->column_set = cur_sql->cur_col_set;
			cur_sql->cur_col_set = g_ptr_array_sized_new(8);
			g_ptr_array_set_free_func(cur_sql->cur_col_set, myg_char_strdup_destroy);
		;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 263 "sql_parser.y"
    { g_ptr_array_add(cur_sql->table_set, strdup((yyvsp[(1) - (1)].strval))); ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 264 "sql_parser.y"
    { g_ptr_array_add(cur_sql->table_set, strdup((yyvsp[(3) - (3)].strval))); ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 268 "sql_parser.y"
    { strcpy(cur_sql->cond_formula, (yyvsp[(2) - (2)].strval)); ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 283 "sql_parser.y"
    { sprintf((yyval.strval), "%s+%s", (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval)); ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 284 "sql_parser.y"
    { sprintf((yyval.strval), "%s*%s", (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval)); ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 285 "sql_parser.y"
    { sprintf((yyval.strval), "~%s", (yyvsp[(2) - (2)].strval)); ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 286 "sql_parser.y"
    { sprintf((yyval.strval), "(%s)", (yyvsp[(2) - (3)].strval)); ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 287 "sql_parser.y"
    { sprintf((yyval.strval), "c"); ;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 297 "sql_parser.y"
    {
			cur_sql->cond_refcol_set[cur_sql->condition_set->len] = cur_sql->cur_col_set;

			struct condition * cond;
			cond = condition_new_instance((yyvsp[(2) - (3)].intval), (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval));
			g_ptr_array_add(cur_sql->condition_set, cond);

			cur_sql->cur_col_set = g_ptr_array_sized_new(8);
			g_ptr_array_set_free_func(cur_sql->cur_col_set, myg_char_strdup_destroy);
		;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 311 "sql_parser.y"
    { sprintf((yyval.strval), "%s+%s", (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval)); ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 312 "sql_parser.y"
    { sprintf((yyval.strval), "%s-%s", (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval)); ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 313 "sql_parser.y"
    { sprintf((yyval.strval), "%s*%s", (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval)); ;}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 314 "sql_parser.y"
    { sprintf((yyval.strval), "%s/%s", (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval)); ;}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 315 "sql_parser.y"
    { sprintf((yyval.strval), "%s", (yyvsp[(1) - (1)].strval)); ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 316 "sql_parser.y"
    { sprintf((yyval.strval), "%s", (yyvsp[(1) - (1)].strval)); g_ptr_array_add(cur_sql->cur_col_set, strdup((yyvsp[(1) - (1)].strval))); ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 317 "sql_parser.y"
    { sprintf((yyval.strval), "(%s)", (yyvsp[(2) - (3)].strval)); ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 326 "sql_parser.y"
    { g_ptr_array_add(cur_sql->cur_col_set, strdup((yyvsp[(1) - (1)].strval))); ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 330 "sql_parser.y"
    { sprintf((yyval.strval),"%s", (yyvsp[(1) - (1)].strval)); ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 334 "sql_parser.y"
    { sprintf((yyval.strval), "%s", (yyvsp[(1) - (1)].strval)); strreplace((yyval.strval), "'", "", 256); ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 335 "sql_parser.y"
    { sprintf((yyval.strval), "%lf", (yyvsp[(1) - (1)].floatval)); ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 341 "sql_parser.y"
    { sprintf((yyval.strval), "%s", (yyvsp[(1) - (1)].strval)); ;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 342 "sql_parser.y"
    { sprintf((yyval.strval), "%s.%s", (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval)); ;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 346 "sql_parser.y"
    { sprintf((yyval.strval), "%s", (yyvsp[(1) - (1)].strval)); ;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 347 "sql_parser.y"
    { sprintf((yyval.strval), "%s.%s", (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval)); ;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 361 "sql_parser.y"
    { sprintf((yyval.strval), "%s", (yyvsp[(1) - (1)].strval)); ;}
    break;



/* Line 1455 of yacc.c  */
#line 1912 "sql_parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
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
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 363 "sql_parser.y"


