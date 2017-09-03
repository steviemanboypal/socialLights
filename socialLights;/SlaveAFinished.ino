#define NUM_LEDS 79
int SpeedDelay = 180;
int pos = random(75);//position
int colour = 225;
int MY_ADDRESS = 12;
volatile int E1 = 0;
int collisionB = 0;
int collisionC = 0;
int collisionD = 0;
int collisionNotification = 0;  //gets set to 1 when we receive collission notification from master. gets reset to 0 after checking what kind of collission it was.
int direction_ = 1; //set direction of movement

long timeCounter = 0;
long mySpeedInterval = 60000;  //value range = 12000 is fast, 160000 is every second
volatile int ReceivedData;
#include <Wire.h>

void setup() 
{
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
            if(E1 == 231) //GREEN + RED = 231
            { E1 = 0;
              collisionB = collisionB+1;
              if(collisionB == 5)
              {
               direction_ = !direction_;
               mySpeedInterval = 25000;
               collisionB = 0;
              }
              else
              {
               mySpeedInterval = 35000;
               madCollission();
              }
              //call collision function here
            }
            
            if(E1 == 230) //GREEN + BLUE = 230
            { 
              E1 = 0;
              collisionC = collisionC+1;
              if(collisionC == 3)
              {
                mySpeedInterval = 30000;
                collisionC = 0;
              }
              madCollission();
            }
            
            if(E1 == 229) //GREEN + YELLOW = 229
            { 
              E1 = 0;
              collisionD = collisionD+1;
              if(collisionD == 6)
              {
                mySpeedInterval = 70000;
                collisionD = 0;
              }
              madCollission();
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
    E1 = ReceivedData;
    //Serial.println(E1);
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
    for(int g=0; g <10; g++)
    {

    delay(25);

    delay(25);
    }
    
}
