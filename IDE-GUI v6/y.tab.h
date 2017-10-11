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
    ESCRIBIR = 271,
    MAZE = 272,
    INI_LOOP = 273,
    FIN_LOOP = 274,
    INI_FOR = 275,
    FIN_FOR = 276,
    IN = 277,
    STEP = 278,
    EXIT = 279,
    TIMES = 280,
    INI_IF = 281,
    FIN_IF = 282,
    ELSE = 283,
    ELSE_IF = 284,
    THEN = 285,
    DECLARAR_PROCEDIMIENTO = 286,
    INI_PROCEDIMIENTO = 287,
    FIN_PROCEDIMIENTO = 288,
    IGUAL = 289,
    TIEMPO = 290,
    BOTON = 291,
    VTIEMPO = 292,
    PUNTO_COMA = 293,
    CALL = 294,
    PARENTESIS_A = 295,
    PARENTESIS_C = 296,
    COMA = 297,
    NOMBRE = 298
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
#define ESCRIBIR 271
#define MAZE 272
#define INI_LOOP 273
#define FIN_LOOP 274
#define INI_FOR 275
#define FIN_FOR 276
#define IN 277
#define STEP 278
#define EXIT 279
#define TIMES 280
#define INI_IF 281
#define FIN_IF 282
#define ELSE 283
#define ELSE_IF 284
#define THEN 285
#define DECLARAR_PROCEDIMIENTO 286
#define INI_PROCEDIMIENTO 287
#define FIN_PROCEDIMIENTO 288
#define IGUAL 289
#define TIEMPO 290
#define BOTON 291
#define VTIEMPO 292
#define PUNTO_COMA 293
#define CALL 294
#define PARENTESIS_A 295
#define PARENTESIS_C 296
#define COMA 297
#define NOMBRE 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
