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

typedef enum {STOP, FORWARD, ROTATE_RIGHT, ROTATE_LEFT, JOYSTICK} States;

States state = STOP;
#include <SoftwareSerial.h>

//timer library https://github.com/JChristensen/Timer
Timer t;
uint16_t tickMillis = 0;
uint16_t tickRateMillis = 10;
uint16_t bluetoothTick = 0;
uint16_t bluetoothTickRate = 20;
uint16_t tick = 0;
uint16_t tickRateSeconds = 1000;
uint8_t firstInterval = 1;
uint8_t secondInterval = 3;
bool backwardsFlag = 0;

int mode = 0;
int xJoystick = 0;
int yJoystick = 0;

double ultrasonicDistance = 20;
int ultrasonicTick = 50;

void setup()
{
  Serial.begin(115200);
  bluetoothSetup();
  gyroSetup();
  t.every(tickRateSeconds, pulseTickSeconds);
  t.every(tickRateMillis, pulseTickMillis);
  t.every(bluetoothTickRate, pulseTickBluetooth);
  t.every(ultrasonicTick, pulseTickUltrasonic);
  SetupTTC();

}
void loop()
{
  int temp = LT_IsInside();
  state_machine(temp);
  runGyro();
  MotorLoop();
  if (state == FORWARD || backwardsFlag) 
    incrementCount();
  t.update();
  if (Serial.available() > 0){
    parseData(btReadData());
  }
}

void pulseTickSeconds(void){
    tick++;
  
  }
void pulseTickMillis(void) {
  if (tickMillis >= 65535) {
    tickMillis = 0;
  } else {
    tickMillis++;
  }
}

void pulseTickBluetooth(void) {
    unsigned long timeMilli = millis();
    if ((state == ROTATE_LEFT || state == ROTATE_RIGHT) &&  tick <= firstInterval) {
      btSendPosData(GetGyro(), 0, GetUltrasonicDistance(), LT_IsInside(), timeMilli);
    }
    else if (state == ROTATE_LEFT || state == ROTATE_RIGHT) {
      btSendPosData(GetGyro(), 1, GetUltrasonicDistance(), LT_IsInside(), timeMilli); 
    }
    else {
      btSendPosData(GetGyro(), 2, GetUltrasonicDistance(), LT_IsInside(), timeMilli);
    }
}

void pulseTickUltrasonic(void){
  ultrasonicDistance = GetUltrasonicDistance();
  
  }


void state_machine(int16_t sensors) 
{
  if(ultrasonicDistance < 5 && state != ROTATE_RIGHT){
    state = ROTATE_RIGHT;
    tick = 0;
  }
  switch(state)
  {
    case STOP:
      if (sensors == BOTH) {
        Stop();
        ResetDistance();
        state = ROTATE_RIGHT;
        tick = 0;
      }
        else if(sensors == NONE) {
        ResetDistance();
        state = FORWARD;
      } else if (sensors == SENSOR_RIGHT) {
        //rotate left
        ResetDistance();
        state = ROTATE_LEFT;
      } else if (sensors == SENSOR_LEFT){
        //rotate right
        ResetDistance();
        state = ROTATE_RIGHT;
        tick = 0;
      } else if (sensors == SENSOR_LEFT){
        //rotate right
        ResetDistance();
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


      if(tick <= firstInterval){
        backwardsFlag = 1;
        Backward();
      }
      else if(tick > firstInterval && tick < secondInterval){
        backwardsFlag = 0;
        TurnLeft();
      }
      else{
        backwardsFlag = 0;
        state = STOP;
      }
       
      break;

    case ROTATE_RIGHT:


      //Serial.print("RIght Tick: ");
      //Serial.println(tick);

      if(tick <= firstInterval){
        backwardsFlag = 1;
        Backward();
      }
      else if(tick > firstInterval && tick < secondInterval){
        backwardsFlag = 0;
        TurnRight();
      } else{
        backwardsFlag = 0;
        state = STOP;
      }

      break;

    case JOYSTICK:
      if(xJoystick == 0 && yJoystick == 0) {
        Stop();
      }
      else if(yJoystick == 1) {
        Forward();
      }
      else if(xJoystick == 2) {
        TurnRight();
      }
      else if(yJoystick == 2) {
        Backward();
      }
      else if(xJoystick == 1) {
        TurnLeft();
      }
      break;
      
  } 
}

States getState(void){
    return state;
  }
      
