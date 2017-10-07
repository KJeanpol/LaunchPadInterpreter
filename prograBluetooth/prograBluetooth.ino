#include <SoftwareSerial.h>
#include <Vector.h>
#include <ArduinoJson.h>
#include <Arduino.h>
SoftwareSerial BT1(12, 13); // RX, TX recorder que se cruzan

Vector <String> vector;
int flag = 0;
String value2;
String value1;





void setup()
{
  BT1.begin(9600);
  Serial.begin(9600);



}

void loop() {
  if (BT1.available()) {
    read();
    Serial.print(vector[9]);
  }

}


//...............READSOCKETANDSAVE............//
void read() {

  String json = BT1.readString();
  splitter(json);

}




//...............TOKENCOUNT............//
//ESTA FUNCION SE CREO POR QUE EL LOOP DE CREACION DE LOS VECTORES HACIA UQE AL INSTANCIARLOS AUN NO SE HABIAN CREADO LO CUAL PROVOCABA
//UN ERROR EN TIEMPO DE EJECUCION YA QUE SE DEBIA DE ESPERAR UN MOMENTO PARA QUE SE CREARAN Y LUEGO INSTANCIARLOS PERO NO HABIA FORMA YA QUE EL DILAY() PAUSA EL EVENTO PERO ESO
//INVOLUCRABA DETENER TODO ANTES DE LA LINA DE CODIGO DONDE SE DEVUELVE PARA CREARSE, POR LO CUAL SE OPTA POR OBTENER TODO EL STRING PARA LUEGO SPLITEARLO Y ACOMODAR TODO EN TIEMPO DE COMPILACION
void splitter(String Q) {
  for (int i = 0; i < Q.length(); i++) {
    if (Q.substring(i, i + 1) =="}") {
        value1 = Q.substring(0, i + 1);
        value2 = Q.substring(i + 1);
        vector.push_back(value1);
       // Serial.print("ESTE ES EL NUEVO VALOR......................");
        //Serial.print(value1);
        //Serial.println("......>>>>>>...............................>>>>................");
        splitter(value2);break;}
        
        
//        
//        if (value2 == '\0') {
//          Serial.println("si entra");
//          break;
//        
//          
//        }
        
        


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





