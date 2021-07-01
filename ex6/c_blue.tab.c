/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "c_blue.y"

        #include "stdio.h"
        #include "math.h"
        #include "string.h"
        #include "def.h"
        extern int yylineno;
        extern char *yytext;
        extern FILE *yyin;
        void yyerror(const char* fmt);
        void display(struct Node *,int);

#line 82 "c_blue.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_C_BLUE_TAB_H_INCLUDED
# define YY_YY_C_BLUE_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CHAR = 258,
    INT = 259,
    ID = 260,
    RELOP = 261,
    TYPE = 262,
    FLOAT = 263,
    STRUCT = 264,
    WRITE = 265,
    READ = 266,
    DPLUS = 267,
    LP = 268,
    RP = 269,
    LC = 270,
    RC = 271,
    LB = 272,
    RB = 273,
    SEMI = 274,
    COMMA = 275,
    DOT = 276,
    ADD = 277,
    SUB = 278,
    MUL = 279,
    DIV = 280,
    ASSIGNOP = 281,
    AND = 282,
    OR = 283,
    NOT = 284,
    ADDSELF = 285,
    SUBSELF = 286,
    IF = 287,
    ELSE = 288,
    WHILE = 289,
    FOR = 290,
    RETURN = 291,
    COLON = 292,
    DEFAULT = 293,
    CONTINUE = 294,
    BREAK = 295,
    VOID = 296,
    EXT_DEF_LIST = 297,
    EXT_VAR_DEF = 298,
    FUNC_DEF = 299,
    FUNC_DEC = 300,
    EXT_DEC_LIST = 301,
    PARAM_LIST = 302,
    PARAM_DEC = 303,
    VAR_DEF = 304,
    DEC_LIST = 305,
    DEF_LIST = 306,
    COMP_STM = 307,
    STM_LIST = 308,
    EXP_STMT = 309,
    IF_THEN = 310,
    IF_THEN_ELSE = 311,
    ARRAY_LIST = 312,
    ARRAY_LAST = 313,
    FUNC_CALL = 314,
    ARGS = 315,
    FUNCTION = 316,
    PARAM = 317,
    ARG = 318,
    CALL = 319,
    LABEL = 320,
    GOTO = 321,
    JLT = 322,
    JLE = 323,
    JGT = 324,
    JGE = 325,
    EQ = 326,
    NEQ = 327,
    FOR_DEC = 328,
    STRUCT_DEF = 329,
    STRUCT_DEC = 330,
    STRUCT_TAG = 331,
    EXP_ELE = 332,
    DEFAULT_STMT = 333,
    EXP_ARRAY = 334,
    EXT_STRUCT_DEF = 335,
    ARRAY_DEC = 336,
    ADDSELF_L = 337,
    ADDSELF_R = 338,
    SUBSELF_L = 339,
    SUBSELF_R = 340,
    USUB = 341,
    LOWER_THEN_ELSE = 342
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 15 "c_blue.y"

	int    type_int;
	float  type_float;
	char   type_id[32];
        char   type_char[32];
        char   struct_name[32];
	struct Node *ptr;

#line 231 "c_blue.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_C_BLUE_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   409

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  149

