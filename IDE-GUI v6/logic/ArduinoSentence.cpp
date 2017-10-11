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


bool ArduinoSentence::check(){

}


void ArduinoSentence::execute()
{

    setPara();
QJsonObject object;
    if(name.compare("TurnOn")==0){

        object.insert("Juego",juego);
        object.insert("Type","TurnOn");
        if(values[0]>36){ID->console("BUTTON INDEX OUT OF BOUNDS"); return; }else{
        object.insert("Boton",values[0]);}
        if(values[1]>5){ID->console("ROW INDEX OUT OF BOUNDS"); return; }else{
        object.insert("Fil",values[1]);}
        if(values[2]>5){ID->console("COL INDEX OUT OF BOUNDS"); return; }else{
        object.insert("Col",values[2]);}
        if(values[3]>255){ID->console("RED COLOR INDEX OUT OF BOUNDS"); return; }else{
        object.insert("R",values[3]);}
        if(values[4]>255){ID->console("GREEN COLOR INDEX OUT OF BOUNDS"); return; }else{
        object.insert("G",values[4]);}
        if(values[5]>255){ID->console("BLUE INDEX OUT OF BOUNDS"); return; }else{
        object.insert("B",values[5]);}
        QJsonDocument doc(object);
        qDebug(doc.toJson());
        ID->sendMessage(doc.toJson());
        ejecutar();


        return;

    }else if(name.compare("TurnON")==0){

        object.insert("Juego",juego);
        object.insert("Type","TurnON");
        if(values[0]>36){ID->console("BUTTON INDEX OUT OF BOUNDS"); return; }else{
        object.insert("Boton",values[0]);}
        if(values[1]>5){ID->console("ROW INDEX OUT OF BOUNDS"); return; }else{
        object.insert("Fil",values[1]);}
        if(values[2]>5){ID->console("COL INDEX OUT OF BOUNDS"); return; }else{
        object.insert("Col",values[2]);}
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
        if(values[0]>36){ID->console("BUTTON INDEX OUT OF BOUNDS"); return; }else{
        object.insert("Boton",values[0]);}
        if(values[1]>5){ID->console("ROW INDEX OUT OF BOUNDS"); return; }else{
        object.insert("Fil",values[1]);}
        if(values[2]>5){ID->console("COL INDEX OUT OF BOUNDS"); return; }else{
        object.insert("Col",values[2]);}
        QJsonDocument doc(object);
        qDebug(doc.toJson());
        ID->sendMessage(doc.toJson());
        ejecutar();


        return;
    }else if(name.compare("SoundOn")==0){

        object.insert("Juego",1);
        object.insert("Type","SoundOn");
        if(values[0]>36){ID->console("BUTTON INDEX OUT OF BOUNDS"); return; }else{
        object.insert("Boton",values[0]);}
        QJsonDocument doc(object);
        qDebug(doc.toJson());
        ID->sendMessage(doc.toJson());
        ejecutar();


        return;
    }else if(name.compare("SoundOff")==0){

        object.insert("Juego",1);
        object.insert("Type","SoundOff");
        if(values[0]>36){ID->console("BUTTON INDEX OUT OF BOUNDS"); return; }else{
        object.insert("Boton",values[0]);}
        QJsonDocument doc(object);
        qDebug(doc.toJson());
        ID->sendMessage(doc.toJson());
        ejecutar();


        return;
    }else if(name.compare("Maze")==0){

        object.insert("Juego",2);
        object.insert("Type","Maze");
        if(values[0]>5){ID->console("ROW INDEX OUT OF BOUNDS"); return; }else{
        object.insert("Fil",values[0]);}
        if(values[0]>5){ID->console("COL INDEX OUT OF BOUNDS"); return; }else{
        object.insert("Col",values[1]);}
        QJsonDocument doc(object);
        qDebug(doc.toJson());
        ID->sendMessage(doc.toJson());
        ejecutar();


        return;
    }else{

        object.insert("Juego",3);
        object.insert("Text",palabra.c_str());
        QJsonDocument doc(object);
        qDebug(doc.toJson());
        ID->sendMessage(doc.toJson());
        ejecutar();

        return; }




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

