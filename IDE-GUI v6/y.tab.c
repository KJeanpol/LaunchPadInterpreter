/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 15 "y.y" /* yacc.c:339  */

#include<stdio.h>
    //#include <iostream>
    #include <stdlib.h>
    #include <string>
    #include "lex.yy.c"
    #include "logic/Block.h"
    #include "logic/ArduinoSentence.h"
    #include "logic/Dow.h"
    #include "logic/ForTimes.h"
    #include "logic/Var.h"
    #include "logic/If.h"
    #include "logic/Decrease.h"
    #include "logic/Increase.h"
    #include "mainwindow.h"
    #include <fstream>


    //______________________________________________________________________//
    using namespace std;
    extern int yylineno;
    int yyerror(const char* s );
    long block = 0;
    std::vector<Block *> BlockList;
    std::vector<Var *> Locals;
    std::vector<Var *> Global;
    std::vector<string> ProcI;
    string LastVar;
    int juego=1;
    int ifval=1;
    MainWindow* MIDE;

//------------------------------------------------------------------------//
void addParam(string pname, string ptype){
    Block* tmp= BlockList.back();
    while(tmp->hasBlock()){
        tmp=tmp->sentences.back();
    }tmp->setParams(pname, ptype);


}

//______________________________________________________________________//


bool ins(string pname, int pvalue){
    Block* tmp= BlockList.back();
    while(tmp->hasBlock()){
        if(tmp->exist(pname)){
            tmp->setVal(pname, pvalue);
            tmp->getVar(pname);
            return true;}else{
            tmp=tmp->sentences.back();}
    } if(tmp->exist(pname)){
        tmp->setVal(pname, pvalue);
        return true;}else{cout<<"NO EXISTE"<<endl;return false;}
}

//______________________________________________________________________//
    bool cmp(string proc){
            cout<<"-----"<<BlockList.back()->sentences.size()<<endl;
            for(int i=0;i<BlockList.back()->sentences.size();i++){
                cout<<"Sentencia: "<< i<<BlockList.back()->sentences[i]->getName();
                if(BlockList.back()->sentences[i]->getName().compare(proc)==0){
                    BlockList.back()->sentences[i]->execute();
                    return true;
                }
            }return false;
}


        //______________________________________________________________________//
        void ejecutar(string pname){
            for(int i=0;i!=BlockList.back()->sentences.size();i++){
                if(BlockList.back()->sentences[i]->getName().compare(pname)){
                    BlockList.back()->sentences[i]->execute();
                    return;
                }
                MIDE->console("ERROR: El metodo no existe");
            }printf("ERROR: El metodo no existe");

        }
        //______________________________________________________________________//
                void addGlobals(){
                    for(int i=0;i!=Global.size();i++){
                        BlockList.back()->Variables.push_back(Global[i]);
                        cout<<"Anadiendo "<<Global[i]->getName()<<endl;
                    }
                    for(int i=0;i!=BlockList.back()->Variables.size();i++){
                        cout<<"Tenemos "<<BlockList.back()->Variables[i]->getName()<<endl;
                    }
                }
        //______________________________________________________________________//
          void addVariables(){
             Block* tmp= BlockList.back();
               while(tmp->hasBlock()){
                 tmp=tmp->sentences.back();
               } for(int i=0;i!=Locals.size();i++){
                    tmp->addVars(Locals[i]);


                 }


          }
    void setincremento(string pvar){
        Block* tmp= BlockList.back();
        while(tmp->hasBlock()){
            tmp=tmp->sentences.back();
        } tmp->setVarInc(pvar);

        }
    void setdecremento(string pvar){
        Block* tmp= BlockList.back();
        while(tmp->hasBlock()){
            tmp=tmp->sentences.back();
        } tmp->setVarDec(pvar);

    }
       //_______________________________________________________________________//
           void insertarFondo(Block *pblock){
               Block* tmp= BlockList.back();
               while(tmp->hasBlock()){
                    if(tmp->getName().compare("If")!=0 && tmp->getName().compare("Dow")!=0){
                        tmp=tmp->sentences.back();
                    }else{
                        tmp->addSentence(pblock);
                        tmp->sentences.back()->setIDS(MIDE);
                        return;
                    }

               }tmp->addSentence(pblock); tmp->sentences.back()->setIDS(MIDE);
           }
           void insertarBloque(Block *pblock){
               Block* tmp= BlockList.back();
               while(tmp->hasBlock()){
                    if(tmp->sentences.back()->getName().compare("If")!=0 && tmp->sentences.back()->getName().compare("Dow")!=0){
                        tmp=tmp->sentences.back();
                    }else{
                        tmp->addSentence(pblock);
                        tmp->sentences.back()->setIDS(MIDE);
                        return;
                    }

               }tmp->addSentence(pblock); tmp->sentences.back()->setIDS(MIDE);
           }


           void setNames(string pname){
                          Block* tmp= BlockList.back();
                          while(tmp->hasBlock()){
                               tmp=tmp->sentences.back();
                          }tmp->setName(pname);
                      }
           void setifs(int ppar){
                          Block* tmp= BlockList.back();
                          while(tmp->hasBlock()){
                               tmp=tmp->sentences.back();
                          }tmp->setIf(ppar);
                      }

        //_______________________________________________________________________//
        void addLeftIf(string pval){
            Block* tmp= BlockList.back();
            while(tmp->hasBlock()){
                tmp=tmp->sentences.back();
            }tmp->setVal1(pval);
        }


        void addRightIf(int pval){
            Block* tmp= BlockList.back();
            while(tmp->hasBlock()){
               tmp=tmp->sentences.back();
                }tmp->setVal2(pval);
        }
