//
// Created by Luis on 5/10/2017.
//

#include "Decrease.h"

Decrease::Decrease() {}

void Decrease::execute() {
    decrease(vardec);
    sentences.back()->execute();
}
