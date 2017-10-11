//
// Created by Luis on 5/10/2017.
//

#ifndef SEMANTICANALYSIS_INCREASE_H
#define SEMANTICANALYSIS_INCREASE_H


#include "Block.h"

class Increase: public Block {
public:
    string varn;
    Increase();
    void ejecutar();
    void execute();

};


#endif //SEMANTICANALYSIS_INCREASE_H