void setValor1(int pval){
    Block* tmp= BlockList.back();
    while(tmp->hasBlock()){
        tmp=tmp->sentences.back();
    }tmp->setValor1(pval);
}
void setValor2(int pval){
    Block* tmp= BlockList.back();
    while(tmp->hasBlock()){
        tmp=tmp->sentences.back();
    }tmp->setValor2(pval);
}
void palabra(string ppal){
    Block* tmp= BlockList.back();
    while(tmp->hasBlock()){
        tmp=tmp->sentences.back();
    }tmp->palabra = ppal;
}

int vval(string pname){
    Block* tmp= BlockList.back();
    while(tmp->hasBlock()){
        tmp->getVar(pname);
        tmp=tmp->sentences.back();
    }tmp->getVar(pname);
}

void exits(){
    Block* tmp= BlockList.back();
    while(tmp->hasBlock()){
        tmp=tmp->sentences.back();
    }tmp->setExit(true);
}
void process(string pname){
    ProcI.push_back(pname);
}

void setGame(){
    if(BlockList.back()->sentences.back()->name.find("2")<BlockList.back()->sentences.back()->name.size()){
        BlockList.back()->sentences.back()->setjuego(2);
    }else if(BlockList.back()->sentences.back()->name.find("3")<BlockList.back()->sentences.back()->name.size()){
        BlockList.back()->sentences.back()->setjuego(3);
    }else if(BlockList.back()->sentences.back()->name.find("4")<BlockList.back()->sentences.back()->name.size()){
        BlockList.back()->sentences.back()->setjuego(4);
    }else{
        BlockList.back()->sentences.back()->setjuego(1);
    }
}



int interprete(MainWindow *IDE){
   ifstream ifs("/home/joserivera/Downloads/LaunchPadInterpreter-master/IDE-GUI v6/test.txt");
                string content( (istreambuf_iterator<char>(ifs) ),
                                 (istreambuf_iterator<char>()    ) );
                ifs.close();
                yy_scan_string(content.c_str());
//                IDE->sendMessage("AAA");
                MIDE=IDE;
                yyparse();
                return 0;
}

//void send(const QString &message){

//}



#line 312 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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

/* Copy the second part of user declarations.  */

