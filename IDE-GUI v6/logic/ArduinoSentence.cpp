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
        return;

    }else if(name.compare("TurnON")==0){
        object.insert("Juego",juego);
        object.insert("Type","TurnON");
        object.insert("Boton",bot);
        object.insert("Fil",fils);
        object.insert("Col",cols);
        QJsonDocument doc(object);
        qDebug(doc.toJson());
        sentences.back()->execute();
        ID->sendMessage(doc.toJson());
        //pro.sendMessage("ADIOS");
        return;
    }else if(name.compare("TurnOff")==0){
        sentences.back()->execute();
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
        sentences.back()->execute();
        ID->sendMessage(doc.toJson());
        return;
    }else if(name.compare("SoundOn")==0){
        object.insert("Juego",juego);
        object.insert("Type","SoundOn");
        object.insert("Boton",bot);
        QJsonDocument doc(object);
        qDebug(doc.toJson());
        sentences.back()->execute();
        ID->sendMessage(doc.toJson());
        return;
    }else if(name.compare("SoundOff")==0){
        object.insert("Juego",juego);
        object.insert("Type","Soundff");
        object.insert("Boton",bot);
        QJsonDocument doc(object);
        qDebug(doc.toJson());
        sentences.back()->execute();
        ID->sendMessage(doc.toJson());
        return;
    }else{ return; }




}

void connectToHost()
{
}

void ArduinoSentence::closeConnection()
{
    cout << "Cerrando conexion";

}