#define YYUNDEFTOK  2
#define YYMAXUTOK   342


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    55,    55,    57,    58,    60,    61,    62,    63,    65,
      66,    68,    69,    71,    74,    75,    78,    79,    82,    83,
      86,    87,    89,    90,    92,    95,    97,    98,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     114,   117,   118,   119,   121,   123,   124,   126,   127,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   156,   157
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR", "INT", "ID", "RELOP", "TYPE",
  "FLOAT", "STRUCT", "WRITE", "READ", "DPLUS", "LP", "RP", "LC", "RC",
  "LB", "RB", "SEMI", "COMMA", "DOT", "ADD", "SUB", "MUL", "DIV",
  "ASSIGNOP", "AND", "OR", "NOT", "ADDSELF", "SUBSELF", "IF", "ELSE",
  "WHILE", "FOR", "RETURN", "COLON", "DEFAULT", "CONTINUE", "BREAK",
  "VOID", "EXT_DEF_LIST", "EXT_VAR_DEF", "FUNC_DEF", "FUNC_DEC",
  "EXT_DEC_LIST", "PARAM_LIST", "PARAM_DEC", "VAR_DEF", "DEC_LIST",
  "DEF_LIST", "COMP_STM", "STM_LIST", "EXP_STMT", "IF_THEN",
  "IF_THEN_ELSE", "ARRAY_LIST", "ARRAY_LAST", "FUNC_CALL", "ARGS",
  "FUNCTION", "PARAM", "ARG", "CALL", "LABEL", "GOTO", "JLT", "JLE", "JGT",
  "JGE", "EQ", "NEQ", "FOR_DEC", "STRUCT_DEF", "STRUCT_DEC", "STRUCT_TAG",
  "EXP_ELE", "DEFAULT_STMT", "EXP_ARRAY", "EXT_STRUCT_DEF", "ARRAY_DEC",
  "ADDSELF_L", "ADDSELF_R", "SUBSELF_L", "SUBSELF_R", "USUB",
  "LOWER_THEN_ELSE", "$accept", "program", "ExtDefList", "ExtDef",
  "Specifier", "StructSpecifier", "OptTag", "ExtDecList", "VarDec",
  "Arraylist", "FuncDec", "VarList", "ParamDec", "CompSt", "StmList",
  "Stmt", "ForDec", "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342
};
# endif

