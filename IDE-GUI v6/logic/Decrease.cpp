//
// Created by Luis on 5/10/2017.
//

#include "Decrease.h"

Decrease::Decrease() {}

void Decrease::ejecutar(){
    for(int i=0;i!=sentences.size();i++){
        sentences[i]->setPara();
        sentences[i]->execute();
    }
}

void Decrease::execute() {
    cout<<"DEC"<<vardec;
    decrease(vardec);
    setPara();
    ejecutar();
}
