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
    for (int i = 1; i < game1.size(); i++) {
      Serial.println(vector[i]);
    }

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
        vector.push_back(value1);
        //game_push(value1);
        sirve = 5;
      }

      value1 = value1 + json[i + 1];
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

void cleanVector() {

  for (int i = 1; i < vector.size(); i++) {
    game_push(vector[i]);
  }
  //      vectorBandera.push_back(vector[i]);
  //      Serial.print(vectorBandera[i-1]);
  //      Serial.println("-------------------------------------------------");
  //    }
  //    Serial.println("--------------------VECTOR[1]-----------------------------");
  //    Serial.print(vectorBandera[1]);


}


