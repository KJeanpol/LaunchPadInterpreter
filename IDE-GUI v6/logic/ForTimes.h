//
// Created by Jeanpol on 18/9/2017.
//

#ifndef SEMANTICANALYSIS_FORTIMES_H
#define SEMANTICANALYSIS_FORTIMES_H

#include "Block.h"
#include <vector>


class ForTimes: public Block {

    public:
    ForTimes (int ptimes);

    void execute();

};


#endif //SEMANTICANALYSIS_FORTIMES_H
