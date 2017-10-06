#include <Wire.h>             // Set up connection master (arduino mega)/slave(arduino uno)
#include <Vector.h>
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

//-------------------------------Vectors for each button that contains every statement to execute-------------------------------------------------
Vector <String> b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15, b16, b17, b18, b19, b20, b21, b22, b23, b24, b25, b26, b27, b28, b29, b30, b31, b32, b33, b34, b35, b36;

void setup() {
  Wire.begin();
  Serial.begin(9600);
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
  saveStatement(7, "perra2");
  saveStatement(5, "perra1");
 }
int x    = matrix.width();
int pass = 0;

void loop() {
  delay(1000);
  int dato = analogRead(0);
  int dato2 = analogRead(1);
  onTouchButton(0, dato);
  onTouchButton(1, dato2);
  /*
    Wire.beginTransmission(8);
    int dato=analogRead(0);
    int dato1=analogRead(1);

    botton(dato);
    botton1(dato1);
    //writeDown("Computadores!!");
    delay(500);
    for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();
    }
    Wire.endTransmission();
  */
}

void onTouchButton(int anPin, int dato) {
  if (dato > 100) {
    if (dato > 500 && dato < 520) {
      if (anPin == 0) {
        Serial.println(b1[0]);
        delay(250);
      }
      else if (anPin == 1) {
        Serial.println(b7[0]);
        delay(250);
      }
      else if (anPin == 2) {
        Serial.println(b13[0]);
        delay(250);
      }
      else if (anPin == 3) {
        Serial.println(b19[0]);
        delay(250);
      }
      else if (anPin == 4) {
        Serial.println(b25[0]);
        delay(250);
      }
      else if (anPin == 5) {
        Serial.println(b31[0]);
        delay(250);
      }
    }
    else if (dato > 330 && dato < 350) {
      if (anPin == 0) {
        Serial.println(b2[0]);
        delay(250);
      }
      else if (anPin == 1) {
        Serial.println(b8[0]);
        delay(250);
      }
      else if (anPin == 2) {
        Serial.println(b14[0]);
        delay(250);
      }
      else if (anPin == 3) {
        Serial.println(b20[0]);
        delay(250);
      }
      else if (anPin == 4) {
        Serial.println(b26[0]);
        delay(250);
      }
      else if (anPin == 5) {
        Serial.println(b32[0]);
        delay(250);
      }
    }

    else if (dato > 244 && dato < 264) {
      if (anPin == 0) {
        Serial.println(b3[0]);
        delay(250);
      }
      else if (anPin == 1) {
        Serial.println(b9[0]);
        delay(250);
      }
      else if (anPin == 2) {
        Serial.println(b15[0]);
        delay(250);
      }
      else if (anPin == 3) {
        Serial.println(b21[0]);
        delay(250);
      }
      else if (anPin == 4) {
        Serial.println(b27[0]);
        delay(250);
      }
      else if (anPin == 5) {
        Serial.println(b33[0]);
        delay(250);
      }
    }
    else if (dato > 190 && dato < 210) {
      if (anPin == 0) {
        Serial.println(b4[0]);
        delay(250);
      }
      else if (anPin == 1) {
        Serial.println(b10[0]);
        delay(250);
      }
      else if (anPin == 2) {
        Serial.println(b16[0]);
        delay(250);
      }
      else if (anPin == 3) {
        Serial.println(b22[0]);
        delay(250);
      }
      else if (anPin == 4) {
        Serial.println(b28[0]);
        delay(250);
      }
      else if (anPin == 5) {
        Serial.println(b34[0]);
        delay(250);
      }
    }
    else if (dato > 150 && dato < 185) {
      if (anPin == 0) {
        Serial.println(b5[0]);
        delay(250);
      }
      else if (anPin == 1) {
        Serial.println(b11[0]);
        delay(250);
      }
      else if (anPin == 2) {
        Serial.println(b17[0]);
        delay(250);
      }
      else if (anPin == 3) {
        Serial.println(b23[0]);
        delay(250);
      }
      else if (anPin == 4) {
        Serial.println(b29[0]);
        delay(250);
      }
      else if (anPin == 5) {
        Serial.println(b35[0]);
        delay(250);
      }
    }
    else if (dato > 135 && dato < 148) {
      if (anPin == 0) {
        Serial.println(b6[0]);
        delay(250);
      }
      else if (anPin == 1) {
        Serial.println(b12[0]);
        delay(250);
      }
      else if (anPin == 2) {
        Serial.println(b18[0]);
        delay(250);
      }
      else if (anPin == 3) {
        Serial.println(b24[0]);
        delay(250);
      }
      else if (anPin == 4) {
        Serial.println(b30[0]);
        delay(250);
      }
      else if (anPin == 5) {
        Serial.println(b36[0]);
        delay(250);
      }
    }
  }
}


