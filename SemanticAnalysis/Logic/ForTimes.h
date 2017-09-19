//
// Created by Jeanpol on 18/9/2017.
//

#ifndef SEMANTICANALYSIS_FORTIMES_H
#define SEMANTICANALYSIS_FORTIMES_H

#include "Block.h"
#include <vector>
#include "Variable.h"

class ForTimes {

    public:
    int times;
    vector <Block> instructions;
    void addBlock(Block *pblock);
    ForTimes (int ptimes);

};


#endif //SEMANTICANALYSIS_FORTIMES_H
