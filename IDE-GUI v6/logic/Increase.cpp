//
// Created by Luis on 5/10/2017.
//

#include "Increase.h"

Increase::Increase() {}

void Increase::ejecutar(){
    for(int i=0;i!=sentences.size();i++){
        sentences[i]->setPara();
        cout<<"YYYYYY"<<sentences[i]->getVar(varinc);
        for(int j=0;j!=sentences[i]->params.size();j++){
            if(varinc.compare((sentences[i]->params[j]))==0){
               sentences[i]->values[j] = getVar(varinc);
            }
        }
        sentences[i]->execute();
    }
}


void Increase::execute() {
    increase(varinc);
    cout<<"XXXXX"<<getVar(varinc);

    ejecutar();
}
