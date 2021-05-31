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
    INT = 258,
    FLOAT = 259,
    CHAR = 260,
    RELOP = 261,
    ID = 262,
    TYPE = 263,
    STRUCT = 264,
    RETURN = 265,
    IF = 266,
    ELSE = 267,
    WHILE = 268,
    VOID = 269,
    BREAK = 270,
    CONTINUE = 271,
    WRITE = 272,
    READ = 273,
    LP = 274,
    RP = 275,
    LB = 276,
    RB = 277,
    DOT = 278,
    ADDSELF = 279,
    SUBSELF = 280,
    NOT = 281,
    MUL = 282,
    DIV = 283,
    SUB = 284,
    ADD = 285,
    AND = 286,
    OR = 287,
    ASSIGNOP = 288,
    COMMA = 289,
    SEMI = 290,
    LC = 291,
    RC = 292,
    EXT_DEF_LIST = 293,
    EXT_VAR_DEF = 294,
    EXT_STRUCT_DEF = 295,
    FUNC_DEF = 296,
    VOID_FUNC_DEF = 297,
    EXT_DEC_LIST = 298,
    FUNC_DEC = 299,
    STRUCT_DEF = 300,
    STRUCT_DEC = 301,
    PARAM_LIST = 302,
    PARAM_DEC = 303,
    ARRAY_DEC = 304,
    COMP_STM = 305,
    STM_LIST = 306,
    EXP_STMT = 307,
    IF_THEN = 308,
    IF_THEN_ELSE = 309,
    DEF_LIST = 310,
    VAR_DEF = 311,
    DEC_LIST = 312,
    DEC_LISTS = 313,
    ARGS = 314,
    VARLIST = 315,
    EXP_ELE = 316,
    FUNC_CALL = 317,
    EXP_ARRAY = 318,
    FUNCTION = 319,
    PARAM = 320,
    ARG = 321,
    CALL = 322,
    LABEL = 323,
    GOTO = 324,
    JLT = 325,
    JLE = 326,
    JGT = 327,
    JGE = 328,
    EQ = 329,
    NEQ = 330,
    USUB = 331,
    LOWER_THEN_ELSE = 332
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "c_blue.y"

	int type_int;
	float type_float;
        char type_char[32];
	char type_id[32];
	struct Node *ptr;

#line 143 "c_blue.tab.h"

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
