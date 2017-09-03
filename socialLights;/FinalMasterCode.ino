#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUM_LEDS 80

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

const int SlaveA = 12; //Slave arduino ID 11
const int SlaveB = 18; //Slave arduino ID 18 
const int SlaveC = 15; //Slave arduino ID 15
const int SlaveD = 17; //Slave arduino ID 17


int collisionA = 0;
int collisionB = 0;
int collisionC = 0;
int collisionD = 0;

int SpeedDelay = 50;
int ReturnDelay = 50;
char Code;
int PositionA = 0;
int ColourA = 0;
int PositionB = 0;
int ColourB = 0;
int PositionC = 0;
int ColourC = 0;
int PositionD = 0;
int ColourD = 0;

int oldPositionA = 0;
int oldPositionB = 0;
int oldPositionC = 0;
int oldPositionD = 0;





void setup ()
{
    Wire.begin(8);  
    Serial.begin (115200); 
    //Wire.onReceive(receiveEvent);
    strip.begin();
    delay(10000);
}
  
void loop()
{   
    Serial.println(millis());
    pullSlaves();

              //update the led strip
              setAll(0, 0, 0); //blank the strip
              setPixel(PositionA, 0, ColourA, 0); //Green
              setPixel(PositionB, ColourB, 0, ColourB); //Purple
              setPixel(PositionC, 0, ColourC, ColourC); //Aqua
              setPixel(PositionD, ColourD, ColourD, 0); //Yellow
              strip.show(); 

              //start checking for collisions
              collisionA = 0;
              collisionB = 0;
              collisionC = 0;
              collisionD = 0;

              
              //below code writes collision code to slaves when collision occurs
               
              if(PositionA == PositionB)
              { 
                if(oldPositionA != PositionA) //makes sure there is no repeated firing of messages when they collision occurs
                { 
                collisionA = 231; //number values for collisions only used as a code to make clear what the values stand for
                Wire.beginTransmission(SlaveA);
                Wire.write(collisionA);
                Wire.endTransmission();
                delay(1);
                collisionB = 231;
                Wire.beginTransmission(SlaveB);
                Wire.write(collisionB);
                Wire.endTransmission();
                delay(1);
                oldPositionA = PositionA;
                }
              }
              
              if(PositionA == PositionC)
              {
                if(oldPositionA != PositionA)
                { 
                collisionA = 230;
                Wire.beginTransmission(SlaveA);
                Wire.write(collisionA);
                Wire.endTransmission();
                delay(1);
                
                collisionC = 230;
                Wire.beginTransmission(SlaveC);
                Wire.write(collisionC);
                Wire.endTransmission();
                delay(1);
                oldPositionA = PositionA;
                }
              }
              if(PositionA == PositionD)
              { 
                if(oldPositionA != PositionA)
                { 
                collisionA = 229; 
                Wire.beginTransmission(SlaveA);
                Wire.write(collisionA);
                Wire.endTransmission();
                delay(1);
                
                collisionD = 229; 
                Wire.beginTransmission(SlaveD);
                Wire.write(collisionD);
                Wire.endTransmission();
                delay(1);
                oldPositionA = PositionA;
                }
              }
              
              if(PositionB == PositionC)
              {
                if(oldPositionB != PositionB)
                { 
                collisionB = 228; 
                Wire.beginTransmission(SlaveB);
                Wire.write(collisionB);
                Wire.endTransmission();
                delay(1);
                
                collisionC = 228; 
                Wire.beginTransmission(SlaveC);
                Wire.write(collisionC);
                Wire.endTransmission();
                delay(1);
                oldPositionB = PositionB;
                }

              }
              if(PositionB == PositionD)
              {
                if(oldPositionB != PositionB)
                { 
                collisionB = 227; 
                Wire.beginTransmission(SlaveB);
                Wire.write(collisionB);
                Wire.endTransmission();
                delay(1);
                
                collisionD = 227;
                Wire.beginTransmission(SlaveD);
                Wire.write(collisionD);
                Wire.endTransmission();
                delay(1);
                oldPositionB = PositionB;
                }
              }
              if(PositionC == PositionD)
              { 
                if(oldPositionC != PositionC)
                { 
                collisionC = 226;
                Wire.beginTransmission(SlaveC);
                Wire.write(collisionC);
                Wire.endTransmission();
                delay(1);
                
                collisionD = 226;              
                Wire.beginTransmission(SlaveD);
                Wire.write(collisionD);
                Wire.endTransmission();
                delay(1);              
               }
               oldPositionC = PositionC;
               }
          
              
    
    
}


void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}

void pullSlaves()
{

  Wire.requestFrom(12, 2);    // request 6 bytes from slave device #8
  while (Wire.available()) { // slave may send less than requested
    PositionA = Wire.read(); // receive a byte as int
    ColourA = Wire.read(); // receive a byte as int
  }
  Wire.requestFrom(18, 2);    // request 6 bytes from slave device #8
  while (Wire.available()) { // slave may send less than requested
    PositionB = Wire.read(); // receive a byte as int
    ColourB = Wire.read(); // receive a byte as int
  }
  Wire.requestFrom(15, 2);    // request 6 bytes from slave device #8
  while (Wire.available()) { // slave may send less than requested
    PositionC = Wire.read(); // receive a byte as int
    ColourC = Wire.read(); // receive a byte as int
  }
  Wire.requestFrom(17, 2);    // request 6 bytes from slave device #8
  while (Wire.available()) { // slave may send less than requested
    PositionD = Wire.read(); // receive a byte as int
    ColourD = Wire.read(); // receive a byte as int
  }
}

