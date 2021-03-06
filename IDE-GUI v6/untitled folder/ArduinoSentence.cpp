//
// Created by Luis on 30/9/2017.
//

#include <iostream>
#include "ArduinoSentence.h"
#include "QJsonObject"
#include "QJsonDocument"
#include<QtBluetooth>
#include "stdio.h"
#include "mainwindow.h"



void ArduinoSentence::execute()
{   QJsonObject object;
           int bot= getVar(boton);
            int fils= getVar(fil);
            int cols= getVar(col);
    if(name.compare("TurnOn")==0){
        object.insert("Juego",juego);
        object.insert("Type","TurnOn");
        object.insert("Boton",bot);
        object.insert("Fil",fils);
        object.insert("Col",cols);
        object.insert("R",red);
        object.insert("G",green);
        object.insert("B",blue);
        QJsonDocument doc(object);
        qDebug(doc.toJson());
        ID->sendMessage(doc.toJson());
        ejecutar();


        return;

    }else if(name.compare("TurnON")==0){
        object.insert("Juego",juego);
        object.insert("Type","TurnON");
        object.insert("Boton",bot);
        object.insert("Fil",fils);
        object.insert("Col",cols);
        QJsonDocument doc(object);
        qDebug(doc.toJson());
        ID->sendMessage(doc.toJson());
        ejecutar();


        return;
    }else if(name.compare("TurnOff")==0){
        ejecutar();
        cout<<"Apagando un led";

        return;
    }else if(name.compare("TurnOFF")==0){
        object.insert("Juego",juego);
        object.insert("Type","TurnOFF");
        object.insert("Boton",bot);
        object.insert("Fil",fils);
        object.insert("Col",cols);
        QJsonDocument doc(object);
        qDebug(doc.toJson());
        ID->sendMessage(doc.toJson());
        ejecutar();


        return;
    }else if(name.compare("SoundOn")==0){
        object.insert("Juego",juego);
        object.insert("Type","SoundOn");
        object.insert("Boton",bot);
        QJsonDocument doc(object);
        qDebug(doc.toJson());
        ID->sendMessage(doc.toJson());
        ejecutar();


        return;
    }else if(name.compare("SoundOff")==0){
        object.insert("Juego",juego);
        object.insert("Type","SoundOff");
        object.insert("Boton",bot);
        QJsonDocument doc(object);
        qDebug(doc.toJson());
        ID->sendMessage(doc.toJson());
        ejecutar();


        return;
    }else{ return; }




}

void ArduinoSentence::ejecutar()
{
    for(int i = 0; i!=sentences.size(); i++){
        sentences[i]->execute();
    }
}

void ArduinoSentence::closeConnection()
{
    cout << "Cerrando conexion";

}
