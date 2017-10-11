//
// Created by Jeanpol on 18/9/2017.
//

#include "ForTimes.h"

ForTimes::ForTimes(int ptimes) {

    times=ptimes;

}


void ForTimes::execute()
{

    for (int x = 0; x < times; x++){
        for(int i=0; i<sentences.size();i++){

            sentences[i]->setPara();
            sentences[i]->execute();
        }
    }
}
