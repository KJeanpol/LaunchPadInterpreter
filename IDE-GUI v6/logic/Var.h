//
// Created by Luis on 30/9/2017.
//

#ifndef SEMANTICANALYSIS_VAR_H
#define SEMANTICANALYSIS_VAR_H

#include <string>
#include <iostream>

using namespace std;
class Var {
public:
    int value;
    string name;
    string type;
public:
    Var(string pname);
    void setValues(int pval){
        this->value=pval;

    }
    void setType(string ptype){
        this->type=ptype;
    }
    string getName(){
        return name;
    }
    string getType(){
        return type;
    }
    int getVal(){
        return value;
    }

};


#endif //SEMANTICANALYSIS_VAR_H
