//
// Created by Luis on 29/9/2017.
//

#ifndef SEMANTICANALYSIS_DOWSENTENCE_H
#define SEMANTICANALYSIS_DOWSENTENCE_H


#include "Block.h"

class Dow: public Block{
public:

    Dow (string pvar);
    void setval1(int pval){
        pval=valor1;
    }
    void setval2(int pval){
        pval=valor2;
    }
    void execute();
    int getVal(){
        return valor1;
    }


};


#endif //SEMANTICANALYSIS_DOWSENTENCE_H
