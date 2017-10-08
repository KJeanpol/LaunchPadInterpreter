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
  value1="";


}

void loop() {
  if (BT1.available()) {
    read();
   for(int i=0; i<vector.size(); i++){
    Serial.print(vector[i]);
  }}

}


//...............READSOCKETANDSAVE............//
void read() {

  String json = BT1.readString();
  miSplitter(json);
 

}

void miSplitter(String json){
  for (int i = 0; i < json.length(); i++){
    if (json[i]=='}'){
        value1=value1+json[i];
        //Serial.println(value1);
        vector.push_back(value1);
        value1="";
      }
    value1=value1+json[i];
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





