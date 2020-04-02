/*************************************************************************
Makeblock bluetooth car controller test code, shoulde be replaced with project code.

I included all makeblock library files, which should be available in our project repo.
Library files should be placed into Arduino installation folder -> installation folder\Arduino\libraries\Makeblock\
**************************************************************************/
#include <MeAuriga.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include "LineTrackerController.h"

typedef enum {STOP, FORWARD, BACKWARDS, RANDOM, ROTATE_RIGHT, ROTATE_LEFT} States;

States state = STOP;


void setup()
{
  Serial.begin(9600);
}

void loop()
{
  //LT_IsInside();
  //delay(500);
  // ChangeDirectionRandom();
  int temp = LT_IsInside();
  state_machine(temp);
}

void state_machine(int16_t sensors) 
{
  Serial.print(state);
  switch(state)
  {
    case STOP:
      if(sensors == NONE) {
        state = FORWARD;
      } else if (sensors == SENSOR_RIGHT) {
        //rotate left
        state = ROTATE_LEFT;
      } else {
        //rotate right
        state = ROTATE_RIGHT;
      }
      break;
      
    case FORWARD:
      if (sensors != NONE) {
        Forward();
      }
      break;
      
    case ROTATE_LEFT:
      if (sensors != SENSOR_RIGHT) {
        TurnLeft();
      } else {
        state = FORWARD;
      }
       
      break;

    case ROTATE_RIGHT:
      if (sensors == SENSOR_RIGHT ){
         TurnRight();
      } else {
        state = FORWARD;
      }
      break;
      
  } 
}
