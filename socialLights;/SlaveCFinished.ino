#define NUM_LEDS 79

//BLUE COLOUR
int SpeedDelay = 190;
int pos = random(70);
int colour = 225;
int MY_ADDRESS = 15;

volatile int C1 = 0;
int collisionA = 0;
int collisionB = 0;
int collisionD = 0;
int collisionNotification = 0;  //gets set to 1 when we receive collission notification from master. gets reset to 0 after checking what kind of collission it was.
int direction_ = 1; //set direction of movement

long timeCounter = 0;
long mySpeedInterval = 20000;  //value range = 12000 is fast, 160000 is every second
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
}

  if(collisionNotification == 1)
      {
            if(C1 == 230) //GREEN +BLUE = 230
            { C1 = 0;
              collisionA = collisionA+1;
              //Serial.println("CRASH A");
            
              if(collisionA == 7)
              {
                direction_ = !direction_;
                collisionA = 0;
              }
              else
              {
              
              madCollission();
              }
              //call collision function here
            }
            
            if(C1 == 228) //B+C = 228
            { C1 = 0;
              collisionB = collisionB+1;
              if(collisionB = 5)
              {
                mySpeedInterval = 4000;
                direction_ = !direction_;
                collisionB = 0;
              }
              else
              {
                mySpeedInterval = 20000;
              }
              madCollission();
            }
            
            if(C1 == 226) //C+D = 226
            {
              C1 = 0;
              collisionD = collisionD+1;
              //Serial.println("CRASH D");
              if(collisionD == 4);
              {
              mySpeedInterval = 40000;
              collisionD = 0;
              }
            }
              else
              {
                
              
              
              
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
 // Wire.write(1); // respond with message of 6 bytes
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
    C1 = ReceivedData;
    //Serial.println(C1);
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
        delay(40);
      }
      else if(colour==0)
      {
        colour = 225;
        g++;
        delay(40);
      }
    }
    
}
