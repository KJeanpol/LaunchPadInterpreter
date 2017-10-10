#include <SoftwareSerial.h>
#include <Vector.h>
#include <Wire.h>             // Set up connection master (arduino mega)/slave(arduino uno)
#include <ArduinoJson.h>

//--------------------------------Libraries to control Led Matrix---------------------------------------------------
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN            6      //Pin where Din input from Leds is connected
#define NUMPIXELS      36     //How many Leds are in the Matrix
//---------------------------------Setting up Global Variables Used on the Games--------------------------------
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);   //pixels is used to control individual leds
int delayval = 500;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(6, 6, 4, 1, 6,                       //matrix is used to control the scrolling text on game 3
                            NEO_TILE_TOP   + NEO_TILE_LEFT   + NEO_TILE_ROWS   + NEO_TILE_ZIGZAG +
                            NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
                            NEO_RGB);
const uint16_t colors[] = {                                                        //Array that contains led rgb colors to continously change them in each scrolling text
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(255, 255, 0), matrix.Color(0, 0, 255),
  matrix.Color(255, 0, 255), matrix.Color(0, 255, 255), matrix.Color(255, 255, 255)
};
int  pixelPerChar = 6;
int  maxDisplacement;
//..............................Bluetooth..........................................................................
SoftwareSerial BT1(12, 13); // RX, TX recorder que se cruzan

//............................Variables............................................................................
Vector <String> game1;
Vector <String> game2;
Vector <String> game3;
Vector <String> game4;
Vector <String> vector;
Vector <String> vectorBandera;
int flagGame = 2;
String value2;
String value1;
int vidas = 3;
int bug = 0;

int matriz[6][6] = {{0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0}
};








void setup()
{
  Wire.begin();
  BT1.begin(9600);
  Serial.begin(9600);
  value1 = "";
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);



}
int x    = matrix.width();
int pass = 0;

void loop() {
  if (BT1.available()) {
    readD();
    cleanVector();
  }
  if (flagGame == 1) { //RECORDAR MODIFICAR flagGame en pruebas
    int dato0 = analogRead(0);
    int dato1 = analogRead(1);
    int dato2 = analogRead(2);
    int dato3 = analogRead(3);
    int dato4 = analogRead(4);
    int dato5 = analogRead(5);
    onTouchButton(0, dato0);
    onTouchButton(1, dato1);
    onTouchButton(2, dato2);
    onTouchButton(3, dato3);
    onTouchButton(4, dato4);
    onTouchButton(5, dato5);

  }
  else if (flagGame == 2) {
    int dato0 = analogRead(0);
    int dato1 = analogRead(1);
    int dato2 = analogRead(2);
    int dato3 = analogRead(3);
    int dato4 = analogRead(4);
    int dato5 = analogRead(5);
    int dato6 = analogRead(6);
    mazeButton(0, dato0);
    mazeButton(1, dato1);
    mazeButton(2, dato2);
    mazeButton(3, dato3);
    mazeButton(4, dato4);
    mazeButton(5, dato5);
    mazeButton(6, dato6);


  }
  else if (flagGame == 3) {

    scrollText();
  }
}


//...............READSOCKETANDSAVE............//
void readD() {

  String json = BT1.readString();
  miSplitter(json);
  Serial.print(json);


}

void miSplitter(String json) {
  int sirve = 0;
  for (int i = 0; i < json.length(); i++) {
    if (json[i] == '}') {
      if (sirve == 0) {
        value1 = '{' + value1 + json[i - 1];
        sirve++;
      }

      value1 = value1 + json[i + 1];
      vector.push_back(value1);
      value1 = "";
    }
    value1 = value1 + json[i + 1];

  }
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

  for (int i = 0; i < vector.size(); i++) {
    game_push(vector[i]);
  }
}

