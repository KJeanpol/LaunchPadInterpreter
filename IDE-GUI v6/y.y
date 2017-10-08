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
	std::vector<Var *> Vars;
	std::vector<Var *> Global;
    std::vector<string *> ProcI;
    string LastVar;
    int juego=1;
    MainWindow* MIDE;


//______________________________________________________________________//
bool inslocal(string pname, int pvalue){
    for(int i=0;i<Vars.size();i++){
        if(Vars[i]->getName().compare(pname)==0){
            return true;
        }
    }return false;
}

bool ins(string pname, int pvalue){
    Block* tmp= BlockList.back();
    while(tmp->hasBlock()){
        tmp=tmp->sentences.back();
    }tmp->setVal(pname, pvalue);
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
    bool exists(string pvar){
        bool res=false;
        for(int i=0;i<Vars.size();i++){
            if(Vars[i]->getName().compare(pvar)==0){
                res=true;
                return res;
            }else{
                res=false;
            }
        }return res;
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
                        BlockList.back()->addVars(Global[i]);
                    }
                }
        //______________________________________________________________________//
          void addVariables(){
             Block* tmp= BlockList.back();
               while(tmp->hasBlock()){
                 tmp=tmp->sentences.back();
               } for(int i=0;i!=Vars.size();i++){
                    tmp->addVars(Vars[i]);
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
                    if(tmp->getName().compare("If")!=0){
                        tmp=tmp->sentences.back();
                    }else{
                        tmp->addSentence(pblock);
                        tmp->sentences.back()->setIDS(MIDE);
                        return;
                    }

               }tmp->addSentence(pblock); tmp->sentences.back()->setIDS(MIDE);
           }

           void setBoton(string pvar){
               Block* tmp= BlockList.back();
               while(tmp->hasBlock()){
                    if(tmp->getName().compare("If")!=0){
                        tmp=tmp->sentences.back();
                    }else{
                        tmp->boton=pvar;
                        return;
                    }

               }tmp->boton=pvar;
           }
           void setFila(string pvar){
               Block* tmp= BlockList.back();
               while(tmp->hasBlock()){
                    if(tmp->getName().compare("If")!=0){
                        tmp=tmp->sentences.back();
                    }else{
                        tmp->fil=pvar;
                        return;
                    }

               }tmp->fil=pvar;
           }
           void setCol(string pvar){
               Block* tmp= BlockList.back();
               while(tmp->hasBlock()){
                    if(tmp->getName().compare("If")!=0){
                        tmp=tmp->sentences.back();
                    }else{
                        tmp->col=pvar;
                        return;
                    }

               }tmp->col=pvar;
           }
           void setRed(int pvar){
               Block* tmp= BlockList.back();
               while(tmp->hasBlock()){
                    if(tmp->getName().compare("If")!=0){
                        tmp=tmp->sentences.back();
                    }else{
                        tmp->red=pvar;
                        return;
                    }

               }tmp->red=pvar;
           }
           void setGreen(int pvar){
               Block* tmp= BlockList.back();
               while(tmp->hasBlock()){
                    if(tmp->getName().compare("If")!=0){
                        tmp=tmp->sentences.back();
                    }else{
                        tmp->green=pvar;
                        return;
                    }

               }tmp->green=pvar;
           }
           void setBlue(int pvar){
               Block* tmp= BlockList.back();
               while(tmp->hasBlock()){
                    if(tmp->getName().compare("If")!=0){
                        tmp=tmp->sentences.back();
                    }else{
                        tmp->blue=pvar;
                        return;
                    }

               }tmp->blue=pvar;
           }

           void setNames(string pname){
                          Block* tmp= BlockList.back();
                          while(tmp->hasBlock()){
                               tmp=tmp->sentences.back();
                          }tmp->setName(pname);
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

    PRINCIPIO: COMENTARIO{BlockList.push_back(new Block());BlockList.back()->setIDS(MIDE);} HOJA_D{addVariables();Vars.clear();setNames("Block");} PROCEDIMIENTO EXPRESION;

	DEFINIR_VAR: DEFINIR VARIABLE{Vars.push_back(new Var(yytext));} VTIEMPO {Vars.back()->setType(yytext);} PUNTO_COMA;

	DEFINIR_LOCAL: VARIABLE{Vars.push_back(new Var(yytext));} VTIEMPO {Vars.back()->setType(yytext);} PUNTO_COMA;

	COMENTARIO: COMENTARIO_I NOMBRE COMENTARIO_F COMENTARIO
			  | EPSILON;

	HOJA_D: DEFINIR_VAR HOJA_D
		  | EPSILON;

	EPSILON: ;

	MODIFICAR_VAR: INCREMENTO VARIABLE{insertarFondo((new Increase()));setNames("Incremento");setincremento(yytext); } INCREMENTO PUNTO_COMA
				 | DECREMENTO VARIABLE{insertarFondo((new Decrease()));setNames("Decremento");setdecremento(yytext);} DECREMENTO PUNTO_COMA;


	INSTANCIAR_VAR: INI_VARIABLE VARIABLE{LastVar=yytext;} IGUAL PARAMETRO{if(!inslocal(LastVar,atoi(yytext))) ins(LastVar,atoi(yytext));} PUNTO_COMA;

	EXPRESION: EXPRESION_SIMPLE EXPRESION
			 |	EPSILON;

	EXPRESION_SIMPLE: TURNON
             |DEFINIR_LOCAL
			 | TURNOFF
			 | SOUNDON
			 | SOUNDOFF
			 | INSTANCIAR_VAR
			 | DOW_LOOP
			 | FOR_LOOP
			 | IF_SENTENCIA
			 | MODIFICAR_VAR
			 | INVOKE_PROCEDIMIENTO;
			 //| EXIT PUNTO_COMA;

    TURNON: ENCENDER{insertarFondo(new ArduinoSentence());setNames("TurnOn");} PARENTESIS_A PARAMETRO{setBoton(yytext);} COMA PARAMETRO{setCol(yytext);} COMA PARAMETRO{setFila(yytext);} COMA PARAMETRO{setRed(atoi(yytext));} COMA PARAMETRO{setGreen(atoi(yytext));} COMA PARAMETRO{setBlue(atoi(yytext));} PARENTESIS_C PUNTO_COMA
            | ENCENDER_TODOS{insertarFondo(new ArduinoSentence());setNames("TurnON");} PARENTESIS_A PARAMETRO{setBoton(yytext);} COMA PARAMETRO{setCol(yytext);} COMA PARAMETRO{setFila(yytext);} PARENTESIS_C PUNTO_COMA;


    TURNOFF: APAGAR_TODOS {insertarFondo(new ArduinoSentence());setNames("TurnOFF");} PARENTESIS_A PARAMETRO{setBoton(yytext);} COMA PARAMETRO{setCol(yytext);} COMA PARAMETRO{setFila(yytext);} PARENTESIS_C PUNTO_COMA
           | APAGAR {insertarFondo(new ArduinoSentence());setNames("TurnOff");}PARENTESIS_A PARAMETRO{setBoton(yytext);} COMA PARAMETRO{setCol(yytext);} COMA PARAMETRO{setFila(yytext);}PARENTESIS_C PUNTO_COMA;

    SOUNDON: ENCENDER_SONIDO{insertarFondo(new ArduinoSentence());setNames("SoundOn");} PARENTESIS_A PARAMETRO{setBoton(yytext);} PARENTESIS_C PUNTO_COMA;

    SOUNDOFF: APAGAR_SONIDO{insertarFondo(new ArduinoSentence());setNames("SoundOff");} PARENTESIS_A PARAMETRO{setBoton(yytext);} PARENTESIS_C PUNTO_COMA;


	DOW_LOOP: INI_LOOP VARIABLE{insertarFondo((new Dow(yytext)));setNames("Dow");} IN PARAMETRO{setValor1(atoi(yytext));} STEP PARAMETRO{setValor2(atoi(yytext));} EXPRESION EXIT PUNTO_COMA EXPRESION FIN_LOOP PUNTO_COMA;


	FOR_LOOP: INI_FOR PARAMETRO{insertarFondo((new ForTimes(atoi(yytext))));setNames("For");} TIMES EXPRESION FIN_FOR PUNTO_COMA;

	IF_SENTENCIA: INI_IF{insertarFondo((new If())); setNames(yytext);} VARIABLE{addLeftIf(yytext);} IGUAL PARAMETRO{addRightIf(atoi(yytext));} THEN EXPRESION ELSEIF FIN_IF PUNTO_COMA;


	ELSEIF: ELSE_IF VARIABLE{addLeftIf(yytext);} IGUAL PARAMETRO{addRightIf(atoi(yytext));} PUNTO_COMA EXPRESION ELSEIF
		  | ELSEFIN;

	ELSEFIN: ELSE EXPRESION
		   | EPSILON;

    PROCEDIMIENTO: DECLARAR_PROCEDIMIENTO VARIABLE{BlockList.back()->addSentence(new Block()); BlockList.back()->sentences.back()->setName(yytext); setGame();} INI_PROCEDIMIENTO EXPRESION DECLARAR_PROCEDIMIENTO VARIABLE FIN_PROCEDIMIENTO{addVariables(); Vars.clear();} PROCEDIMIENTO
			 | EPSILON;

	PARAMETRO: VARIABLE  {}
			 | TIEMPO {};

	INVOKE_PROCEDIMIENTO: CALL VARIABLE{printf(yytext);if(cmp(yytext))printf("SI");} PUNTO_COMA;

%%
int yyerror(const char* s ) {
	//yyerrok;
	//cout<<yytext<<endl;
	//fprintf(stderr,"%s: %s at line %d\n", s, yytext,yylineno);
	std::cout<<"Error de sintaxis en linea: "<<yylineno;
    yyclearin;
    QString num= QString::number(yylineno);
    QString error= "Syntax error line: " + num;
    MIDE->console(error);
    yylineno=1;

	return 0;
}
