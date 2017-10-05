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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    DEFINIR = 258,
    INCREMENTO = 259,
    DECREMENTO = 260,
    INI_VARIABLE = 261,
    VARIABLE = 262,
    COMENTARIO_I = 263,
    COMENTARIO_F = 264,
    ENCENDER_TODOS = 265,
    APAGAR_TODOS = 266,
    ENCENDER = 267,
    APAGAR = 268,
    ENCENDER_SONIDO = 269,
    APAGAR_SONIDO = 270,
    INI_LOOP = 271,
    FIN_LOOP = 272,
    INI_FOR = 273,
    FIN_FOR = 274,
    IN = 275,
    STEP = 276,
    EXIT = 277,
    TIMES = 278,
    INI_IF = 279,
    FIN_IF = 280,
    ELSE = 281,
    ELSE_IF = 282,
    THEN = 283,
    DECLARAR_PROCEDIMIENTO = 284,
    INI_PROCEDIMIENTO = 285,
    FIN_PROCEDIMIENTO = 286,
    IGUAL = 287,
    TIEMPO = 288,
    BOTON = 289,
    VTIEMPO = 290,
    PUNTO_COMA = 291,
    CALL = 292,
    PARENTESIS_A = 293,
    PARENTESIS_C = 294,
    COMA = 295,
    NOMBRE = 296
  };
#endif
/* Tokens.  */
#define DEFINIR 258
#define INCREMENTO 259
#define DECREMENTO 260
#define INI_VARIABLE 261
#define VARIABLE 262
#define COMENTARIO_I 263
#define COMENTARIO_F 264
#define ENCENDER_TODOS 265
#define APAGAR_TODOS 266
#define ENCENDER 267
#define APAGAR 268
#define ENCENDER_SONIDO 269
#define APAGAR_SONIDO 270
#define INI_LOOP 271
#define FIN_LOOP 272
#define INI_FOR 273
#define FIN_FOR 274
#define IN 275
#define STEP 276
#define EXIT 277
#define TIMES 278
#define INI_IF 279
#define FIN_IF 280
#define ELSE 281
#define ELSE_IF 282
#define THEN 283
#define DECLARAR_PROCEDIMIENTO 284
#define INI_PROCEDIMIENTO 285
#define FIN_PROCEDIMIENTO 286
#define IGUAL 287
#define TIEMPO 288
#define BOTON 289
#define VTIEMPO 290
#define PUNTO_COMA 291
#define CALL 292
#define PARENTESIS_A 293
#define PARENTESIS_C 294
#define COMA 295
#define NOMBRE 296

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