#define YYPACT_NINF (-86)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-42)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     216,    -9,   -86,    21,    38,   -86,   216,    36,    34,   -86,
     -86,    41,   -86,   -86,    20,    44,    47,    49,   -86,     8,
      52,    64,   -86,   -86,    72,    88,   -86,    65,    72,   -86,
      67,    88,   -86,    72,    71,    66,    69,    83,   -86,   126,
     -86,    62,    86,    82,   -86,   -86,   -86,   -86,    73,    83,
     -86,   -86,    23,   -86,    93,    95,   207,   207,   207,   207,
     207,   108,   112,   119,   207,    96,   116,   121,   -86,   132,
     126,   220,   207,   -86,    72,   -86,   -86,   178,   -86,    72,
      72,   243,   117,   117,   117,   117,   207,   207,   207,   256,
     164,   -86,   -86,   -86,   -86,   207,   -86,   145,   207,   207,
     207,   207,   207,   207,   207,   -86,   -86,   355,   -86,   -86,
     270,   137,   140,   149,   -86,   293,   316,   156,   329,   -86,
     -86,   122,   -86,    -2,    -2,     4,     4,    48,   378,   366,
     207,   -86,   152,   154,   164,   164,   164,   207,   -86,   -86,
     -86,   143,   -86,   -86,   343,   164,   207,   -86,   355
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     9,     0,     0,     2,     0,     0,    10,     8,
      13,    12,     1,     4,    16,     0,    14,     0,     6,     0,
       0,     0,    17,     5,     0,     0,     7,     0,     0,    10,
       0,     0,    21,     0,     0,    22,     0,    16,    15,    72,
      43,    47,     0,    45,    11,    42,    24,    20,     0,    18,
      69,    67,    66,    68,     0,     0,    72,    72,    72,    72,
      72,     0,     0,     0,    72,     0,     0,     0,    29,     0,
      72,     0,    72,    44,     0,    23,    19,    72,    70,     0,
       0,     0,    62,    63,    59,    60,    72,    72,    72,     0,
      72,    35,    36,    25,    27,    72,    28,     0,    72,    72,
      72,    72,    72,    72,    72,    57,    58,    48,    46,    65,
      74,     0,     0,     0,    61,     0,     0,     0,     0,    30,
      39,    52,    71,    53,    54,    55,    56,    49,    50,    51,
      72,    64,     0,     0,    72,    72,    72,    72,    73,    38,
      37,    31,    33,    34,     0,    72,    72,    32,    40
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -86,   -86,   153,   -86,     7,    12,   -86,   160,   -22,    13,
     -86,   130,   -86,   163,   115,   -85,   -86,   -11,   -86,   114,
     -86,   -56,    59
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    28,    29,    11,    15,    16,    22,
      17,    34,    35,    68,    69,    70,   117,    30,    31,    42,
      43,    71,   111
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      81,    82,    83,    84,    85,   120,    41,     7,    89,    27,
       9,    46,     8,     7,    39,     2,   107,     3,     8,    97,
      45,   110,   100,   101,   -41,    97,    10,    33,   105,   106,
     115,   116,   118,    20,   105,   106,    77,    21,    12,   121,
      21,    14,   123,   124,   125,   126,   127,   128,   129,   141,
     142,   143,    41,    18,    95,    33,    19,   112,   113,     2,
     147,     3,    76,    23,    25,    78,    32,    24,    36,    97,
      98,    99,   100,   101,   110,   103,   104,    37,   105,   106,
       2,   144,     3,    44,    40,    47,    48,    49,    72,    27,
     148,   -41,   -41,   -41,   -41,     2,   -41,     3,   -41,   -41,
      21,   -41,    74,   -41,   -41,    73,    79,   -41,    80,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,    86,   -41,   -41,   -41,    87,   -41,   -41,   -41,    50,
      51,    52,    88,    90,    53,    91,    54,    55,    97,    56,
      92,    25,   -26,    97,    98,    99,   100,   101,    93,    57,
     122,   131,   105,   106,   132,    58,    59,    60,    61,    13,
      62,    63,    64,   133,    65,    66,    67,    50,    51,    52,
     136,   139,    53,   140,    54,    55,   145,    56,    75,    25,
      26,    50,    51,    52,    38,    94,    53,    57,   108,   138,
       0,    56,   109,    58,    59,    60,    61,     0,    62,    63,
      64,    57,    65,    66,    67,     0,     0,    58,    59,    60,
      50,    51,    52,     0,     0,    53,    -3,     1,     0,     0,
      56,     0,     0,     2,     0,     3,    95,     0,     0,     0,
      57,     0,     0,     0,     0,     0,    58,    59,    60,    96,
       0,    97,    98,    99,   100,   101,   102,   103,   104,    95,
     105,   106,     0,     0,     0,     0,     0,   114,     0,     0,
       0,     0,    95,     0,    97,    98,    99,   100,   101,   102,
     103,   104,     0,   105,   106,   119,    95,    97,    98,    99,
     100,   101,   102,   103,   104,     0,   105,   106,     0,     0,
     130,    97,    98,    99,   100,   101,   102,   103,   104,    95,
     105,   106,     0,     0,     0,     0,     0,   134,     0,     0,
       0,     0,     0,     0,    97,    98,    99,   100,   101,   102,
     103,   104,    95,   105,   106,     0,     0,     0,     0,     0,
     135,     0,     0,     0,     0,    95,     0,    97,    98,    99,
     100,   101,   102,   103,   104,     0,   105,   106,   137,    95,
      97,    98,    99,   100,   101,   102,   103,   104,     0,   105,
     106,    95,   146,     0,    97,    98,    99,   100,   101,   102,
     103,   104,    95,   105,   106,     0,    97,    98,    99,   100,
     101,   102,   103,   104,    95,   105,   106,    97,    98,    99,
     100,   101,     0,   103,     0,     0,   105,   106,     0,    97,
      98,    99,   100,   101,     0,     0,     0,     0,   105,   106
};

