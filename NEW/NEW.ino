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
int flagGame = 1;
String value2;
String value1;

int dato1 = analogRead(1);
int dato2 = analogRead(2);
int dato3 = analogRead(3);
int dato4 = analogRead(4);
int dato5 = analogRead(5);
int dato6 = analogRead(6);
int dato7 = analogRead(7);






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

void loop() {
  if (BT1.available()) {
    readD();
    cleanVector();
  }
  if (flagGame == 1) { //RECORDAR MODIFICAR flagGame en pruebas
    int dato = analogRead(0);
    int dato2 = analogRead(1);
    onTouchButton(0, dato,flagGame);
    onTouchButton(1, dato2,flagGame);


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

void onTouchButton(int anPin, int dato, int game) {
  if (dato > 100) {
    if (dato > 500 && dato < 520) {
      if (anPin == 0) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 1) {
            Serial.println("b1");
            execute(game1[i], game);
            
          }
        }

        delay(250);
      }
      else if (anPin == 1) {
         for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 7) {
            Serial.println("b7");
            execute(game1[i],game);
          }
        }
       
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
    else if (dato > 330 && dato < 350) {
      if (anPin == 0) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 2) {
            Serial.println("b2");
            execute(game1[i],game);
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

    else if (dato > 244 && dato < 264) {
      if (anPin == 0) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 3) {
            Serial.println("b3");
            execute(game1[i],game);
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
    else if (dato > 190 && dato < 210) {
      if (anPin == 0) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 4) {
            Serial.println("b4");
            execute(game1[i],game);
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
    else if (dato > 150 && dato < 185) {
      if (anPin == 0) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 5) {
            Serial.println("b5");
            execute(game1[i],game);
            
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
    else if (dato > 135 && dato < 148) {
      if (anPin == 0) {
        for (int i = 0; i < game1.size(); i++) {
          if (parserBoton(game1[i]) == 6) {
            Serial.println("b6");
            execute(game1[i],game);
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
    int r =251;
    int g =255;
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
    int r =0;
    int g =39;
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
    int r =255;
    int g =0;
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
    int r =255;
    int g =0;
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
    int r =0.;
    int g =255;
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
    int r =0;
    int g =0;
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
    int r =0;
    int g =0;
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
    int r =0;
    int g =0;
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
    int r =0;
    int g =0;
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
    int r =0.;
    int g =0;
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

void execute(String json, int game){
  String type = parserFunction(json);
  if(game==1){
      if (type == "TurnOn"){
    parserTurnOn(json);
  }
  else if(type == "TurnON"){
    parserTurnON(json);
  }
   else if(type == "TurnOFF"){
    parserTurnOFF(json);
  }
    
  }
  else if(game==2){
    parserMaze(json);
  }

}

void parserTurnOn(String json){
  int col = parserCol(json);
  int fil = parserFil(json);
  int R = parserR(json);
  int G = parserG(json);
  int B = parserB(json);
  turnLED(col,fil,R,G,B);
  delay(200);
  turnLED(col,fil,0,0,0); 
  
}

void parserMaze(String json){
    int col = parserCol(json);
    int fil = parserFil(json);
    int R = parserR(json);
    int G = parserG(json);
    int B = parserB(json);
    goMaze(col,fil,R,G,B);
  
}

void goMaze(int col, int fil, int r, int g, int b){
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

int parserCol(String json){
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  int col = root["Col"];
  return col;
  
}

int parserFil(String json){
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  int fill = root["Fil"];
  return fill ;
  
}

int parserR(String json){
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  int R = root["R"];
  return R;
  
}

int parserG(String json){
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  int G = root["G"];
  return G;
  
}

int parserB(String json){
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  int B = root["B"];
  return B;
  
}

void parserTurnON(String json){
  int col = parserCol(json);
  int fil = parserFil(json);
  turnALL(col,fil);

  
}

void parserTurnOFF(String json){
  int col = parserCol(json);
  int fil = parserFil(json);
  turnOFF(col,fil);
  
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