#line 449 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   210

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  64
/* YYNRULES -- Number of rules.  */
#define YYNRULES  87
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  212

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   321,   321,   321,   321,   323,   323,   323,   325,   325,
     325,   327,   328,   330,   330,   331,   333,   335,   335,   336,
     336,   339,   339,   339,   341,   342,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   359,
     359,   360,   360,   363,   363,   364,   364,   366,   366,   368,
     368,   370,   370,   370,   372,   372,   374,   374,   375,   377,
     377,   377,   377,   377,   380,   380,   382,   382,   382,   382,
     382,   382,   385,   385,   385,   386,   388,   388,   389,   391,
     391,   391,   391,   396,   398,   399,   401,   401
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DEFINIR", "INCREMENTO", "DECREMENTO",
  "INI_VARIABLE", "VARIABLE", "COMENTARIO_I", "COMENTARIO_F",
  "ENCENDER_TODOS", "APAGAR_TODOS", "ENCENDER", "APAGAR",
  "ENCENDER_SONIDO", "APAGAR_SONIDO", "ESCRIBIR", "MAZE", "INI_LOOP",
  "FIN_LOOP", "INI_FOR", "FIN_FOR", "IN", "STEP", "EXIT", "TIMES",
  "INI_IF", "FIN_IF", "ELSE", "ELSE_IF", "THEN", "DECLARAR_PROCEDIMIENTO",
  "INI_PROCEDIMIENTO", "FIN_PROCEDIMIENTO", "IGUAL", "TIEMPO", "BOTON",
  "VTIEMPO", "PUNTO_COMA", "CALL", "PARENTESIS_A", "PARENTESIS_C", "COMA",
  "NOMBRE", "$accept", "PRINCIPIO", "$@1", "$@2", "DEFINIR_VAR", "$@3",
  "$@4", "DEFINIR_LOCAL", "$@5", "$@6", "COMENTARIO", "HOJA_D", "$@7",
  "EPSILON", "MODIFICAR_VAR", "$@8", "$@9", "INSTANCIAR_VAR", "$@10",
  "$@11", "EXPRESION", "EXPRESION_SIMPLE", "TURNON", "$@12", "$@13",
  "TURNOFF", "$@14", "$@15", "SOUNDON", "$@16", "SOUNDOFF", "$@17",
  "WRITE", "$@18", "$@19", "MAZEE", "$@20", "EXITS", "$@21", "DOW_LOOP",
  "$@22", "$@23", "$@24", "$@25", "FOR_LOOP", "$@26", "IF_SENTENCIA",
  "$@27", "$@28", "$@29", "$@30", "$@31", "ELSEIF", "$@32", "$@33",
  "ELSEFIN", "$@34", "PROCEDIMIENTO", "$@35", "$@36", "$@37", "PARAMETRO",
  "INVOKE_PROCEDIMIENTO", "$@38", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298
};
# endif

