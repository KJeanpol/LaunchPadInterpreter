//
// Created by Luis on 5/10/2017.
//

#ifndef SEMANTICANALYSIS_DECREASE_H
#define SEMANTICANALYSIS_DECREASE_H


#include "Block.h"

class Decrease: public Block {
public:
    string varn;
    Decrease();
    void ejecutar();

    void execute();

};


#endif //SEMANTICANALYSIS_DECREASE_H
