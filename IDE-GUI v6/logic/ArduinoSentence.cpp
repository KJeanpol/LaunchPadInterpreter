//
// Created by Luis on 30/9/2017.
//

#include <iostream>
#include "ArduinoSentence.h"

void ArduinoSentence::execute()
{ cout << "Ejecutando sentencia arduino"<<endl; }
void ArduinoSentence::connectToHost(string ip, int port)
{
    cout << "Conectando";

}
void ArduinoSentence::closeConnection()
{
    cout << "Cerrando conexion";

}