void onTouchButton(int anPin, int dato) {
  if (dato > 100) {
    if (dato > 500 && dato < 520) {
      if (anPin == 0) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 1) {
            Serial.println("b1");
            execute(game1[i]);

          }
        }

        delay(250);
      }
      else if (anPin == 1) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 7) {
            Serial.println("b7");
            execute(game1[i]);
          }
        }

        delay(250);
      }
      else if (anPin == 2) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 13) {
            Serial.println("b13");
            execute(game1[i]);
          }
        }

        delay(250);
      }
      else if (anPin == 3) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 19) {
            Serial.println("b19");
            execute(game1[i]);
          }
        }

        delay(250);
      }
      else if (anPin == 4) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 25) {
            Serial.println("b25");
            execute(game1[i]);
          }
        }

        delay(250);
      }
      else if (anPin == 5) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 31) {
            Serial.println("b31");
            execute(game1[i]);
          }
        }

        delay(250);
      }
            else if (anPin == 5) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 31) {
            Serial.println("b31");
            execute(game1[i]);
          }
        }

        delay(250);
      }
    }
    else if (dato > 330 && dato < 350) {
      if (anPin == 0) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 2) {
            Serial.println("b2");
            execute(game1[i]);
          }
        }
        delay(250);
      }
      else if (anPin == 1) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 8) {
            Serial.println("b8");
            execute(game1[i]);
          }
        }

        delay(250);
      }
      else if (anPin == 2) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 14) {
            Serial.println("b14");
            execute(game1[i]);
          }
        }


        delay(250);
      }
      else if (anPin == 3) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 20) {
            Serial.println("b20");
            execute(game1[i]);
          }
        }

        delay(250);
      }
      else if (anPin == 4) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 26) {
            Serial.println("b26");
            execute(game1[i]);
          }
        }

        delay(250);
      }
      else if (anPin == 5) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 32) {
            Serial.println("b32");
            execute(game1[i]);
          }
        }

        delay(250);
      }
    }

    else if (dato > 244 && dato < 264) {
      if (anPin == 0) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 3) {
            Serial.println("b3");
            execute(game1[i]);
          }
        }
        delay(250);
      }
      else if (anPin == 1) {

        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 9) {
            Serial.println("b9");
            execute(game1[i]);
          }
        }


        delay(250);
      }
      else if (anPin == 2) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 15) {
            Serial.println("b15");
            execute(game1[i]);
          }
        }

        delay(250);
      }
      else if (anPin == 3) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 21) {
            Serial.println("b21");
            execute(game1[i]);
          }
        }

        delay(250);
      }
      else if (anPin == 4) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 27) {
            Serial.println("b27");
            execute(game1[i]);
          }
        }

        delay(250);
      }
      else if (anPin == 5) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 33) {
            Serial.println("b33");
            execute(game1[i]);
          }
        }

        delay(250);
      }
    }
    else if (dato > 190 && dato < 210) {
      if (anPin == 0) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 4) {
            Serial.println("b4");
            execute(game1[i]);
          }
        }
        delay(250);
      }
      else if (anPin == 1) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 10) {
            Serial.println("b10");
            execute(game1[i]);
          }
        }

        delay(250);
      }
      else if (anPin == 2) {

        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 16) {
            Serial.println("b16");
            execute(game1[i]);
          }
        }

        delay(250);
      }
      else if (anPin == 3) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 22) {
            Serial.println("b22");
            execute(game1[i]);
          }
        }

        delay(250);
      }
      else if (anPin == 4) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 28) {
            Serial.println("b28");
            execute(game1[i]);
          }
        }

        delay(250);
      }
      else if (anPin == 5) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 34) {
            Serial.println("b34");
            execute(game1[i]);
          }
        }

        delay(250);
      }
    }
    else if (dato > 150 && dato < 185) {
      if (anPin == 0) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 5) {
            Serial.println("b5");
            execute(game1[i]);

          }
        }
        delay(250);
      }
      else if (anPin == 1) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 11) {
            Serial.println("b11");
            execute(game1[i]);
          }
        }


        delay(250);
      }
      else if (anPin == 2) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 17) {
            Serial.println("b17");
            execute(game1[i]);
          }
        }


        delay(250);
      }
      else if (anPin == 3) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 23) {
            Serial.println("b23");
            execute(game1[i]);
          }
        }

        delay(250);
      }
      else if (anPin == 4) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 29) {
            Serial.println("b29");
            execute(game1[i]);
          }
        }

        delay(250);
      }
      else if (anPin == 5) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 35) {
            Serial.println("b35");
            execute(game1[i]);
          }
        }

        delay(250);
      }
    }
    else if (dato > 135 && dato < 148) {
      if (anPin == 0) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 6) {
            Serial.println("b6");
            execute(game1[i]);
          }
        }


        delay(250);
      }

      else if (anPin == 1) {



        delay(250);
      }

      else if (anPin == 2) {




        delay(250);
      }
      else if (anPin == 3) {




        delay(250);
      }
      else if (anPin == 4) {



        delay(250);
      }
      else if (anPin == 5) {




        delay(250);
      }
    }

  }
}

