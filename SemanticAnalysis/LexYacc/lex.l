%option noyywrap
%option yylineno

%{
	#include "y.tab.h"
	#include<stdio.h>
%}

NUMERO [0-9]+
NOMBRE  [a-zA-Z]*
VARIABLE [A-Z]("@"|"$"|"#"|[a-zA-Z0-9]){0,11}

%%

"Tiempo"											{return VTIEMPO;}

">>"												{return COMENTARIO_I;}
"<<"												{return COMENTARIO_F;}
"+"													{return INCREMENTO;}
"-"													{return DECREMENTO;}
"="													{return IGUAL;}
"("													{return PARENTESIS_A;}
")"													{return PARENTESIS_C;}
","													{return COMA;}
";"													{return PUNTO_COMA;}

"TurnON"											{return ENCENDER_TODOS;}
"TurnOn"											{return ENCENDER;}
"TurnOff"											{return APAGAR;}
"TurnOFF"											{return APAGAR_TODOS;}
"SoundOn"											{return ENCENDER_SONIDO;}
"SoundOff"											{return APAGAR_SONIDO;}

"Dow"												{return INI_LOOP;}
"Enddo"												{return FIN_LOOP;}
"For"												{return INI_FOR;}
"FEnd"												{return FIN_FOR;}
"If"												{return INI_IF;}
"Endif"												{return FIN_IF;}
"else"												{return ELSE;}
"elseIf"											{return ELSE_IF;}

"D"													{return DEFINIR;}
"P"													{return DECLARAR_PROCEDIMIENTO;}	
"Call"												{return CALL;}
"B"													{return INI_PROCEDIMIENTO;}
"E"													{return FIN_PROCEDIMIENTO;}


"in"												{return	IN;}
"Step"												{return STEP;}
"Then"												{return THEN;}
"Exit"												{return EXIT;}
"Times"												{return TIMES;}
"INZ"												{return INI_VARIABLE;}

{VARIABLE}											{return VARIABLE;}
{NOMBRE}											{return NOMBRE;}
{NUMERO}											{return TIEMPO;}
\n													{ }
\t													{ }
" "													{ }
.                              						{printf("Error lexico en linea %d\n",yylineno);}
%%

int yyerror (const char* s );