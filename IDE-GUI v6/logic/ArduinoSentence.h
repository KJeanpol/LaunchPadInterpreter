//
// Created by Luis on 30/9/2017.
//

#ifndef SEMANTICANALYSIS_ARDUINOSENTENCE_H
#define SEMANTICANALYSIS_ARDUINOSENTENCE_H

#include <string>
#include "Block.h"
#include<QBluetoothDeviceDiscoveryAgent>
#include<QBluetoothSocket>







using namespace std;



class ArduinoSentence: public Block {

public:
    void execute();
    void connectToHost()
    {
    }
    void closeConnection();


private:
    QBluetoothDeviceDiscoveryAgent *agent = new QBluetoothDeviceDiscoveryAgent;
    QBluetoothSocket *socket;



};


#endif //SEMANTICANALYSIS_ARDUINOSENTENCE_H
