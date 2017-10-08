  #include <SoftwareSerial.h>
#include <Vector.h>
#include <ArduinoJson.h>

SoftwareSerial BT1(12, 13); // RX, TX recorder que se cruzan

Vector <String> game1;
Vector <String> game2;
Vector <String> game3;
Vector <String> game4;
Vector <String> vector;
Vector <String> vectorBandera;
Vector <String> b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,
b14,b15,b16,b17,b18,b19,b20,b21,b22,b23,b24,b25,b26,b27,b28,
b29,b30,b31,b32,b33,b34,b35,b36;

int flag = 0;
String value2;
String value1;





void setup()
{
  BT1.begin(9600);
  Serial.begin(9600);
  value1 = "";


}

void loop() {
  if (BT1.available()) {
    readD();
    cleanVector();
    int w=0;
    for (int i = 0; i < b5.size(); i++) {
      Serial.println(b5[i]);
      w++;
    }
    Serial.println(w);

  }
}


//...............READSOCKETANDSAVE............//
void readD() {

  String json = BT1.readString();
  miSplitter(json);


}

void miSplitter(String json) {
  int sirve = 0;
  for (int i = 0; i < json.length(); i++) {
    if (json[i] == '}') {
      if (sirve == 0) {
        value1 = '{' + value1 + json[i - 1];
       
        //vector.push_back(value1);
        //game_push(value1);
        sirve++;
     
      }

      value1 = value1 + json[i + 1];
     // Serial.print(value1);
       
      vector.push_back(value1);
      //game_push(value1);
      value1 = "";
    }
    value1 = value1 + json[i + 1];

  }



}

//................PARSERJUEGO...............//

int parserJuego(String Json) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(Json);
  int juego = root["Juego"];
  return juego;

}

//................PARSERBOTON...............//

int parserBoton(String Json) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(Json);
  int boton = root["Boton"];
  return boton;

}



void game_push(String json) {
  switch (parserJuego(json)) {
    case 1:
      game1.push_back(json);
      break;
    case 2:
      game2.push_back(json);
      break;
    case 3:
      game3.push_back(json);
      break;
    case 4:
      game4.push_back(json);
      break;
  }
}

void Button_push(String json) {
  switch (parserBoton(json)) {
    case 1:
      b1.push_back(json);
      break;
    case 2:
      b2.push_back(json);
      break;
    case 3:
      b3.push_back(json);
      break;
    case 4:
      b4.push_back(json);
      break;
    case 5:
      b5.push_back(json);
      break;
  }
}

void cleanVector() {

  for (int i = 0; i < vector.size(); i++) {
    game_push(vector[i]);
    Button_push(vector[i]);
  }
  //      vectorBandera.push_back(vector[i]);
  //      Serial.print(vectorBandera[i-1]);
  //      Serial.println("-------------------------------------------------");
  //    }
  //    Serial.println("--------------------VECTOR[1]-----------------------------");
  //    Serial.print(vectorBandera[1]);


}


