#include <SoftwareSerial.h>
#include <Vector.h>
#include <ArduinoJson.h>
#include <Arduino.h>
SoftwareSerial BT1(12, 13); // RX, TX recorder que se cruzan

Vector <String> vector;
char cadena[255];
int i = 0;
int flag = 0;
StaticJsonBuffer<1000> jsonBuffer;




void setup()
{
  BT1.begin(9600);
  Serial.begin(9600);



}

void loop() {
  if (BT1.available()) {
    read();
    Serial.print(vector[0]);
    Serial.print(vector[1]);
    Serial.print(vector[2]);
    Serial.print(vector[3]);
    Serial.print(vector[4]);
   
  }
}


  void clean()
  {
    for (int cl = 0; cl <= i; cl++)
    {
      cadena[cl] = 0;
    }
    i = 0;
  }

  //...............READSOCKETANDSAVE............//
  void read() {

    String json = BT1.readString();
    //Serial.print(json);
    splitter(json);
    
}

    
    
//    char dato = BT1.read();
//    cadena[i++] = dato;
//    Serial.print(dato);
//    if (dato == '}') {
//      vector.push_back(cadena);
//      clean();
//      //Serial.print("hola");
//  }

  

  //...............TOKENCOUNT............//
  //ESTA FUNCION SE CREO POR QUE EL LOOP DE CREACION DE LOS VECTORES HACIA UQE AL INSTANCIARLOS AUN NO SE HABIAN CREADO LO CUAL PROVOCABA
  //UN ERROR EN TIEMPO DE EJECUCION YA QUE SE DEBIA DE ESPERAR UN MOMENTO PARA QUE SE CREARAN Y LUEGO INSTANCIARLOS PERO NO HABIA FORMA YA QUE EL DILAY() PAUSA EL EVENTO PERO ESO
  //INVOLUCRABA DETENER TODO ANTES DE LA LINEA DE CODIGO DONDE SE DEVUELVE PARA CREARSE, POR LO CUAL SE OPTA POR OBTENER TODO EL STRING PARA LUEGO SPLITEARLO Y ACOMODAR TODO EN TIEMPO DE COMPILACION
  void splitter(String Q){               
    for (int i = 0; i < Q.length(); i++) {
  if (Q.substring(i, i+1) == "}") {
    String value1 = Q.substring(0, i+1);
    vector.push_back(value1);
    String value2= Q.substring(i+1);
    
    //Serial.print(value1);
    splitter(value2);
    
    
    break;
  }
    
  }
  }





  //................PARSERJUEGO...............//

  int parserJuego(String Json) {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(Json);
    // Test if parsing succeeds.
    if (!root.success()) {
      Serial.println("parseObject() failed");
      return;
    }

    int juego = root["Juego"];
    return juego;

  }

  //................PARSERBOTON..............//

  int parserBoton(String Json) {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(Json);
    // Test if parsing succeeds.
    if (!root.success()) {
      Serial.println("parseObject() failed");
      return;
    }

    int boton = root["Boton"];
    return boton;

  }
  //................PARSERFUNCTION..............//
  String parserFunction(String Json) {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(Json);
    // Test if parsing succeeds.
    if (!root.success()) {
      Serial.println("parseObject() failed");
      return;
    }

    String type = root["Type"];
    return type;

  }





