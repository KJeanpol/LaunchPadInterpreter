//
// Created by Luis on 5/10/2017.
//

#include "Increase.h"

Increase::Increase() {}

void Increase::ejecutar(){
    for(int i=0;i!=sentences.size();i++){
        sentences[i]->setPara();
        sentences[i]->execute();
    }
}


void Increase::execute() {
    cout<<"INC"<<varinc;
    increase(varinc);
    cout<<getVar(varinc);

    ejecutar();
}
