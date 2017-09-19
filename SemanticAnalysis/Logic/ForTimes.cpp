//
// Created by Jeanpol on 18/9/2017.
//

#include "ForTimes.h"

ForTimes::ForTimes(int ptimes) {
    times=ptimes;

}

void ForTimes::addBlock(Block *pblock) {
    instructions.push_back(*pblock);
}