void mazeButton(int anPin, int dato) {
  if (vidas > 0) {
    if (dato > 100) {
      if (dato > 500 && dato < 520) {
        if (anPin == 0) {
          Serial.println("b1");
          goMaze();
          for(int i =0; i<6; i++){
            for(int j=0;j<6;j++){
              Serial.println(matriz[i][j]);
            }
          }
          pixels.setPixelColor(0, pixels.Color(0, 0, 255));
          pixels.show();
          matriz[0][0] = 0;

          delay(250);
        }

        else if (anPin == 1) {
          Serial.println("b7");
                    Serial.println("........................MATRIZ");
                     for(int i =0; i<6; i++){
            for(int j=0;j<6;j++){
              Serial.println(matriz[i][j]);
            }
          }
                              
          if (matriz[0][0] == 1 || /*matriz[1][1] == 1 || matriz[2][0] == 1 || matriz[0][1] == 1 || matriz[2][1] == 1 ||*/ matriz[1][0]==0) {
            Serial.print("entra aqui puta");
            pixels.setPixelColor(11, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[1][0] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              Serial.print(" aqui no puta");
              pixels.setPixelColor(11, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[1][0] = 0;

            }

          }
          delay(250);
        }

        else if (anPin == 2) {
          Serial.println("b13");
          if (matriz[1][0] == 1 || matriz[1][1] == 1 || matriz[2][1] == 1 || matriz[3][1] == 1 || matriz[3][0] == 1 || matriz[2][0]==0) {
            pixels.setPixelColor(12, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[2][0] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(12, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[2][0] = 0;

            }

          }
          delay(250);
        }
        else if (anPin == 3) {
          Serial.println("b19");
          if (matriz[2][0] == 1 || matriz[4][0] == 1 || matriz[2][1] == 1 || matriz[3][1] == 1 || matriz[4][1] == 1 || matriz[3][0]==0) {
            pixels.setPixelColor(23, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[3][0] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(23, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[3][0] = 0;

            }

          }
          delay(250);
        }
        else if (anPin == 4) {
          Serial.println("b25");
          if (matriz[3][0] == 1 || matriz[5][0] == 1 || matriz[5][1] == 1 || matriz[3][1] == 1 || matriz[4][1] == 1 || matriz[4][0]==0) {
            pixels.setPixelColor(24, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[4][0] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(24, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[4][0] = 0;

            }

          }
          delay(250);
        }
        else if (anPin == 5) {
          Serial.println("b31");
          if (matriz[4][0] == 1 || matriz[5][1] == 1 ||  matriz[4][1] == 1 || matriz[1][0]==0 || matriz[5][0]==0) {
            pixels.setPixelColor(35, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[5][0] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(35, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[5][0] = 0;

            }

          }
          delay(250);
        }
        else if (anPin == 6) {
          Serial.println("CHECK");
          goMaze();
                        for(int i=0; i<36; i++){
                 pixels.setPixelColor(i,pixels.Color(0, 0, 0));
                 pixels.show();
                
              }
          delay(250);
        }
      }
      else if (dato > 330 && dato < 350) {
        if (anPin == 0) {
          Serial.println("b2");
          if (matriz[0][0] == 1 || matriz[0][2] == 1 || matriz[1][0] == 1 || matriz[1][1] == 1 || matriz[1][2] == 1 || matriz[0][1]==0) {
            pixels.setPixelColor(1, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[0][1] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(1, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[0][1] = 0;

            }

          }
          delay(250);
        }

        else if (anPin == 1) {
          Serial.println("b8");
          if ((matriz[0][0] == 1) || (matriz[1][2] == 1) || (matriz[0][2] == 1) || (matriz[2][0] == 1) || (matriz[2][2] == 1) || (matriz[0][1] == 1) || (matriz[2][1] == 1) || (matriz[1][0] == 1) || matriz[1][1]==0) {
            pixels.setPixelColor(10, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[1][1] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(10, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[1][1] = 0;

            }

          }

          delay(250);
        }

        else if (anPin == 2) {
          Serial.println("b14");
          if (matriz[1][0] == 1 || matriz[2][0] || matriz[1][1] == 1 || matriz[1][2] == 1 || matriz[3][2] == 1 || matriz[2][2] == 1 || matriz[3][1] == 1 || matriz[3][0] == 1 || matriz[2][1]==0) {
            pixels.setPixelColor(13, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[2][1] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(13, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[2][1] = 0;

            }

          }

          delay(250);
        }
        else if (anPin == 3) {
          Serial.println("b20");
          if (matriz[2][0] == 1 || matriz[4][0] == 1 || matriz[2][1] == 1 || matriz[3][2] == 1 || matriz[4][2] == 1 || matriz[3][0] == 1 || matriz[2][2] == 1 || matriz[4][1] == 1 || matriz[3][1]==0) {
            pixels.setPixelColor(22, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[3][1] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(22, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[3][1] = 0;

            }

          }

          delay(250);
        }
        else if (anPin == 4) {
          Serial.println("b26");
          if (matriz[4][0] = 1 || matriz[3][0] == 1 || matriz[5][0] == 1 || matriz[5][1] == 1 || matriz[3][1] == 1 || matriz[5][2] == 1 || matriz[3][2] == 1 || matriz[4][2] == 1 || matriz[4][1]==0) {
            pixels.setPixelColor(25, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[4][1] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(25, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[4][1] = 0;

            }

          }

          delay(250);
        }
        else if (anPin == 5) {
          Serial.println("b32");
          if (matriz[4][0] == 1 || matriz[5][0] == 1 ||  matriz[4][1] == 1 || matriz[4][2] == 1 || matriz[5][2] == 1 || matriz[5][1]==0) {
            pixels.setPixelColor(34, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[5][1] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(34, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[5][1] = 0;

            }

          }

          delay(250);
        }
      }

      else if (dato > 244 && dato < 264) {
        if (anPin == 0) {
          Serial.println("b3");
          if (matriz[0][1] == 1 || matriz[0][3] == 1 || matriz[1][1] == 1 || matriz[1][3] == 1 || matriz[1][2] == 1 || matriz[0][2]==0) {
            pixels.setPixelColor(2, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[0][2] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(2, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[0][2] = 0;

            }

          }
          delay(250);
        }

        else if (anPin == 1) {
          Serial.println("b9");
          if (matriz[1][3] == 1 || matriz[0][1] == 1 || matriz[1][2] == 1 || matriz[0][2] == 1 || matriz[2][1] == 1 || matriz[2][2] == 1 || matriz[0][3] == 1 || matriz[2][3] == 1 || matriz[1][2]==0) {
            pixels.setPixelColor(9, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[1][2] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(9, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[1][2] = 0;

            }

          }
          delay(250);
        }

        else if (anPin == 2) {
          Serial.println("b15");
          if (matriz[2][3] == 1 || matriz[1][3] == 1 || matriz[1][1] == 1 || matriz[1][2] == 1 || matriz[3][2] == 1 || matriz[2][3] == 1 || matriz[3][1] == 1 || matriz[3][3] == 1 || matriz[2][2]==0) {
            pixels.setPixelColor(14, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[2][2] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(14, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[2][2] = 0;

            }

          }

          delay(250);
        }
        else if (anPin == 3) {
          Serial.println("b21");
          if (matriz[2][3] == 1 || matriz[4][3] == 1 || matriz[2][1] == 1 || matriz[3][3] == 1 || matriz[4][2] == 1 || matriz[3][2] == 1 || matriz[2][2] == 1 || matriz[4][1] == 1 || matriz[3][2]==0) {
            pixels.setPixelColor(21, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[3][2] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(21, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[3][2] = 0;

            }

          }
          delay(250);
        }
        else if (anPin == 4) {
          Serial.println("b27");
          if (matriz[4][3] == 1 || matriz[3][2] == 1 || matriz[5][3] == 1 || matriz[5][1] == 1 || matriz[3][1] == 1 || matriz[5][2] == 1 || matriz[3][3] == 1 || matriz[4][1] == 1 || matriz[4][2]==0) {
            pixels.setPixelColor(26, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[4][2] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(26, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[4][2] = 0;

            }

          }

          delay(250);
        }
        else if (anPin == 5) {
          Serial.println("b33");
          if (matriz[4][2] == 1 || matriz[5][1] == 1 ||  matriz[4][1] == 1 || matriz[4][3] == 1 || matriz[5][3] == 1 || matriz[5][2]==0) {
            pixels.setPixelColor(33, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[5][2] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(33, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[5][2] = 0;

            }

          }

          delay(250);
        }
      }

      else if (dato > 190 && dato < 210) {
        if (anPin == 0) {
          Serial.println("b4");
          if (matriz[0][2] == 1 || matriz[0][4] == 1 || matriz[1][2] == 1 || matriz[1][3] == 1 || matriz[1][4] == 1 || matriz[0][3]==0) {
            pixels.setPixelColor(3, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[0][3] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(3, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[0][3] = 0;

            }

          }
          delay(250);
        }

        else if (anPin == 1) {
          Serial.println("b10");
          if (matriz[1][4] == 1 || matriz[0][2] == 1 || matriz[1][2] == 1 || matriz[0][4] == 1 || matriz[2][2] == 1 || matriz[2][4] == 1 || matriz[0][3] == 1 || matriz[2][3] == 1 || matriz[1][3]==0) {
            pixels.setPixelColor(8, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[1][3] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(8, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[1][3] = 0;

            }

          }

          delay(250);
        }

        else if (anPin == 2) {
          Serial.println("b16");
          if (matriz[2][4] == 1 || matriz[1][3] == 1 || matriz[1][4] == 1 || matriz[1][2] == 1 || matriz[3][2] == 1 || matriz[2][3] == 1 || matriz[3][3] == 1 || matriz[3][4] == 1 || matriz[2][3]==0) {
            pixels.setPixelColor(15, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[2][3] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(15, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[2][3] = 0;

            }

          }

          delay(250);
        }
        else if (anPin == 3) {
          Serial.println("b22");
          if (matriz[2][3] == 1 || matriz[4][3] == 1 || matriz[2][2] == 1 || matriz[3][4] == 1 || matriz[4][2] == 1 || matriz[3][2] == 1 || matriz[2][4] == 1 || matriz[4][4] == 1 || matriz[3][3]==0) {
            pixels.setPixelColor(20, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[3][3] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(20, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[3][3] = 0;

            }

          }

          delay(250);
        }
        else if (anPin == 4) {
          Serial.println("b28");
          if (matriz[4][4] == 1 || matriz[3][2] == 1 || matriz[5][3] == 1 || matriz[5][2] == 1 || matriz[3][3] == 1 || matriz[5][4] == 1 || matriz[3][4] == 1 || matriz[4][2] == 1 | matriz[4][3]==0) {
            pixels.setPixelColor(27, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[4][3] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(27, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[4][3] = 0;

            }

          }
          delay(250);
        }
        else if (anPin == 5) {
          Serial.println("b34");
          if (matriz[4][2] == 1 || matriz[5][2] == 1 ||  matriz[4][4] == 1 || matriz[4][3] == 1 || matriz[5][4] == 1 || matriz[5][3]==0) {
            pixels.setPixelColor(32, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[5][3] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(32, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[5][3] = 0;

            }

          }
          delay(250);
        }

      }
      else if (dato > 150 && dato < 185) {
        if (anPin == 0) {
          Serial.println("b5");
          if (matriz[0][3] == 1 || matriz[0][5] == 1 || matriz[1][4] == 1 || matriz[1][3] == 1 || matriz[1][5] == 1 || matriz[0][4]==0) {
            pixels.setPixelColor(4, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[0][4] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(4, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[0][4] = 0;

            }

          }
          delay(250);
        }
        else if (anPin == 1) {
          Serial.println("b11");
          if (matriz[1][5] == 1 || matriz[0][4] == 1 || matriz[1][3] == 1 || matriz[0][5] == 1 || matriz[2][3] == 1 || matriz[2][4] == 1 || matriz[0][3] == 1 || matriz[2][5] == 1 || matriz[1][4]==0) {
            pixels.setPixelColor(7, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[1][4] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(7, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[1][4] = 0;

            }

          }
          delay(250);
        }
        else if (anPin == 2) {
          Serial.println("b17");
          if (matriz[2][5] == 1 || matriz[1][3] == 1 || matriz[1][4] == 1 || matriz[1][5] == 1 || matriz[3][5] == 1 || matriz[2][3] == 1 || matriz[3][3] == 1 || matriz[3][4] == 1 || matriz[2][4]==0) {
            pixels.setPixelColor(16, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[2][4] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(16, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[2][4] = 0;

            }

          }
          delay(250);
        }
        else if (anPin == 3) {
          Serial.println("b23");
          if (matriz[2][3] == 1 || matriz[4][3] == 1 || matriz[2][5] == 1 || matriz[3][3] == 1 || matriz[4][5] == 1 || matriz[3][5] == 1 || matriz[2][4] == 1 || matriz[4][4] == 1 || matriz[3][4]==0) {
            pixels.setPixelColor(19, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[3][4] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(19, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[3][4] = 0;

            }

          }
          delay(250);
        }
        else if (anPin == 4) {
          Serial.println("b29");
          if (matriz[4][3] == 1 || matriz[3][5] == 1 || matriz[5][3] == 1 || matriz[5][5] == 1 || matriz[3][3] == 1 || matriz[5][4] == 1 || matriz[3][4] == 1 || matriz[4][5] == 1 || matriz[4][4]==0) {
            pixels.setPixelColor(28, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[4][4] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(28, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[4][4] = 0;

            }

          }
          delay(250);
        }
        else if (anPin == 5) {
          Serial.println("b35");
          if (matriz[4][5] == 1 || matriz[5][3] == 1 ||  matriz[4][4] == 1 || matriz[4][3] == 1 || matriz[5][5] == 1 || matriz[5][4]==0) {
            pixels.setPixelColor(31, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[5][4] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(31, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[5][4] = 0;

            }

          }

          delay(250);
        }
      }
      else if (dato > 135 && dato < 148) {
        if (anPin == 0) {
          Serial.println("b6");
          if (matriz[0][4] == 1 || matriz[1][4] == 1 || matriz[1][5] == 1 || matriz[0][5]==0) {
            pixels.setPixelColor(5, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[0][5] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(5, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[0][5] = 0;

            }

          }
          delay(250);
        }

        else if (anPin == 1) {
          Serial.println("b12");
          if (matriz[1][4] == 1 || matriz[0][4] == 1 || matriz[2][4] == 1 || matriz[0][5] == 1 || matriz[2][5] == 1 || matriz[1][5]==0) {
            pixels.setPixelColor(6, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[1][5] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(6, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[1][5] = 0;

            }

          }

          delay(250);
        }

        else if (anPin == 2) {
          Serial.println("b18");
          if (matriz[2][4] == 1  || matriz[1][4] == 1 || matriz[1][5] == 1 || matriz[3][5] == 1  || matriz[3][4] == 1 || matriz[2][5]==0) {
            pixels.setPixelColor(17, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[2][5] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(17, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[2][5] = 0;

            }
          }
          delay(250);
        }
        else if (anPin == 3) {
          Serial.println("b24");
          if (matriz[2][5] == 1 || matriz[3][4] == 1 || matriz[4][5] == 1 || matriz[2][4] == 1 || matriz[4][4] == 1 || matriz[3][5]==0) {
            pixels.setPixelColor(18, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[3][5] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(18, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[3][5] = 0;

            }

          }
          delay(250);
        }
        else if (anPin == 4) {
          Serial.println("b30");
          if (matriz[4][4] == 1 || matriz[3][5] == 1  || matriz[5][5] == 1  || matriz[5][4] == 1 || matriz[3][4] == 1 || matriz[4][5]==0) {
            pixels.setPixelColor(29, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[4][5] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(29, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[4][5] = 0;

            }

          }
          delay(250);
        }
        else if (anPin == 5) {
          Serial.println("b36");
          if (matriz[4][5] == 1 || matriz[5][4] == 1 ||  matriz[4][4] == 1 || matriz[5][5]==0) {
            pixels.setPixelColor(30, pixels.Color(255, 0, 0));
            pixels.show();
            vidas--;
          }
          else {
            if (matriz[5][5] == 6) {
              writeDown("WIN", 0, 255, 0);
            }
            else {
              pixels.setPixelColor(30, pixels.Color(0, 0, 255));
              pixels.show();
              matriz[5][5] = 0;

            }

          }

          delay(250);
        }
      }
    }

  }
  else {
    writeDown("LOSE", 255, 0, 0);
    goMaze();
    Serial.print("LOSE");

    vidas = 3;
  }
}

void turnLED(int col, int fil, int r, int g, int b) {
  //  ------------------------------------ -FILA 0---------------------------------------- -
  if (fil == 0) {
    if (col == 0) {
      pixels.setPixelColor(0, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(100);

    }
    else if (col == 1) {
      pixels.setPixelColor(1, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 2) {
      pixels.setPixelColor(2, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 3) {
      pixels.setPixelColor(3, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 4) {
      pixels.setPixelColor(4, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 5) {
      pixels.setPixelColor(5, pixels.Color(r, g, b));
      pixels.show();
    }
  }

  //  ------------------------------------ -FILA 1---------------------------------------- -
  if (fil == 1) {
    if (col == 0) {
      pixels.setPixelColor(11, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 1) {
      pixels.setPixelColor(10, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 2) {
      pixels.setPixelColor(9, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 3) {
      pixels.setPixelColor(8, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 4) {
      pixels.setPixelColor(7, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 5) {
      pixels.setPixelColor(6, pixels.Color(r, g, b));
      pixels.show();
    }
  }

  //  ------------------------------------ -FILA 2---------------------------------------- -
  if (fil == 2) {
    if (col == 0) {
      pixels.setPixelColor(12, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 1) {
      pixels.setPixelColor(13, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 2) {
      pixels.setPixelColor(14, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 3) {
      pixels.setPixelColor(15, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 4) {
      pixels.setPixelColor(16, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 5) {
      pixels.setPixelColor(17, pixels.Color(r, g, b));
      pixels.show();
    }
  }

  //  ------------------------------------ -FILA 3---------------------------------------- -
  if (fil == 3) {
    if (col == 0) {
      pixels.setPixelColor(23, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 1) {
      pixels.setPixelColor(22, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 2) {
      pixels.setPixelColor(21, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 3) {
      pixels.setPixelColor(20, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 4) {
      pixels.setPixelColor(19, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 5) {
      pixels.setPixelColor(18, pixels.Color(r, g, b));
      pixels.show();
    }
  }

  //------------------------------------ -FILA 4---------------------------------------- -
  if (fil == 4) {
    if (col == 0) {
      pixels.setPixelColor(24, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 1) {
      pixels.setPixelColor(25, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 2) {
      pixels.setPixelColor(26, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 3) {
      pixels.setPixelColor(27, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 4) {
      pixels.setPixelColor(28, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 5) {
      pixels.setPixelColor(29, pixels.Color(r, g, b));
      pixels.show();
    }
  }

  //------------------------------------ -FILA 5-----------------------------------------
  if (fil == 5) {
    if (col == 0) {
      pixels.setPixelColor(35, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 1) {
      pixels.setPixelColor(34, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 2) {
      pixels.setPixelColor(33, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 3) {
      pixels.setPixelColor(32, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 4) {
      pixels.setPixelColor(31, pixels.Color(r, g, b));
      pixels.show();
    }
    else if (col == 5) {
      pixels.setPixelColor(30, pixels.Color(r, g, b));
      pixels.show();
    }
  }
}

//________________________________TURNONALLLEDSBYBOTTON_______________________________________
//_____________________________________________________________________________________________
//_____________________________________________________________________________________________
//_____________________________________________________________________________________________
void turnALL(int col, int fil) {
  //  ------------------------------------ -FILA 0---------------------------------------- -
  if (fil == 0) {
    if (col == 0) {
      pixels.setPixelColor(0, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(3, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(11, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(12, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(23, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(24, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(35, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.

      //      delay(100);
      //      pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Moderately bright green color.
      //      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 1) {
      pixels.setPixelColor(0, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(3, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.

    }
    else if (col == 2) {
      pixels.setPixelColor(0, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(3, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 3) {
      pixels.setPixelColor(0, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show();
      pixels.setPixelColor(3, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 4) {
      pixels.setPixelColor(0, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show();
      pixels.setPixelColor(3, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.

    }
    else if (col == 5) {
      pixels.setPixelColor(0, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show();
      pixels.setPixelColor(3, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(245, 7, 7)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.

    }
  }

  //  ------------------------------------ -FILA 1---------------------------------------- -
  if (fil == 1) {
    int r = 251;
    int g = 255;
    int b = 0;
    if (col == 0) {
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(0, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.

    }
    else if (col == 1) {
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.

    }
    else if (col == 2) {
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 3) {
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(3, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 4) {
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 5) {
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
  }

  //  ------------------------------------ -FILA 2---------------------------------------- -
  if (fil == 2) {
    int r = 0;
    int g = 39;
    int b = 255;

    if (col == 0) {
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(0, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.

    }
    else if (col == 1) {
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 2) {
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 3) {
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(3, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 4) {
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 5) {
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
  }

  //  ------------------------------------ -FILA 3---------------------------------------- -
  if (fil == 3) {
    int r = 255;
    int g = 0;
    int b = 243;
    if (col == 0) {
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(0, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 1) {
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 2) {
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 3) {
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(3, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 4) {
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 5) {
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
  }

  //------------------------------------ -FILA 4---------------------------------------- -
  if (fil == 4) {
    int r = 255;
    int g = 0;
    int b = 243;
    if (col == 0) {
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(0, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 1) {
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends te updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 2) {
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 3) {
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(3, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 4) {
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 5) {
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
  }

  //------------------------------------ -FILA 5-----------------------------------------
  if (fil == 5) {
    int r = 0.;
    int g = 255;
    int b = 228;
    if (col == 0) {
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(0, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 1) {
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 2) {
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 3) {
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(3, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 4) {
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 5) {
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends te updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
  }
}

//________________________________TURNoffALLEDSBYBOTTON_______________________________________
//_____________________________________________________________________________________________
//_____________________________________________________________________________________________
//_____________________________________________________________________________________________
void turnOFF(int col, int fil) {
  //  ------------------------------------ -FILA 0---------------------------------------- -
  if (fil == 0) {
    if (col == 0) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(3, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(11, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(12, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(23, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(24, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(35, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.

      //      delay(100);
      //      pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Moderately bright green color.
      //      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 1) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(3, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.

    }
    else if (col == 2) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(3, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 3) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show();
      pixels.setPixelColor(3, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 4) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show();
      pixels.setPixelColor(3, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.

    }
    else if (col == 5) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show();
      pixels.setPixelColor(3, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(0, 0, 0)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.

    }
  }

  //  ------------------------------------ -FILA 1---------------------------------------- -
  if (fil == 1) {
    int r = 0;
    int g = 0;
    int b = 0;
    if (col == 0) {
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(0, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.

    }
    else if (col == 1) {
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.

    }
    else if (col == 2) {
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 3) {
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(3, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 4) {
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 5) {
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
  }

  //  ------------------------------------ -FILA 2---------------------------------------- -
  if (fil == 2) {
    int r = 0;
    int g = 0;
    int b = 0;

    if (col == 0) {
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(0, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.

    }
    else if (col == 1) {
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 2) {
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 3) {
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(3, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 4) {
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 5) {
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
  }

  //  ------------------------------------ -FILA 3---------------------------------------- -
  if (fil == 3) {
    int r = 0;
    int g = 0;
    int b = 0;
    if (col == 0) {
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(0, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 1) {
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 2) {
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 3) {
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(3, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 4) {
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 5) {
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
  }

  //------------------------------------ -FILA 4---------------------------------------- -
  if (fil == 4) {
    int r = 0;
    int g = 0;
    int b = 0;
    if (col == 0) {
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(0, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 1) {
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends te updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 2) {
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 3) {
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(3, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 4) {
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 5) {
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
  }

  //------------------------------------ -FILA 5-----------------------------------------
  if (fil == 5) {
    int r = 0.;
    int g = 0;
    int b = 0;
    if (col == 0) {
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(0, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(11, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(12, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(23, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(24, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 1) {
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(1, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(10, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(13, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(22, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(25, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 2) {
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(2, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(9, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(14, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(21, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(26, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 3) {
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(3, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(8, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(15, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(20, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(27, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 4) {
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(4, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(7, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(16, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(19, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(28, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    else if (col == 5) {
      pixels.setPixelColor(35, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(34, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(33, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(32, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(31, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(30, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(5, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends te updated pixel color to the hardware.
      pixels.setPixelColor(6, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(17, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(18, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels.setPixelColor(29, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
  }
}

void execute(String json) {
  String type = parserFunction(json);
  if (type == "TurnOn") {
    parserTurnOn(json);
  }
  else if (type == "TurnON") {
    parserTurnON(json);
  }
  else if (type == "TurnOFF") {
    parserTurnOFF(json);
  }


}

void parserTurnOn(String json) {
  int col = parserCol(json);
  int fil = parserFil(json);
  int R = parserR(json);
  int G = parserG(json);
  int B = parserB(json);
  turnLED(col, fil, R, G, B);
  delay(200);
  turnLED(col, fil, 0, 0, 0);

}


void goMaze() {
  for (int i = 0; i < game2.size(); i++) {
    int col = parserCol(game2[i]);
    int fil = parserFil(game2[i]);

    if (i == game2.size() - 1) {
      matriz[fil][col] = 6; //fin del recorrido
    }
    else {
      matriz[fil][col] = 1;
    }
  }
}

int parserCol(String json) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  int col = root["Col"];
  return col;

}

int parserFil(String json) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  int fill = root["Fil"];
  return fill ;

}

int parserR(String json) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  int R = root["R"];
  return R;

}

int parserG(String json) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  int G = root["G"];
  return G;

}

int parserB(String json) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  int B = root["B"];
  return B;

}

void parserTurnON(String json) {
  int col = parserCol(json);
  int fil = parserFil(json);
  turnALL(col, fil);


}

void parserTurnOFF(String json) {
  int col = parserCol(json);
  int fil = parserFil(json);
  turnOFF(col, fil);

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

//................PARSERFUNCTION...............//

String parserFunction(String Json) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(Json);
  String type = root["Type"];
  return type;

}

String parserText(String json) {
  String scroll = parserScrollText(json);
  int R = parserR(json);
  int B = parserB(json);
  int G = parserG(json);
  writeDown(scroll, R, G, B);

}

String parserScrollText(String json) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  String type = root["Text"];
  delay(200);
  return type;

}


void scrollText() {
  for (int i = 0; i < game3.size(); i++) {
    parserText(game3[i]);
    delay(200);
  }
}

void writeDown(String data, int R, int G, int B) {
  char yourText[data.length() + 1];
  strcpy(yourText, data.c_str());
  maxDisplacement = strlen(yourText) * pixelPerChar + matrix.width();
  matrix.fillScreen(0);
  matrix.setCursor(x, -1);
  matrix.print(data);

  if (--x < -maxDisplacement) {
    x = matrix.width();
    if (++pass >= 3)
      pass = 0;
    matrix.setTextColor( matrix.Color(R, G, B));
  }
  matrix.show();
  delay(200);
}

//void slaveConnection(){
//    Wire.beginTransmission(8);
//    int dato=analogRead(0);
//    int dato1=analogRead(1);
//
//    botton(dato);
//    botton1(dato1);
//    //writeDown("Computadores!!");
//    delay(500);
//    for(int i=0;i<NUMPIXELS;i++){
//    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
//    pixels.show();
//    }
//    Wire.endTransmission();
//
//}





