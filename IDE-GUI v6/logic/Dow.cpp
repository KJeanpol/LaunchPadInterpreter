//
// Created by Luis on 29/9/2017.
//

#include "Dow.h"

Dow::Dow(string pvar) {
    var=pvar;

}


void Dow::execute()
{
    if(valor1>valor2){
        QString variab = QString::fromStdString(var);
        ID->console("ERROR No se puede incrementar "+ variab);
        cout<<"ERROR No se puede incrementar"<<endl;
        return;
    }else {
        while (valor1 != valor2) {
            cout << valor1 << endl;
            for (int i = 0; i < sentences.size(); i++) {
                sentences[i]->execute();
            }
            valor1 += 1;
        }
        setVal(var, valor1);
    }
}
