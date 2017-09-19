#include "LexYacc/y.tab.c"
#include "Logic/Variable.h"
#include "Logic/Procedimiento.h"
int main(int a, char * str[]){
    yy_scan_string(str[1]);
    yyparse();

    //Procedimiento *miProcedimiento=new Procedimiento();
    //setProcedimiento(miProcedimiento);
 //   miProcedimiento->addVariable(new Variable("MiVar",2));
   // miProcedimiento->searchVarible("MiVar");
    return 0;
}
