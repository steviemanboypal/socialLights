#define NUM_LEDS 79

int pos = random(75);
int colour = 225;
int MY_ADDRESS = 17; // Yellow Colour
volatile int C1 = 0;
int collisionA = 0;
int collisionB = 0;
int collisionC = 0;
int collisionNotification = 0;  //gets set to 1 when we receive collission notification from master. gets reset to 0 after checking what kind of collission it was.
int direction_ = 1; //set direction of movement

long timeCounter = 0;
long mySpeedInterval = 30000;  //value range = 12000 is fast, 160000 is every second
volatile int ReceivedData;

#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Wire.begin(MY_ADDRESS);                // join i2c bu  Wire.onRequest(requestEvent); // register event
}

void loop() 
{
  

timeCounter ++; //a counter to measure time

if(timeCounter > mySpeedInterval)
{
  moveLed();
  timeCounter = 0;
  //Serial.println("b");
}

  if(collisionNotification == 1)
      {
            if(C1 == 229) //A+D
            { C1 = 0;
              collisionA = collisionA+1;
              //Serial.println("CRASH A");
              if(collisionB == 3)
                {
                direction_ = !direction_;
                collisionA = 0;
                }
              
              madCollission();
              //call collision function here
            }
            
            if(C1 == 227) //B+D
            { C1 = 0;
              collisionB = collisionB+1;
             // Serial.println("CRASH B");
                if(collisionB == 10)
                {
                  mySpeedInterval = 8000;
                  collisionB = 0;
                  madCollissionWithPause();
                }
              
            }
            
            if(C1 == 226) //C+D = 229
            { C1 = 0;
              collisionC = collisionC+1;
              //Serial.println("CRASH C");
              madCollission();
            }
            
            
      collisionNotification = 0;     
      }
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() 
{
  Wire.write(pos);
  Wire.write(colour);
}

void receiveEvent(int numBytes)
{
  while(Wire.available())
  {
    ReceivedData = Wire.read();
    collisionNotification = 1;
    C1 = ReceivedData;
  }
}


void moveLed()
{
  if(direction_ == 1)  //if direction is forward
  { 
    if(pos <=NUM_LEDS)  //check Im not off hte end
    {
    pos++;
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
    }
    else
   {
    direction_ = 1;
   } 
   
   }
}


void madCollission()
{
    for(int g=0; g <10;)
    {
      if(colour==225)
      {
        colour = 0;
        g++;
        delay(45);
      }
      else if(colour==0)
      {
        colour = 225;
        g++;
        delay(45);
      }
    }
    
}

void madCollissionWithPause()
{
    for(int g=0; g <10; g++)
    {
      if(colour==225)
      {
        colour = 0;
        delay(405);
      }
      else if(colour==0)
      {
        colour = 225;
        delay(150);
      }
    }
    
}
