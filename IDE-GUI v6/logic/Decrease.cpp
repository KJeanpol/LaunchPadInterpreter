//
// Created by Luis on 5/10/2017.
//

#include "Decrease.h"

Decrease::Decrease() {}

void Decrease::ejecutar(){
    for(int i=0;i!=sentences.size();i++){
        sentences[i]->setPara();
        cout<<"YYYYYY"<<sentences[i]->getVar(vardec);
        for(int j=0;j!=sentences[i]->params.size();j++){
            if(vardec.compare((sentences[i]->params[j]))==0){
               sentences[i]->values[j] = getVar(vardec);
            }
        }
        sentences[i]->execute();
    }
}

void Decrease::execute() {
    cout<<"DEC"<<vardec;
    decrease(vardec);
    setPara();
    ejecutar();
}
