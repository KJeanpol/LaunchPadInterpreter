#include "y.tab.c"

main(){
	if(yyparse()==0)
	printf("\nAnalisis Sintactico concluido sin errores\n");
}