#define YYPACT_NINF -152

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-152)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -2,   -34,    10,  -152,  -152,     2,  -152,     9,    -2,     6,
    -152,  -152,  -152,  -152,  -152,     9,   -17,   -12,  -152,    19,
    -152,    92,  -152,  -152,    20,    21,    22,  -152,  -152,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,    24,    -5,  -152,    25,
    -152,  -152,  -152,  -152,  -152,    11,  -152,  -152,  -152,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,    -1,     1,  -152,  -152,
    -152,     3,     7,     8,    12,    13,    18,    23,    26,    27,
    -152,  -152,  -152,  -152,    31,  -152,  -152,  -152,    92,  -152,
      92,    35,    36,    15,  -152,    -5,    -5,    -5,    -5,    -5,
      -5,    -5,    -5,    28,    17,  -152,     5,    30,  -152,  -152,
      32,    33,    -5,    34,     4,    37,    42,    43,    46,    48,
    -152,    49,    -5,    92,    40,  -152,  -152,    29,  -152,  -152,
    -152,  -152,    -5,    -5,    -5,    -5,    38,    39,    50,    -5,
    -152,    41,    -5,    44,    52,    51,    58,    71,    73,  -152,
    -152,    -5,    76,    55,    81,  -152,  -152,  -152,    -5,    -5,
      -5,    -5,    78,    83,    -5,  -152,    45,    89,    82,    84,
      85,    88,    -5,  -152,  -152,    92,   -17,    86,    95,    -5,
      96,    94,    92,  -152,  -152,  -152,  -152,    97,  -152,    -5,
     107,   -24,    -5,    99,  -152,  -152,    62,  -152,   103,  -152,
     100,   105,   106,    92,  -152,  -152,    -5,  -152,  -152,  -152,
     104,   108,   109,    -5,  -152,   110,  -152,  -152,   111,    92,
     -24,  -152
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      16,     0,     0,     2,    12,     0,     1,    16,    16,     0,
      13,     3,    15,    11,     5,    16,    16,     0,    14,     0,
      83,    16,     6,    79,     0,     0,     0,     8,    41,    43,
      39,    45,    47,    49,    51,    54,     0,     0,    66,     0,
      27,    25,    37,    31,     4,    16,    26,    28,    29,    30,
      34,    35,    32,    33,    36,    38,     0,     0,    17,    19,
      21,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      59,    84,    85,    64,     0,    86,    56,    58,    16,     7,
      16,     0,     0,     0,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    67,     0,     0,    24,    80,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      52,     0,     0,    16,     0,    87,    57,     0,    18,    20,
      22,    10,     0,     0,     0,     0,     0,     0,     0,     0,
      60,     0,     0,     0,     0,     0,     0,     0,     0,    48,
      50,     0,     0,     0,     0,    68,    81,    23,     0,     0,
       0,     0,     0,     0,     0,    65,     0,     0,     0,     0,
       0,     0,     0,    55,    61,    16,    16,     0,     0,     0,
       0,     0,    16,    69,    82,    42,    44,     0,    46,     0,
       0,    16,     0,     0,    62,    76,     0,    78,     0,    75,
       0,     0,     0,    16,    72,    70,     0,    53,    63,    77,
       0,     0,     0,     0,    71,     0,    73,    40,     0,    16,
      16,    74
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,
      57,   122,  -152,     0,  -152,  -152,  -152,  -152,  -152,  -152,
     -77,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,
    -152,  -152,  -151,  -152,  -152,  -152,  -152,   -25,  -152,  -152,
    -152,   -68,  -152,  -152
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     7,    16,    10,    17,    56,    40,    61,   103,
       3,    11,    15,    41,    42,    81,    82,    43,    83,   134,
      44,    45,    46,    64,    62,    47,    63,    65,    48,    66,
      49,    67,    50,    68,   128,    51,    69,    78,    97,    52,
      93,   143,   172,   192,    53,    94,    54,    74,   114,   156,
     181,   201,   188,   200,   208,   189,   193,    21,    57,   117,
     157,    73,    55,    96
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       4,    98,    71,    99,   185,   186,     1,    12,     4,     5,
       6,     8,     9,    14,    19,    12,    20,   104,   105,   106,
     107,   108,   109,   110,   111,    22,    23,    58,    59,    60,
      72,    70,    75,    80,   120,    76,   131,    79,    95,   100,
      84,   101,   113,   115,   130,    77,   122,    85,    86,   102,
     112,   146,    87,    88,   135,   136,   137,   138,    89,   211,
     133,   142,   144,    90,   145,    13,    91,    92,   116,   194,
     118,   119,   121,   152,   132,   165,   139,   140,   154,   123,
     158,   159,   160,   161,   124,   125,   164,   126,   173,   127,
     147,   129,   141,   148,   171,   180,    24,    25,    26,    27,
     149,   177,    28,    29,    30,    31,    32,    33,    34,    35,
      36,   183,    37,   150,   190,   151,   199,   153,    38,   155,
     162,   163,   166,   167,   175,   168,   184,   169,   202,   170,
     195,    39,   210,   176,   178,   206,   179,    18,   203,   182,
     191,   174,   196,   197,   198,     0,   204,     0,   207,   209,
     205,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    20,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   187,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     187
};

