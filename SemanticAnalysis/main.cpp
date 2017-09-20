#include "LexYacc/y.tab.c"
#include "Logic/Variable.h"
#include "Logic/Procedimiento.h"
#include <fstream>
#include <string.h>
#include <stdio.h>
int main(int a, char * str[]){

    cout << str[1] << endl;


    if (a == 3){
        if (!strcmp("-file", str[1])){
            cout << "in file mode!" << endl;
            std::ifstream ifs(str[2]);
            std::string content( (std::istreambuf_iterator<char>(ifs) ),
                             (std::istreambuf_iterator<char>()    ) );
            ifs.close();
            yy_scan_string(content.c_str());
        }
    }
    if (a == 2){
        cout << "caso 2" << endl;
        yy_scan_string(str[1]);
    }



    yyparse();

    //Procedimiento *miProcedimiento=new Procedimiento();
    //setProcedimiento(miProcedimiento);
 //   miProcedimiento->addVariable(new Variable("MiVar",2));
   // miProcedimiento->searchVarible("MiVar");
    return 0;
}
