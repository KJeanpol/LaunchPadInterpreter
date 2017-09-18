#include "LexYacc/y.tab.h"
#include "Logic/Variable.h"
#include "Logic/Procedimiento.h"
int main(){
    Variable *miVariable= new Variable("MiVariable1", 2);
    cout<<miVariable->getName()<<endl;
    Procedimiento *miProcedimiento=new Procedimiento();
    miProcedimiento->addVariable(new Variable("MiVar",2));
    miProcedimiento->searchVarible("MiVar");
    return 0;
}
