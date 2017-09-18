//
// Created by Jeanpol on 17/9/2017.
//

#ifndef SEMANTICANALYSIS_PROCEDIMIENTO_H
#define SEMANTICANALYSIS_PROCEDIMIENTO_H
#include "Variable.h"
#include <vector>

class Procedimiento {

public:
    vector <Variable> hojaD;
    void addVariable(Variable *pvariable);
    void searchVarible(string pNombre);
    Procedimiento ();
};


#endif //SEMANTICANALYSIS_PROCEDIMIENTO_H