static const yytype_int16 yycheck[] =
{
       0,    78,     7,    80,    28,    29,     8,     7,     8,    43,
       0,     9,     3,     7,    31,    15,    16,    85,    86,    87,
      88,    89,    90,    91,    92,    37,     7,     7,     7,     7,
      35,     7,     7,    32,   102,    24,   113,    38,     7,     4,
      37,     5,    25,    38,   112,    45,    42,    40,    40,    34,
      22,     7,    40,    40,   122,   123,   124,   125,    40,   210,
      31,   129,    21,    40,   132,     8,    40,    40,    38,     7,
      38,    38,    38,   141,    34,    30,    38,    38,    23,    42,
     148,   149,   150,   151,    42,    42,   154,    41,   165,    41,
      38,    42,    42,    42,   162,   172,     4,     5,     6,     7,
      42,   169,    10,    11,    12,    13,    14,    15,    16,    17,
      18,   179,    20,    42,   182,    42,   193,    41,    26,    38,
      42,    38,    33,    41,    38,    41,    19,    42,   196,    41,
      27,    39,   209,    38,    38,   203,    42,    15,    34,    42,
      41,   166,    42,    38,    38,    -1,    38,    -1,    38,    38,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   166,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   181,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     210
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    45,    54,    57,    43,     0,    46,     9,     3,
      48,    55,    57,    54,     7,    56,    47,    49,    55,    31,
      57,   101,    37,     7,     4,     5,     6,     7,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    20,    26,    39,
      51,    57,    58,    61,    64,    65,    66,    69,    72,    74,
      76,    79,    83,    88,    90,   106,    50,   102,     7,     7,
       7,    52,    68,    70,    67,    71,    73,    75,    77,    80,
       7,     7,    35,   105,    91,     7,    24,    57,    81,    38,
      32,    59,    60,    62,    37,    40,    40,    40,    40,    40,
      40,    40,    40,    84,    89,     7,   107,    82,    64,    64,
       4,     5,    34,    53,   105,   105,   105,   105,   105,   105,
     105,   105,    22,    25,    92,    38,    38,   103,    38,    38,
     105,    38,    42,    42,    42,    42,    41,    41,    78,    42,
     105,    64,    34,    31,    63,   105,   105,   105,   105,    38,
      38,    42,   105,    85,    21,   105,     7,    38,    42,    42,
      42,    42,   105,    41,    23,    38,    93,   104,   105,   105,
     105,   105,    42,    38,   105,    30,    33,    41,    41,    42,
      41,   105,    86,    64,   101,    38,    38,   105,    38,    42,
      64,    94,    42,   105,    19,    28,    29,    57,    96,    99,
     105,    41,    87,   100,     7,    27,    42,    38,    38,    64,
      97,    95,   105,    34,    38,    41,   105,    38,    98,    38,
      64,    96
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    46,    47,    45,    49,    50,    48,    52,    53,
      51,    54,    54,    56,    55,    55,    57,    59,    58,    60,
      58,    62,    63,    61,    64,    64,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    67,
      66,    68,    66,    70,    69,    71,    69,    73,    72,    75,
      74,    77,    78,    76,    80,    79,    82,    81,    81,    84,
      85,    86,    87,    83,    89,    88,    91,    92,    93,    94,
      95,    90,    97,    98,    96,    96,   100,    99,    99,   102,
     103,   104,   101,   101,   105,   105,   107,   106
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     6,     0,     0,     6,     0,     0,
       5,     4,     1,     0,     3,     1,     0,     0,     5,     0,
       5,     0,     0,     7,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
      16,     0,    10,     0,    10,     0,    10,     0,     6,     0,
       6,     0,     0,    13,     0,     8,     0,     3,     1,     0,
       0,     0,     0,    13,     0,     7,     0,     0,     0,     0,
       0,    14,     0,     0,     9,     1,     0,     3,     1,     0,
       0,     0,    11,     1,     1,     1,     0,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 321 "y.y" /* yacc.c:1646  */
    {BlockList.push_back(new Block());BlockList.back()->setIDS(MIDE);}
#line 1679 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 321 "y.y" /* yacc.c:1646  */
    {addGlobals();setNames("Block");Global.clear();}
#line 1685 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 323 "y.y" /* yacc.c:1646  */
    {Global.push_back(new Var(yytext)); cout<<yytext;}
#line 1691 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 323 "y.y" /* yacc.c:1646  */
    {Global.back()->setType(yytext);}
#line 1697 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 325 "y.y" /* yacc.c:1646  */
    {Locals.push_back(new Var(yytext));}
#line 1703 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 325 "y.y" /* yacc.c:1646  */
    {Locals.back()->setType(yytext);}
#line 1709 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 330 "y.y" /* yacc.c:1646  */
    {}
#line 1715 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 335 "y.y" /* yacc.c:1646  */
    {insertarFondo((new Increase()));setNames("Incremento");setincremento(yytext); }
#line 1721 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 336 "y.y" /* yacc.c:1646  */
    {insertarFondo((new Decrease()));setNames("Decremento");setdecremento(yytext);}
#line 1727 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 339 "y.y" /* yacc.c:1646  */
    {LastVar=yytext;}
#line 1733 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 339 "y.y" /* yacc.c:1646  */
    { ins(LastVar,atoi(yytext));}
#line 1739 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 359 "y.y" /* yacc.c:1646  */
    {insertarFondo(new ArduinoSentence());setNames("TurnOn");setifs(ifval);}
#line 1745 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 360 "y.y" /* yacc.c:1646  */
    {insertarFondo(new ArduinoSentence());setNames("TurnON");setifs(ifval);}
#line 1751 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 363 "y.y" /* yacc.c:1646  */
    {insertarFondo(new ArduinoSentence());setNames("TurnOFF");setifs(ifval);}
#line 1757 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 364 "y.y" /* yacc.c:1646  */
    {insertarFondo(new ArduinoSentence());setNames("TurnOff");setifs(ifval);}
#line 1763 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 366 "y.y" /* yacc.c:1646  */
    {insertarFondo(new ArduinoSentence());setNames("SoundOn");setifs(ifval);}
#line 1769 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 368 "y.y" /* yacc.c:1646  */
    {insertarFondo(new ArduinoSentence());setNames("SoundOff");setifs(ifval);}
#line 1775 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 370 "y.y" /* yacc.c:1646  */
    {insertarFondo(new ArduinoSentence());setNames("Write");setifs(ifval);}
#line 1781 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 370 "y.y" /* yacc.c:1646  */
    {palabra(yytext);}
#line 1787 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 372 "y.y" /* yacc.c:1646  */
    {insertarFondo(new ArduinoSentence());setNames("Maze");setifs(ifval);}
#line 1793 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 374 "y.y" /* yacc.c:1646  */
    {exits();}
#line 1799 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 377 "y.y" /* yacc.c:1646  */
    {insertarFondo((new Dow(yytext)));setNames("Dow");setifs(ifval);}
#line 1805 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 377 "y.y" /* yacc.c:1646  */
    {setValor1(atoi(yytext));}
#line 1811 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 377 "y.y" /* yacc.c:1646  */
    {setValor2(atoi(yytext));}
#line 1817 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 377 "y.y" /* yacc.c:1646  */
    {insertarBloque(new Block());}
#line 1823 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 380 "y.y" /* yacc.c:1646  */
    {insertarFondo((new ForTimes(atoi(yytext))));setNames("For");setifs(ifval);}
#line 1829 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 382 "y.y" /* yacc.c:1646  */
    {insertarFondo((new If())); setNames(yytext);}
#line 1835 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 382 "y.y" /* yacc.c:1646  */
    {addLeftIf(yytext);}
#line 1841 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 382 "y.y" /* yacc.c:1646  */
    {addRightIf(atoi(yytext));}
#line 1847 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 382 "y.y" /* yacc.c:1646  */
    {ifval+=1;}
#line 1853 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 382 "y.y" /* yacc.c:1646  */
    {insertarBloque(new Block());}
#line 1859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 385 "y.y" /* yacc.c:1646  */
    {addLeftIf(yytext);}
#line 1865 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 385 "y.y" /* yacc.c:1646  */
    {addRightIf(atoi(yytext));}
#line 1871 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 385 "y.y" /* yacc.c:1646  */
    {ifval+=1;}
#line 1877 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 388 "y.y" /* yacc.c:1646  */
    {ifval=0;}
#line 1883 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 391 "y.y" /* yacc.c:1646  */
    {BlockList.back()->addSentence(new Block()); BlockList.back()->sentences.back()->setName(yytext); setGame();process(yytext);}
#line 1889 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 391 "y.y" /* yacc.c:1646  */
    {addVariables(); Locals.clear();}
#line 1895 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 391 "y.y" /* yacc.c:1646  */
    {if(ProcI.back().compare(yytext)!=0){QString err = QString::fromStdString(yytext);
        QString num= QString::number(yylineno);
        QString error= "Syntax error "+err +" line: " + num;
        MIDE->console(error);
        return 0;};}
#line 1905 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 398 "y.y" /* yacc.c:1646  */
    {addParam(yytext,"var");}
#line 1911 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 399 "y.y" /* yacc.c:1646  */
    {addParam(yytext,"num");}
#line 1917 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 401 "y.y" /* yacc.c:1646  */
    {printf(yytext);if(cmp(yytext))printf("SI");}
#line 1923 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1927 "y.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 403 "y.y" /* yacc.c:1906  */

int yyerror(const char* s ) {
    //yyerrok;
    //cout<<yytext<<endl;
    //fprintf(stderr,"%s: %s at line %d\n", s, yytext,yylineno);
    std::cout<<"Error de sintaxis en linea: "<<yylineno;
    yyclearin;
    QString err = QString::fromStdString(yytext);
    QString num= QString::number(yylineno);
    QString error= "Syntax error "+err +" line: " + num;
    MIDE->console(error);
    yylineno=1;

    return 0;
}
