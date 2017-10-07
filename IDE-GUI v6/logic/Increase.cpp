//
// Created by Luis on 5/10/2017.
//

#include "Increase.h"

Increase::Increase() {}

void Increase::execute() {
    increase(varinc);
    sentences.back()->execute();
}