void writeDown(String data) {
  char yourText[data.length() + 1];
  strcpy(yourText, data.c_str());
  maxDisplacement = strlen(yourText) * pixelPerChar + matrix.width();
  matrix.fillScreen(0);
  matrix.setCursor(x, -1);
  matrix.print(F(data));

  if (--x < -maxDisplacement) {
    x = matrix.width();
    if (++pass >= 3)
      pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  delay(200);
}

void saveStatement(int pos, String statement) {
  switch (pos) {
    case 1:
      b1.push_back(statement);
      break;
    case 2:
      b2.push_back(statement);
      break;
    case 3:
      b3.push_back(statement);
      break;
    case 4:
      b4.push_back(statement);
      break;
    case 5:
      b5.push_back(statement);
      break;
    case 6:
      b6.push_back(statement);
      break;
    case 7:
      b7.push_back(statement);
      break;
    case 8:
      b8.push_back(statement);
      break;
    case 9:
      b9.push_back(statement);
      break;
    case 10:
      b10.push_back(statement);
      break;
    case 11:
      b11.push_back(statement);
      break;
    case 12:
      b12.push_back(statement);
      break;
    case 13:
      b13.push_back(statement);
      break;
    case 14:
      b14.push_back(statement);
      break;
    case 15:
      b15.push_back(statement);
      break;
    case 16:
      b16.push_back(statement);
      break;
    case 17:
      b17.push_back(statement);
      break;
    case 18:
      b18.push_back(statement);
      break;
    case 19:
      b19.push_back(statement);
      break;
    case 20:
      b20.push_back(statement);
      break;
    case 21:
      b21.push_back(statement);
      break;
    case 22:
      b22.push_back(statement);
      break;
    case 23:
      b24.push_back(statement);
      break;
    case 25:
      b25.push_back(statement);
      break;
    case 26:
      b26.push_back(statement);
      break;
    case 27:
      b27.push_back(statement);
      break;
    case 28:
      b28.push_back(statement);
      break;
    case 29:
      b29.push_back(statement);
      break;
    case 30:
      b30.push_back(statement);
      break;
    case 31:
      b31.push_back(statement);
      break;
    case 32:
      b32.push_back(statement);
      break;
    case 33:
      b33.push_back(statement);
      break;
    case 34:
      b34.push_back(statement);
      break;
    case 35:
      b35.push_back(statement);
      break;
    default:
      b36.push_back(statement);
      break;
  }
}

void turnLed(int col, int fil, int r, int g, int b) {
//  ------------------------------------ -FILA 0---------------------------------------- -
  if (fil == 0) {
    if (col == 0) {
      pixels.setPixelColor(0, pixels.Color(r, g, b)); // Moderately bright green color.
      pixels.show(); // This sends the updated pixel color to the hardware.
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

void sendSound(int track) {
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(track);
  Wire.endTransmission();
}
void readJson() {
  char json[] = "[\"A\",\"B\",\"C\"]";
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
 
}
