#include <Wire.h>             // Set up connection master (arduino mega)/slave(arduino uno)
//Libraries to control Led Matrix
#include <Adafruit_GFX.h>       
#include <Adafruit_NeoMatrix.h> 
#include <Adafruit_NeoPixel.h>  
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN            6      //Pin where Din input from Leds is connected
#define NUMPIXELS      36     //How many Leds are in the Matrix
#include <Vector.h>


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);   //pixels is used to control individual leds
int delayval = 500;

//GAME 3----------------------------------------------------------------------------

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(6,6,4,1, 6,                          //matrix is used to control the scrolling text on game 3
  NEO_TILE_TOP   + NEO_TILE_LEFT   + NEO_TILE_ROWS   + NEO_TILE_ZIGZAG +
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_RGB);
 
const uint16_t colors[] = {                                                        //Array that contains led rgb colors to continously change them in each scrolling text
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(255, 255, 0),matrix.Color(0, 0, 255), 
  matrix.Color(255, 0, 255), matrix.Color(0, 255, 255), matrix.Color(255, 255, 255)};
int  pixelPerChar = 6;
int  maxDisplacement;
Vector <String> b1;
Vector <String> b2;
Vector <String> b3;
Vector <String> b4;
Vector <String> b5;
Vector <String> b6;
Vector <String> b7;
Vector <String> b8;
Vector <String> b9;
Vector <String> b10;
Vector <String> b11;
Vector <String> b12;
Vector <String> b13;
Vector <String> b14;
Vector <String> b15;
Vector <String> b16;
Vector <String> b17;
Vector <String> b18;
Vector <String> b19;
Vector <String> b20;
Vector <String> b21;
Vector <String> b22;
Vector <String> b23;
Vector <String> b24;
Vector <String> b25;
Vector <String> b26;
Vector <String> b27;
Vector <String> b28;
Vector <String> b29;
Vector <String> b30;
Vector <String> b31;
Vector <String> b32;
Vector <String> b33;
Vector <String> b34;
Vector <String> b35;
Vector <String> b36;
void setup() {
  Wire.begin();
  Serial.begin(9600);
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
    pixels.begin();
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(5);
  matrix.setTextColor(colors[0]);
  saveStatement(5,"perra");
}
int x    = matrix.width();
int pass = 0;

void loop() {
  
  Serial.println(b5[0]);
  delay(1000);

  
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

void saveStatement(int pos, String statement){

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
      Serial.println("B5:");
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
void botton (int dato){
    if (dato>100){

    if (dato>500 && dato <520){
      pixels.setPixelColor(0, pixels.Color( 249, 4, 49  ));
      pixels.show();
      Serial.println("b1");
      delay(50);}
      
   else if (dato>330 && dato <350){
      pixels.setPixelColor(1, pixels.Color( 249, 4, 49  ));
       pixels.show();
      Serial.println("b2");
      delay(50);}
      
   else if (dato>244 && dato <264){

      pixels.setPixelColor(2, pixels.Color( 249, 4, 49  ));
      pixels.show();
      Serial.println("b3");
      delay(50);}
      
    else if (dato>190 && dato <210){
      pixels.setPixelColor(3, pixels.Color( 249, 4, 49  ));
      pixels.show();
      Serial.println("b4");
      delay(50);}
    
   else if (dato>150 && dato <185){
      pixels.setPixelColor(4, pixels.Color( 249, 4, 49  ));
      pixels.show();
      Serial.println("b5");
      delay(50);}

   //else if (dato>130 && dato <145)
   else if (dato>135 && dato <148){
      pixels.setPixelColor(5, pixels.Color( 249, 4, 49  ));
      pixels.show();
      Serial.println("b6");
      delay(50);

    }
  }}
  void botton1 (int dato){
    if (dato>100){

    if (dato>500 && dato <520){
      pixels.setPixelColor(29, pixels.Color( 249, 4, 49  ));
      pixels.show();
      Serial.println("b1");
      delay(50);}
      
   else if (dato>330 && dato <350){
      pixels.setPixelColor(30, pixels.Color( 249, 4, 49  ));
      pixels.setPixelColor(8, pixels.Color( 249, 4, 49  ));
       pixels.show();
      Serial.println("b2");
      delay(50);}
      
   else if (dato>244 && dato <264){

      pixels.setPixelColor(31, pixels.Color( 249, 4, 49  ));
      pixels.show();
      Serial.println("b3");
      delay(50);}
      
    else if (dato>190 && dato <210){
      pixels.setPixelColor(32, pixels.Color( 249, 4, 49  ));
      pixels.show();
      Serial.println("b4");
      delay(50);}
    
   else if (dato>150 && dato <185){
      pixels.setPixelColor(33, pixels.Color( 249, 4, 49  ));
      pixels.show();
      Serial.println("b5");
      delay(50);}

   //else if (dato>130 && dato <145)
   else if (dato>135 && dato <148){
      pixels.setPixelColor(34, pixels.Color( 249, 4, 49  ));
      pixels.show();
      Serial.println("b6");
      delay(50);

    }
  }}

void writeDown(String data){
  char yourText[data.length()+1];
  strcpy(yourText, data.c_str());
  maxDisplacement = strlen(yourText) * pixelPerChar + matrix.width();
  matrix.fillScreen(0);
  matrix.setCursor(x, -1);
  matrix.print(F("Computadores !!"));
 
  if(--x < -maxDisplacement){
    x = matrix.width();
    if(++pass >= 3) 
    pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  delay(200);
}
