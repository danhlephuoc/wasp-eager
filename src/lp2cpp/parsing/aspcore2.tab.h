/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_ASPCORE2_TAB_H_INCLUDED
# define YY_YY_ASPCORE2_TAB_H_INCLUDED
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
    SYMBOLIC_CONSTANT = 258,
    NUMBER = 259,
    VARIABLE = 260,
    STRING = 261,
    DIRECTIVE_NAME = 262,
    DIRECTIVE_VALUE = 263,
    AGGR_COUNT = 264,
    AGGR_MAX = 265,
    AGGR_MIN = 266,
    AGGR_SUM = 267,
    ERROR = 268,
    NEWLINE = 269,
    DOT = 270,
    DDOT = 271,
    SEMICOLON = 272,
    COLON = 273,
    CONS = 274,
    QUERY_MARK = 275,
    PLUS = 276,
    TIMES = 277,
    SLASH = 278,
    ANON_VAR = 279,
    PARAM_OPEN = 280,
    PARAM_CLOSE = 281,
    SQUARE_OPEN = 282,
    SQUARE_CLOSE = 283,
    CURLY_OPEN = 284,
    CURLY_CLOSE = 285,
    EQUAL = 286,
    UNEQUAL = 287,
    LESS = 288,
    GREATER = 289,
    LESS_OR_EQ = 290,
    GREATER_OR_EQ = 291,
    DASH = 292,
    COMMA = 293,
    NAF = 294,
    AT = 295,
    WCONS = 296,
    VEL = 297,
    EXISTS = 298
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 29 "DLV2libs/input/aspcore2.y" /* yacc.c:1909  */

    char* string;
    char single_char;
    int integer;

#line 104 "aspcore2.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (DLV2::InputDirector& director);

#endif /* !YY_YY_ASPCORE2_TAB_H_INCLUDED  */
