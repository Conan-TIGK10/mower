/*************************************************************************
Makeblock bluetooth car controller test code, shoulde be replaced with project code.

I included all makeblock library files, which should be available in our project repo.
Library files should be placed into Arduino installation folder -> installation folder\Arduino\libraries\Makeblock\
**************************************************************************/
#include <Arduino.h>
#include <avr/wdt.h>
#include <MeAuriga.h>
#include "MeEEPROM.h"
#include <Wire.h>
#include "LineTrackerController.h"
#include "Timer.h"

typedef enum {STOP, FORWARD, BACKWARDS, RANDOM, ROTATE_RIGHT, ROTATE_LEFT} States;

States state = STOP;
#include <SoftwareSerial.h>

//timer library https://github.com/JChristensen/Timer
Timer t;
uint16_t tick = 0;
uint16_t tickRate = 1000;
uint8_t firstInterval = 3;
uint8_t secondInterval = 6;

void setup()
{
  Serial.begin(9600);
  //bluetoothSetup();
  gyroSetup();
  t.every(tickRate, pulseTick);

}

void loop()
{
  //LT_IsInside();
  //delay(500);
  // ChangeDirectionRandom();
  int temp = LT_IsInside();
  state_machine(temp);
  runGyro();
  t.update();
  //btSendPosData(0, 0);
  delay(50);
}

void pulseTick(void){
    tick++;
  
  }

void state_machine(int16_t sensors) 
{
  Serial.print("state: ");
  Serial.println(state);
  Serial.println(sensors);
  Serial.print("ultrasonic: ");
  Serial.println(GetUltrasonicDistance());


  if(GetUltrasonicDistance() < 5 && state != ROTATE_RIGHT){
    state = ROTATE_RIGHT;
    tick = 0;
  }
  switch(state)
  {
    case STOP:
      if (sensors == BOTH) {
        Stop();
        state = ROTATE_RIGHT;
        tick = 0;
      }
        else if(sensors == NONE) {
        state = FORWARD;
      } else if (sensors == SENSOR_RIGHT) {
        //rotate left
        state = ROTATE_LEFT;
      } else if (sensors == SENSOR_LEFT){
        //rotate right
        state = ROTATE_RIGHT;
        tick = 0;
      } else if (sensors == SENSOR_LEFT){
        //rotate right
        state = ROTATE_RIGHT;
        tick = 0;
      }
      break;
      
    case FORWARD:
      if (sensors != NONE) {
        state = STOP;
      } else {
        Forward();
      }
      break;
      
    case ROTATE_LEFT:

      Serial.print("Left Tick: ");
      Serial.println(tick);

      if(tick <= firstInterval){
        Backward();
      }
      else if(tick > firstInterval && tick < secondInterval){
        TurnLeft();
      }
      else{
        state = STOP;
      }
       
      break;

    case ROTATE_RIGHT:


      Serial.print("RIght Tick: ");
      Serial.println(tick);

      if(tick <= firstInterval){
        Backward();
      }
      else if(tick > firstInterval && tick < secondInterval){
        TurnRight();
      } else{
        state = STOP;
      }

      break;
      
  } 

}
