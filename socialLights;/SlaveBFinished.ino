#define NUM_LEDS 79
int pos = random(70);
int colour = 225;
int MY_ADDRESS = 18;
char x = 'B';// PURPLE COLOUR
volatile int F1 = 0;
int collisionA = 0;
int collisionC = 0;
int collisionD = 0;
int collisionNotification = 0;  //gets set to 1 when we receive collission notification from master. gets reset to 0 after checking what kind of collission it was.
int direction_ = 1; //set direction of movement

long timeCounter = 0;
long mySpeedInterval = 50000;  //value range = 12000 is fast, 160000 is every second
volatile int ReceivedData;

#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Wire.begin(MY_ADDRESS);                // join i2c bu  Wire.onRequest(requestEvent); // register event
}

void loop() {
timeCounter ++; //a counter to measure time

if(timeCounter > mySpeedInterval)
{
  moveLed();
  timeCounter = 0;
}

  if(collisionNotification == 1)
      {
            if(F1 == 231) //A+B = 231
            { F1 = 0;
              collisionA = collisionA+1;
              //Serial.println("CRASH A");
              //direction_ = !direction_;
              madCollision(); //call collision function here
              if(collisionA == 8)
              {
                mySpeedInterval = 35000;
              }
            }
            
            if(F1 == 228) //B+C = 228
            { F1 = 0;
              collisionC = collisionC+1;
              //Serial.println("CRASH C");
              mySpeedInterval = 11000;
              if(collisionC == 5)
              {
              madCollision();
              collisionC = 0;
            }
            }
            
            if(F1 == 227) //B+D = 229
            { F1 = 0;
              collisionD = collisionD+1;
              if(collisionC == 2)
              {
                direction_ = !direction_;
                collisionD = 0;
              }
                else
                {
                  madCollision();
                }
              //Serial.println("CRASH D");
            }
            
            
      collisionNotification = 0;     
      }
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write(pos);
  Wire.write(colour);
  //Wire.write(1); // respond with message of 6 bytes
  // as expected by master
}

void receiveEvent(int numBytes)
{
  while(Wire.available())
{
    ReceivedData = Wire.read();
    if(ReceivedData != 0)
    {
    collisionNotification = 1;
    F1 = ReceivedData;
    //Serial.println(F1);
    }
  }
}


void moveLed()
{
  if(direction_ == 1)  //if direction is forward
  { 
    if(pos <=NUM_LEDS)  //check Im not off hte end
    {
    pos++;
    /*Serial.print("Colour = ");
    Serial.print(c);
    Serial.print(" & ");
    Serial.print("Position = " );
    Serial.println(i);*/
//    Wire.beginTransmission(8);
//    Wire.write(code);
//    Wire.write(pos);
//    Wire.write(colour);
//    Wire.endTransmission();
    }
    else
    {
      direction_ = 0;  //change direction
    }
    
  }
 
  if (direction_ == 0)  //if direction is backwards
  {
    if(pos > 0)  //if Im not opff the left hand end
    {
    pos--; //move backwards
    /*Serial.print("Colour = ");
    Serial.print(c);
    Serial.print(" & ");
    Serial.print("Position = " );
    Serial.println(i);*/
//    Wire.beginTransmission(8);
//    Wire.write(code);
//    Wire.write(pos);
//    Wire.write(colour);
//    Wire.endTransmission();
    }
    else
   {
    direction_ = 1;
   } 
   
   }
}


void madCollision()
{
    for(int g=0; g <10;)
    {
    if (colour==225)
    {
      colour = 0;
      g++;
      delay(50);
    }
    if (colour==0)
    {
      colour = 225;
      g++;
      delay(50);
    }
    }
    
}
