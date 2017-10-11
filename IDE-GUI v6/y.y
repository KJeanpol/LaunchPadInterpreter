/*
%{
    #include<stdio.h>
    #include <iostream>
    #include "lex.yy.c"
    #include "../Logic/Procedimiento.h"
    Procedimiento *miProce;
    void setProcedimiento(Procedimiento * p){miProce = p;}
    extern int yylineno;
    int yyerror(const char* s );
    using namespace std;
%}
*/

%{
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
                if(tmp->getName().compare("If")!=0){
                    tmp=tmp->sentences.back();
                }else{tmp->setVal1(pval);return;}
            }tmp->setVal1(pval);
        }


        void addRightIf(int pval){
            Block* tmp= BlockList.back();
            while(tmp->hasBlock()){
                if(tmp->getName().compare("If")!=0){
                    tmp=tmp->sentences.back();
                }else{tmp->setVal2(pval);return;}

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


%}

/*------------TOKEN DE MANEJO DE VARIABLES-------*/
%token DEFINIR
%token INCREMENTO
%token DECREMENTO
%token INI_VARIABLE
%token VARIABLE

/*------------TOKEN DE COMENTARIOS-------*/
%token COMENTARIO_I
%token COMENTARIO_F

/*------------TOKEN DE MANEJO DE METODOS DEL ARDUINO-------*/
%token ENCENDER_TODOS
%token APAGAR_TODOS
%token ENCENDER
%token APAGAR
%token ENCENDER_SONIDO
%token APAGAR_SONIDO
%token ESCRIBIR
%token MAZE

/*------------TOKEN DE LOOP-------*/
%token INI_LOOP
%token FIN_LOOP
%token INI_FOR
%token FIN_FOR
%token IN
%token STEP
%token EXIT
%token TIMES
/*------------TOKEN DE SENTENCIA IF-------*/
%token INI_IF
%token FIN_IF
%token ELSE
%token ELSE_IF
%token THEN


/*------------TOKEN DE PROCEDIMIENTOS-------*/
%token DECLARAR_PROCEDIMIENTO
%token INI_PROCEDIMIENTO
%token FIN_PROCEDIMIENTO
%token IGUAL

/*------------TOKENS VARIOS-------*/
%token TIEMPO
%token BOTON
%token VTIEMPO
%token PUNTO_COMA
%token CALL
%token PARENTESIS_A
%token PARENTESIS_C
%token COMA
%token NOMBRE


%start PRINCIPIO

%%

    PRINCIPIO: COMENTARIO{BlockList.push_back(new Block());BlockList.back()->setIDS(MIDE);} HOJA_D{addGlobals();setNames("Block");Global.clear();} PROCEDIMIENTO EXPRESION;

    DEFINIR_VAR: DEFINIR VARIABLE{Global.push_back(new Var(yytext)); cout<<yytext;} VTIEMPO {Global.back()->setType(yytext);} PUNTO_COMA;

    DEFINIR_LOCAL: VARIABLE{Locals.push_back(new Var(yytext));} VTIEMPO {Locals.back()->setType(yytext);} PUNTO_COMA;

    COMENTARIO: COMENTARIO_I NOMBRE COMENTARIO_F COMENTARIO
              | EPSILON;

    HOJA_D: DEFINIR_VAR{} HOJA_D
          | EPSILON;

    EPSILON: ;

    MODIFICAR_VAR: INCREMENTO VARIABLE{insertarFondo((new Increase()));setNames("Incremento");setincremento(yytext); } INCREMENTO PUNTO_COMA
                 | DECREMENTO VARIABLE{insertarFondo((new Decrease()));setNames("Decremento");setdecremento(yytext);} DECREMENTO PUNTO_COMA;


    INSTANCIAR_VAR: INI_VARIABLE VARIABLE{LastVar=yytext;} IGUAL PARAMETRO{ ins(LastVar,atoi(yytext));} PUNTO_COMA;

    EXPRESION: EXPRESION_SIMPLE EXITS EXPRESION
             |	EPSILON;

    EXPRESION_SIMPLE: TURNON
             |DEFINIR_LOCAL
             | TURNOFF
             | SOUNDON
             | SOUNDOFF
             | INSTANCIAR_VAR
             | DOW_LOOP
             | FOR_LOOP
             | WRITE
             | MAZEE
             | IF_SENTENCIA
             | MODIFICAR_VAR
             | INVOKE_PROCEDIMIENTO;
             //| EXIT PUNTO_COMA;

    TURNON: ENCENDER{insertarFondo(new ArduinoSentence());setNames("TurnOn");setifs(ifval);} PARENTESIS_A PARAMETRO COMA PARAMETRO COMA PARAMETRO COMA PARAMETRO COMA PARAMETRO COMA PARAMETRO PARENTESIS_C PUNTO_COMA
            | ENCENDER_TODOS{insertarFondo(new ArduinoSentence());setNames("TurnON");setifs(ifval);} PARENTESIS_A PARAMETRO COMA PARAMETRO COMA PARAMETRO PARENTESIS_C PUNTO_COMA;


    TURNOFF: APAGAR_TODOS {insertarFondo(new ArduinoSentence());setNames("TurnOFF");setifs(ifval);} PARENTESIS_A PARAMETRO COMA PARAMETRO COMA PARAMETRO PARENTESIS_C PUNTO_COMA
           | APAGAR {insertarFondo(new ArduinoSentence());setNames("TurnOff");setifs(ifval);}PARENTESIS_A PARAMETRO COMA PARAMETRO COMA PARAMETRO PARENTESIS_C PUNTO_COMA;

    SOUNDON: ENCENDER_SONIDO{insertarFondo(new ArduinoSentence());setNames("SoundOn");setifs(ifval);} PARENTESIS_A PARAMETRO PARENTESIS_C PUNTO_COMA;

    SOUNDOFF: APAGAR_SONIDO{insertarFondo(new ArduinoSentence());setNames("SoundOff");setifs(ifval);} PARENTESIS_A PARAMETRO PARENTESIS_C PUNTO_COMA;

    WRITE: ESCRIBIR{insertarFondo(new ArduinoSentence());setNames("Write");setifs(ifval);} PARENTESIS_A VARIABLE{palabra(yytext);} PARENTESIS_C PUNTO_COMA;

    MAZEE: MAZE{insertarFondo(new ArduinoSentence());setNames("Maze");setifs(ifval);} PARENTESIS_A PARAMETRO COMA PARAMETRO PARENTESIS_C PUNTO_COMA;

    EXITS: EXIT{exits();} PUNTO_COMA
            | EPSILON;

    DOW_LOOP: INI_LOOP VARIABLE{insertarFondo((new Dow(yytext)));setNames("Dow");setifs(ifval);} IN PARAMETRO{setValor1(atoi(yytext));} STEP PARAMETRO{setValor2(atoi(yytext));} EXPRESION FIN_LOOP {insertarBloque(new Block());} PUNTO_COMA;


    FOR_LOOP: INI_FOR PARAMETRO{insertarFondo((new ForTimes(atoi(yytext))));setNames("For");setifs(ifval);} TIMES EXPRESION FIN_FOR PUNTO_COMA;

    IF_SENTENCIA: INI_IF{insertarFondo((new If())); setNames(yytext);} VARIABLE{addLeftIf(yytext);} IGUAL PARAMETRO{addRightIf(atoi(yytext));} THEN EXPRESION{ifval+=1;} ELSEIF FIN_IF{insertarBloque(new Block());} PUNTO_COMA;


    ELSEIF: ELSE_IF VARIABLE{addLeftIf(yytext);} IGUAL PARAMETRO{addRightIf(atoi(yytext));} PUNTO_COMA EXPRESION ELSEIF{ifval+=1;}
          | ELSEFIN;

    ELSEFIN: ELSE{ifval=0;} EXPRESION
           | EPSILON;

PROCEDIMIENTO: DECLARAR_PROCEDIMIENTO VARIABLE{BlockList.back()->addSentence(new Block()); BlockList.back()->sentences.back()->setName(yytext); setGame();process(yytext);} INI_PROCEDIMIENTO EXPRESION {addVariables(); Locals.clear();}DECLARAR_PROCEDIMIENTO VARIABLE{if(ProcI.back().compare(yytext)!=0){QString err = QString::fromStdString(yytext);
        QString num= QString::number(yylineno);
        QString error= "Syntax error "+err +" line: " + num;
        MIDE->console(error);
        return 0;};} FIN_PROCEDIMIENTO PROCEDIMIENTO
             | EPSILON;

    PARAMETRO: VARIABLE  {addParam(yytext,"var");}
             | TIEMPO {addParam(yytext,"num");};

    INVOKE_PROCEDIMIENTO: CALL VARIABLE{printf(yytext);if(cmp(yytext))printf("SI");} PUNTO_COMA;

%%
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
