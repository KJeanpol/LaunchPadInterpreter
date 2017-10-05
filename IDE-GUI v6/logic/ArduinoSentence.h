//
// Created by Luis on 30/9/2017.
//

#ifndef SEMANTICANALYSIS_ARDUINOSENTENCE_H
#define SEMANTICANALYSIS_ARDUINOSENTENCE_H

#include <string>
#include "Block.h"


using namespace std;
class ArduinoSentence: public Block {

public:
    void execute();
    static void connectToHost(string ip,int port);
    static void closeConnection();
};


#endif //SEMANTICANALYSIS_ARDUINOSENTENCE_H
