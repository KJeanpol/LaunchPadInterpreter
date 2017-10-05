//
// Created by Luis on 2/10/2017.
//

#ifndef SEMANTICANALYSIS_IF_H
#define SEMANTICANALYSIS_IF_H


#include "Block.h"

class If : public Block{

public:
    If();


    void execute();
    ~If();

};


#endif //SEMANTICANALYSIS_IF_H
