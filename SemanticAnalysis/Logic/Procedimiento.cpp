//
// Created by Jeanpol on 17/9/2017.
//

#include "Procedimiento.h"

void Procedimiento::addVariable(Variable *pvariable) {
    hojaD.push_back(*pvariable);

}
void Procedimiento::searchVarible(string pNombre) {
    int i=0;
    for (i;i<hojaD.size();i++){
        if (pNombre==hojaD[i].getName()){
            cout<<"Si existe"<<endl;
        }
        else {
            cout <<"no existe"<<endl;
        }
    }
}

Procedimiento::Procedimiento() {
}
