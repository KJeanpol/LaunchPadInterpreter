//
// Created by Jeanpol on 16/9/2017.
//

#ifndef SEMANTICANALYSIS_VARIABLE_H
#define SEMANTICANALYSIS_VARIABLE_H
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

class Variable {

public:
    string name;
    int value;

    void setName(const string &name);
    void setValue(int value);
    const string &getName() const;
    int getValue() const;

public:
    Variable (string pname, int pvalue);
};


#endif //SEMANTICANALYSIS_VARIABLE_H
