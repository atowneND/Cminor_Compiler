/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_FLYING_TAB_H_INCLUDED
# define YY_YY_FLYING_TAB_H_INCLUDED
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
    TOKEN_ARRAY = 258,
    TOKEN_BOOLEAN = 259,
    TOKEN_CHARACTER = 260,
    TOKEN_ELSE = 261,
    TOKEN_FALSE = 262,
    TOKEN_FOR = 263,
    TOKEN_FCALL = 264,
    TOKEN_IF = 265,
    TOKEN_INTEGER = 266,
    TOKEN_PRINT = 267,
    TOKEN_RETURN = 268,
    TOKEN_STRING = 269,
    TOKEN_TRUE = 270,
    TOKEN_VOID = 271,
    TOKEN_WHILE = 272,
    TOKEN_IDENT = 273,
    TOKEN_INTEGER_LITERAL = 274,
    TOKEN_CHARACTER_LITERAL = 275,
    TOKEN_STRING_LITERAL = 276,
    TOKEN_LBRACK = 277,
    TOKEN_RBRACK = 278,
    TOKEN_LBRACE = 279,
    TOKEN_RBRACE = 280,
    TOKEN_LPAREN = 281,
    TOKEN_RPAREN = 282,
    TOKEN_INC = 283,
    TOKEN_DEC = 284,
    TOKEN_NEG = 285,
    TOKEN_POW = 286,
    TOKEN_MULT = 287,
    TOKEN_DIV = 288,
    TOKEN_MOD = 289,
    TOKEN_ADD = 290,
    TOKEN_LT = 291,
    TOKEN_LE = 292,
    TOKEN_GT = 293,
    TOKEN_GE = 294,
    TOKEN_EQ_COMP = 295,
    TOKEN_NE_COMP = 296,
    TOKEN_AND = 297,
    TOKEN_OR = 298,
    TOKEN_ASSIGN = 299,
    TOKEN_CPP_COMMENT = 300,
    TOKEN_C_COMMENT = 301,
    TOKEN_COMMA = 302,
    TOKEN_COLON = 303,
    TOKEN_SC = 304,
    TOKEN_WS = 305,
    TOKEN_OTHER = 306,
    TOKEN_EOF = 307
  };
#endif
/* Tokens.  */
#define TOKEN_ARRAY 258
#define TOKEN_BOOLEAN 259
#define TOKEN_CHARACTER 260
#define TOKEN_ELSE 261
#define TOKEN_FALSE 262
#define TOKEN_FOR 263
#define TOKEN_FCALL 264
#define TOKEN_IF 265
#define TOKEN_INTEGER 266
#define TOKEN_PRINT 267
#define TOKEN_RETURN 268
#define TOKEN_STRING 269
#define TOKEN_TRUE 270
#define TOKEN_VOID 271
#define TOKEN_WHILE 272
#define TOKEN_IDENT 273
#define TOKEN_INTEGER_LITERAL 274
#define TOKEN_CHARACTER_LITERAL 275
#define TOKEN_STRING_LITERAL 276
#define TOKEN_LBRACK 277
#define TOKEN_RBRACK 278
#define TOKEN_LBRACE 279
#define TOKEN_RBRACE 280
#define TOKEN_LPAREN 281
#define TOKEN_RPAREN 282
#define TOKEN_INC 283
#define TOKEN_DEC 284
#define TOKEN_NEG 285
#define TOKEN_POW 286
#define TOKEN_MULT 287
#define TOKEN_DIV 288
#define TOKEN_MOD 289
#define TOKEN_ADD 290
#define TOKEN_LT 291
#define TOKEN_LE 292
#define TOKEN_GT 293
#define TOKEN_GE 294
#define TOKEN_EQ_COMP 295
#define TOKEN_NE_COMP 296
#define TOKEN_AND 297
#define TOKEN_OR 298
#define TOKEN_ASSIGN 299
#define TOKEN_CPP_COMMENT 300
#define TOKEN_C_COMMENT 301
#define TOKEN_COMMA 302
#define TOKEN_COLON 303
#define TOKEN_SC 304
#define TOKEN_WS 305
#define TOKEN_OTHER 306
#define TOKEN_EOF 307

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_FLYING_TAB_H_INCLUDED  */
