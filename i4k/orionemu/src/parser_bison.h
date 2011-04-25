
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
     NUMBER = 258,
     TAX = 259,
     TBX = 260,
     TCX = 261,
     TDX = 262,
     TSP = 263,
     TBP = 264,
     TSI = 265,
     TDI = 266,
     TIP = 267,
     TEAX = 268,
     TEBX = 269,
     TECX = 270,
     TEDX = 271,
     TESP = 272,
     TEBP = 273,
     TESI = 274,
     TEDI = 275,
     TEIP = 276,
     EOL = 277,
     TPUSH = 278,
     TPOP = 279
   };
#endif
/* Tokens.  */
#define NUMBER 258
#define TAX 259
#define TBX 260
#define TCX 261
#define TDX 262
#define TSP 263
#define TBP 264
#define TSI 265
#define TDI 266
#define TIP 267
#define TEAX 268
#define TEBX 269
#define TECX 270
#define TEDX 271
#define TESP 272
#define TEBP 273
#define TESI 274
#define TEDI 275
#define TEIP 276
#define EOL 277
#define TPUSH 278
#define TPOP 279




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 15 "parser_bison.y"

  struct ast *a;
  struct opcode *op;
  int reg;
  int n;



/* Line 1676 of yacc.c  */
#line 109 "parser_bison.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


