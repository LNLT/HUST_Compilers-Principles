/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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

#line 154 "c_blue.tab.h"

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