static const yytype_int16 yycheck[] =
{
      56,    57,    58,    59,    60,    90,    28,     0,    64,     1,
      19,    33,     0,     6,    25,     7,    72,     9,     6,    21,
      31,    77,    24,    25,    16,    21,     5,    20,    30,    31,
      86,    87,    88,    13,    30,    31,    13,    17,     0,    95,
      17,     5,    98,    99,   100,   101,   102,   103,   104,   134,
     135,   136,    74,    19,     6,    48,    15,    79,    80,     7,
     145,     9,    49,    19,    15,    52,    14,    20,     4,    21,
      22,    23,    24,    25,   130,    27,    28,     5,    30,    31,
       7,   137,     9,    16,    19,    14,    20,    18,    26,     1,
     146,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      17,    13,    20,    15,    16,    19,    13,    19,    13,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    13,    34,    35,    36,    13,    38,    39,    40,     3,
       4,     5,    13,    37,     8,    19,    10,    11,    21,    13,
      19,    15,    16,    21,    22,    23,    24,    25,    16,    23,
       5,    14,    30,    31,    14,    29,    30,    31,    32,     6,
      34,    35,    36,    14,    38,    39,    40,     3,     4,     5,
      14,    19,     8,    19,    10,    11,    33,    13,    48,    15,
      17,     3,     4,     5,    24,    70,     8,    23,    74,   130,
      -1,    13,    14,    29,    30,    31,    32,    -1,    34,    35,
      36,    23,    38,    39,    40,    -1,    -1,    29,    30,    31,
       3,     4,     5,    -1,    -1,     8,     0,     1,    -1,    -1,
      13,    -1,    -1,     7,    -1,     9,     6,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,    19,
      -1,    21,    22,    23,    24,    25,    26,    27,    28,     6,
      30,    31,    -1,    -1,    -1,    -1,    -1,    14,    -1,    -1,
      -1,    -1,     6,    -1,    21,    22,    23,    24,    25,    26,
      27,    28,    -1,    30,    31,    19,     6,    21,    22,    23,
      24,    25,    26,    27,    28,    -1,    30,    31,    -1,    -1,
      20,    21,    22,    23,    24,    25,    26,    27,    28,     6,
      30,    31,    -1,    -1,    -1,    -1,    -1,    14,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    22,    23,    24,    25,    26,
      27,    28,     6,    30,    31,    -1,    -1,    -1,    -1,    -1,
      14,    -1,    -1,    -1,    -1,     6,    -1,    21,    22,    23,
      24,    25,    26,    27,    28,    -1,    30,    31,    19,     6,
      21,    22,    23,    24,    25,    26,    27,    28,    -1,    30,
      31,     6,    19,    -1,    21,    22,    23,    24,    25,    26,
      27,    28,     6,    30,    31,    -1,    21,    22,    23,    24,
      25,    26,    27,    28,     6,    30,    31,    21,    22,    23,
      24,    25,    -1,    27,    -1,    -1,    30,    31,    -1,    21,
      22,    23,    24,    25,    -1,    -1,    -1,    -1,    30,    31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     7,     9,    89,    90,    91,    92,    93,    19,
       5,    94,     0,    90,     5,    95,    96,    98,    19,    15,
      13,    17,    97,    19,    20,    15,   101,     1,    92,    93,
     105,   106,    14,    92,    99,   100,     4,     5,    95,   105,
      19,    96,   107,   108,    16,   105,    96,    14,    20,    18,
       3,     4,     5,     8,    10,    11,    13,    23,    29,    30,
      31,    32,    34,    35,    36,    38,    39,    40,   101,   102,
     103,   109,    26,    19,    20,    99,    97,    13,    97,    13,
      13,   109,   109,   109,   109,   109,    13,    13,    13,   109,
      37,    19,    19,    16,   102,     6,    19,    21,    22,    23,
      24,    25,    26,    27,    28,    30,    31,   109,   107,    14,
     109,   110,    96,    96,    14,   109,   109,   104,   109,    19,
     103,   109,     5,   109,   109,   109,   109,   109,   109,   109,
      20,    14,    14,    14,    14,    14,    14,    19,   110,    19,
      19,   103,   103,   103,   109,    33,    19,   103,   109
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    88,    89,    90,    90,    91,    91,    91,    91,    92,
      92,    93,    93,    94,    95,    95,    96,    96,    97,    97,
      98,    98,    99,    99,   100,   101,   102,   102,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     104,   105,   105,   105,   106,   107,   107,   108,   108,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   110,   110
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     3,     2,     1,
       1,     5,     2,     1,     1,     3,     1,     2,     3,     4,
       4,     3,     1,     3,     2,     4,     0,     2,     2,     1,
       3,     5,     7,     5,     5,     2,     2,     5,     5,     3,
       5,     0,     2,     2,     3,     1,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       2,     3,     2,     2,     4,     3,     1,     1,     1,     1,
       2,     3,     0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 55 "c_blue.y"
                       {display((yyvsp[0].ptr),0);semantic_Analysis0((yyvsp[0].ptr));}
#line 1684 "c_blue.tab.c"
    break;

  case 3:
#line 57 "c_blue.y"
            {(yyval.ptr)=NULL;}
#line 1690 "c_blue.tab.c"
    break;

  case 4:
#line 58 "c_blue.y"
                              {(yyval.ptr)=mknode(2,EXT_DEF_LIST,yylineno,(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 1696 "c_blue.tab.c"
    break;

  case 5:
#line 60 "c_blue.y"
                                      {(yyval.ptr)=mknode(2,EXT_VAR_DEF,yylineno,(yyvsp[-2].ptr),(yyvsp[-1].ptr));}
#line 1702 "c_blue.tab.c"
    break;

  case 6:
#line 61 "c_blue.y"
                               {(yyval.ptr)=mknode(1,EXT_STRUCT_DEF,yylineno,(yyvsp[-1].ptr));}
#line 1708 "c_blue.tab.c"
    break;

  case 7:
#line 62 "c_blue.y"
                                      {(yyval.ptr)=mknode(3,FUNC_DEF,yylineno,(yyvsp[-2].ptr),(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 1714 "c_blue.tab.c"
    break;

  case 8:
#line 63 "c_blue.y"
                       { (yyval.ptr) = NULL; fprintf(stderr, "Grammar Error at Line %d Column %d：",yylloc.first_line,yylloc.first_column);}
#line 1720 "c_blue.tab.c"
    break;

  case 9:
#line 65 "c_blue.y"
                    {(yyval.ptr)=mknode(0,TYPE,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[0].type_id));(yyval.ptr)->type=(!strcmp((yyvsp[0].type_id),"int"))? INT : ((!strcmp((yyvsp[0].type_id), "float")) ? FLOAT : ((!strcmp((yyvsp[0].type_id), "char")) ? CHAR : VOID));}
#line 1726 "c_blue.tab.c"
    break;

  case 10:
#line 66 "c_blue.y"
                            {(yyval.ptr)=(yyvsp[0].ptr);}
#line 1732 "c_blue.tab.c"
    break;

  case 11:
#line 68 "c_blue.y"
                                             {(yyval.ptr)=mknode(2, STRUCT_DEF, yylineno, (yyvsp[-3].ptr), (yyvsp[-1].ptr));}
#line 1738 "c_blue.tab.c"
    break;

  case 12:
#line 69 "c_blue.y"
                               {(yyval.ptr)=mknode(1, STRUCT_DEC, yylineno, (yyvsp[0].ptr));}
#line 1744 "c_blue.tab.c"
    break;

  case 13:
#line 71 "c_blue.y"
           {(yyval.ptr)=mknode(0, ID, yylineno);strcpy((yyval.ptr)->type_id, (yyvsp[0].type_id));}
#line 1750 "c_blue.tab.c"
    break;

  case 14:
#line 74 "c_blue.y"
                         {(yyval.ptr)=mknode(1,EXT_DEC_LIST,yylineno,(yyvsp[0].ptr));}
#line 1756 "c_blue.tab.c"
    break;

  case 15:
#line 75 "c_blue.y"
                                     {(yyval.ptr)=mknode(2,EXT_DEC_LIST,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 1762 "c_blue.tab.c"
    break;

  case 16:
#line 78 "c_blue.y"
                     {(yyval.ptr)=mknode(0,ID,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[0].type_id));}
#line 1768 "c_blue.tab.c"
    break;

  case 17:
#line 79 "c_blue.y"
                      {(yyval.ptr)=mknode(1,ARRAY_DEC,yylineno,(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[-1].type_id));}
#line 1774 "c_blue.tab.c"
    break;

  case 18:
#line 82 "c_blue.y"
                                       {(yyval.ptr)=mknode(0,ARRAY_LAST,yylineno);(yyval.ptr)->type_int=(yyvsp[-1].type_int);(yyval.ptr)->type=INT;}
#line 1780 "c_blue.tab.c"
    break;

  case 19:
#line 83 "c_blue.y"
                                      {(yyval.ptr)=mknode(1,ARRAY_LIST,yylineno,(yyvsp[0].ptr));(yyval.ptr)->type_int=(yyvsp[-2].type_int);(yyval.ptr)->type=INT;}
#line 1786 "c_blue.tab.c"
    break;

  case 20:
#line 86 "c_blue.y"
                            {(yyval.ptr)=mknode(1,FUNC_DEC,yylineno,(yyvsp[-1].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[-3].type_id));}
#line 1792 "c_blue.tab.c"
    break;

  case 21:
#line 87 "c_blue.y"
                     {(yyval.ptr)=mknode(0,FUNC_DEC,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[-2].type_id));(yyval.ptr)->ptr[0]=NULL;}
#line 1798 "c_blue.tab.c"
    break;

  case 22:
#line 89 "c_blue.y"
                   {(yyval.ptr)=mknode(1,PARAM_LIST,yylineno,(yyvsp[0].ptr));}
#line 1804 "c_blue.tab.c"
    break;

  case 23:
#line 90 "c_blue.y"
                                  {(yyval.ptr)=mknode(2,PARAM_LIST,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 1810 "c_blue.tab.c"
    break;

  case 24:
#line 92 "c_blue.y"
                                   {(yyval.ptr)=mknode(2,PARAM_DEC,yylineno,(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 1816 "c_blue.tab.c"
    break;

  case 25:
#line 95 "c_blue.y"
                                 {(yyval.ptr)=mknode(2,COMP_STM,yylineno,(yyvsp[-2].ptr),(yyvsp[-1].ptr));}
#line 1822 "c_blue.tab.c"
    break;

  case 26:
#line 97 "c_blue.y"
         {(yyval.ptr)=NULL; }
#line 1828 "c_blue.tab.c"
    break;

  case 27:
#line 98 "c_blue.y"
                        {(yyval.ptr)=mknode(2,STM_LIST,yylineno,(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 1834 "c_blue.tab.c"
    break;

  case 28:
#line 100 "c_blue.y"
                    {(yyval.ptr)=mknode(1,EXP_STMT,yylineno,(yyvsp[-1].ptr));}
#line 1840 "c_blue.tab.c"
    break;

  case 29:
#line 101 "c_blue.y"
                    {(yyval.ptr)=(yyvsp[0].ptr);}
#line 1846 "c_blue.tab.c"
    break;

  case 30:
#line 102 "c_blue.y"
                          {(yyval.ptr)=mknode(1,RETURN,yylineno,(yyvsp[-1].ptr));}
#line 1852 "c_blue.tab.c"
    break;

  case 31:
#line 103 "c_blue.y"
                                                  {(yyval.ptr)=mknode(2,IF_THEN,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 1858 "c_blue.tab.c"
    break;

  case 32:
#line 104 "c_blue.y"
                                      {(yyval.ptr)=mknode(3,IF_THEN_ELSE,yylineno,(yyvsp[-4].ptr),(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 1864 "c_blue.tab.c"
    break;

  case 33:
#line 105 "c_blue.y"
                             {(yyval.ptr)=mknode(2,WHILE,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 1870 "c_blue.tab.c"
    break;

  case 34:
#line 106 "c_blue.y"
                              {(yyval.ptr)=mknode(2,FOR,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 1876 "c_blue.tab.c"
    break;

  case 35:
#line 107 "c_blue.y"
                      {(yyval.ptr)=mknode(0,CONTINUE, yylineno);}
#line 1882 "c_blue.tab.c"
    break;

  case 36:
#line 108 "c_blue.y"
                   {(yyval.ptr)=mknode(0,BREAK,yylineno);}
#line 1888 "c_blue.tab.c"
    break;

  case 37:
#line 109 "c_blue.y"
                               {(yyval.ptr)=mknode(1,READ,yylineno,(yyvsp[-2].ptr));}
#line 1894 "c_blue.tab.c"
    break;

  case 38:
#line 110 "c_blue.y"
                                {(yyval.ptr)=mknode(1,WRITE,yylineno,(yyvsp[-2].ptr));}
#line 1900 "c_blue.tab.c"
    break;

  case 39:
#line 111 "c_blue.y"
                           {(yyval.ptr)=mknode(1, DEFAULT_STMT, yylineno,(yyvsp[0].ptr));}
#line 1906 "c_blue.tab.c"
    break;

  case 40:
#line 114 "c_blue.y"
                              {(yyval.ptr)=mknode(3, FOR_DEC, yylineno, (yyvsp[-4].ptr), (yyvsp[-2].ptr), (yyvsp[0].ptr));}
#line 1912 "c_blue.tab.c"
    break;

  case 41:
#line 117 "c_blue.y"
         {(yyval.ptr)=NULL; }
#line 1918 "c_blue.tab.c"
    break;

  case 42:
#line 118 "c_blue.y"
                      {(yyval.ptr)=mknode(2,DEF_LIST,yylineno,(yyvsp[-1].ptr),(yyvsp[0].ptr));}
#line 1924 "c_blue.tab.c"
    break;

  case 43:
#line 119 "c_blue.y"
                       {(yyval.ptr)=NULL;fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);}
#line 1930 "c_blue.tab.c"
    break;

  case 44:
#line 121 "c_blue.y"
                               {(yyval.ptr)=mknode(2,VAR_DEF,yylineno,(yyvsp[-2].ptr),(yyvsp[-1].ptr));}
#line 1936 "c_blue.tab.c"
    break;

  case 45:
#line 123 "c_blue.y"
              {(yyval.ptr)=mknode(1,DEC_LIST,yylineno,(yyvsp[0].ptr));}
#line 1942 "c_blue.tab.c"
    break;

  case 46:
#line 124 "c_blue.y"
                            {(yyval.ptr)=mknode(2,DEC_LIST,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 1948 "c_blue.tab.c"
    break;

  case 47:
#line 126 "c_blue.y"
                 {(yyval.ptr)=(yyvsp[0].ptr);}
#line 1954 "c_blue.tab.c"
    break;

  case 48:
#line 127 "c_blue.y"
                              {(yyval.ptr)=mknode(2,ASSIGNOP,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"ASSIGNOP");}
#line 1960 "c_blue.tab.c"
    break;

  case 49:
#line 129 "c_blue.y"
                         {(yyval.ptr)=mknode(2,ASSIGNOP,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"ASSIGNOP");}
#line 1966 "c_blue.tab.c"
    break;

  case 50:
#line 130 "c_blue.y"
                      {(yyval.ptr)=mknode(2,AND,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"AND");}
#line 1972 "c_blue.tab.c"
    break;

  case 51:
#line 131 "c_blue.y"
                      {(yyval.ptr)=mknode(2,OR,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"OR");}
#line 1978 "c_blue.tab.c"
    break;

  case 52:
#line 132 "c_blue.y"
                      {(yyval.ptr)=mknode(2,RELOP,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[-1].type_id));}
#line 1984 "c_blue.tab.c"
    break;

  case 53:
#line 133 "c_blue.y"
                     {(yyval.ptr)=mknode(2,ADD,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"ADD");}
#line 1990 "c_blue.tab.c"
    break;

  case 54:
#line 134 "c_blue.y"
                    {(yyval.ptr)=mknode(2,SUB,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"SUB");}
#line 1996 "c_blue.tab.c"
    break;

  case 55:
#line 135 "c_blue.y"
                     {(yyval.ptr)=mknode(2,MUL,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"MUL");}
#line 2002 "c_blue.tab.c"
    break;

  case 56:
#line 136 "c_blue.y"
                      {(yyval.ptr)=mknode(2,DIV,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"DIV");}
#line 2008 "c_blue.tab.c"
    break;

  case 57:
#line 137 "c_blue.y"
                     {(yyval.ptr)=mknode(1,ADDSELF_R,yylineno,(yyvsp[-1].ptr));strcpy((yyval.ptr)->type_id, "AUTO");}
#line 2014 "c_blue.tab.c"
    break;

  case 58:
#line 138 "c_blue.y"
                    {(yyval.ptr)=mknode(1,SUBSELF_R,yylineno,(yyvsp[-1].ptr));strcpy((yyval.ptr)->type_id,"AUTO");}
#line 2020 "c_blue.tab.c"
    break;

  case 59:
#line 139 "c_blue.y"
                     {(yyval.ptr)=mknode(1,ADDSELF_L,yylineno,(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id, "AUTO");}
#line 2026 "c_blue.tab.c"
    break;

  case 60:
#line 140 "c_blue.y"
                    {(yyval.ptr)=mknode(1,SUBSELF_L,yylineno,(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id, "AUTO");}
#line 2032 "c_blue.tab.c"
    break;

  case 61:
#line 141 "c_blue.y"
                      {(yyval.ptr)=(yyvsp[-1].ptr);}
#line 2038 "c_blue.tab.c"
    break;

  case 62:
#line 142 "c_blue.y"
                             {(yyval.ptr)=mknode(1,USUB,yylineno,(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"USUB");}
#line 2044 "c_blue.tab.c"
    break;

  case 63:
#line 143 "c_blue.y"
                      {(yyval.ptr)=mknode(1,NOT,yylineno,(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,"NOT");}
#line 2050 "c_blue.tab.c"
    break;

  case 64:
#line 144 "c_blue.y"
                      {(yyval.ptr)=mknode(1,FUNC_CALL,yylineno,(yyvsp[-1].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[-3].type_id));}
#line 2056 "c_blue.tab.c"
    break;

  case 65:
#line 145 "c_blue.y"
                      {(yyval.ptr)=mknode(0,FUNC_CALL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[-2].type_id));}
#line 2062 "c_blue.tab.c"
    break;

  case 66:
#line 146 "c_blue.y"
                      {(yyval.ptr)=mknode(0,ID,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[0].type_id));}
#line 2068 "c_blue.tab.c"
    break;

  case 67:
#line 147 "c_blue.y"
                      {(yyval.ptr)=mknode(0,INT,yylineno);(yyval.ptr)->type_int=(yyvsp[0].type_int);(yyval.ptr)->type=INT;}
#line 2074 "c_blue.tab.c"
    break;

  case 68:
#line 148 "c_blue.y"
                      {(yyval.ptr)=mknode(0,FLOAT,yylineno);(yyval.ptr)->type_float=(yyvsp[0].type_float);(yyval.ptr)->type=FLOAT;}
#line 2080 "c_blue.tab.c"
    break;

  case 69:
#line 149 "c_blue.y"
                    {(yyval.ptr)=mknode(0,CHAR,yylineno);strcpy((yyval.ptr)->type_string,(yyvsp[0].type_char));(yyval.ptr)->type=CHAR;}
#line 2086 "c_blue.tab.c"
    break;

  case 70:
#line 150 "c_blue.y"
                      {(yyval.ptr)=mknode(1,EXP_ARRAY,yylineno,(yyvsp[0].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[-1].type_id));}
#line 2092 "c_blue.tab.c"
    break;

  case 71:
#line 151 "c_blue.y"
                      {(yyval.ptr)=mknode(1,EXP_ELE,yylineno,(yyvsp[-2].ptr)); strcpy((yyval.ptr)->type_id,(yyvsp[0].type_id));}
#line 2098 "c_blue.tab.c"
    break;

  case 72:
#line 152 "c_blue.y"
        {(yyval.ptr)=NULL;}
#line 2104 "c_blue.tab.c"
    break;

  case 73:
#line 156 "c_blue.y"
                           {(yyval.ptr)=mknode(2,ARGS,yylineno,(yyvsp[-2].ptr),(yyvsp[0].ptr));}
#line 2110 "c_blue.tab.c"
    break;

  case 74:
#line 157 "c_blue.y"
                           {(yyval.ptr)=mknode(1,ARGS,yylineno,(yyvsp[0].ptr));}
#line 2116 "c_blue.tab.c"
    break;


#line 2120 "c_blue.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
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
  return yyresult;
}
#line 160 "c_blue.y"


int main(){
    yylineno=1;
    yyparse();
    return 0;
}

void yyerror(const char* fmt)
{
    printf( "Grammar Error at Line %d Column %d:", yylloc.first_line,yylloc.first_column);
    printf("%s.\n",fmt);
}
