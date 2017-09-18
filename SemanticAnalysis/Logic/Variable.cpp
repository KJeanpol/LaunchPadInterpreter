//
// Created by Jeanpol on 16/9/2017.
//

#include "Variable.h"

const string &Variable::getName() const {
    return name;
}

int Variable::getValue() const {
    return value;
}

void Variable::setName(const string &name) {
    Variable::name = name;
}

void Variable::setValue(int value) {
    Variable::value = value;
}

Variable::Variable(string pname, int pvalue) {
    name=pname;
    value=pvalue;

}
