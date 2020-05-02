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

typedef enum {STOP, FORWARD, BACKWARDS, RANDOM, ROTATE_RIGHT, ROTATE_LEFT, JOYSTICK} States;

States state = STOP;
#include <SoftwareSerial.h>

//timer library https://github.com/JChristensen/Timer
Timer t;
Timer milliTimer;
uint16_t tickMillis = 0;
uint16_t tickRateMillis = 1;
uint16_t tick = 0;
uint16_t tickRateSeconds = 1000;
uint8_t firstInterval = 1;
uint8_t secondInterval = 3;

int mode = 0;
int xJoystick = 0;
int yJoystick = 0;

void setup()
{
  Serial.begin(115200);
  bluetoothSetup();
  gyroSetup();
  t.every(tickRateSeconds, pulseTickSeconds);
  milliTimer.every(tickrateMillis, pulseTickMillis)
  SetupTTC();

}
void loop()
{
  int temp = LT_IsInside();
  state_machine(temp);
  runGyro();
  MotorLoop();
  t.update();
  
  //printCounter();
  //btSendPosData(123, 20000, 55, 0, 0);
  if (Serial.available() > 0){
    //parseData(btReadData());
  }
    Serial.println("distance: ");
    Serial.print(GetDistance());
  delay(50);
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

void state_machine(int16_t sensors) 
{
  /*
  Serial.print("state: ");
  Serial.println(state);
  Serial.println(sensors);
  Serial.print("ultrasonic: ");
  Serial.println(GetUltrasonicDistance());*/


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

      //Serial.print("Left Tick: ");
      //Serial.println(tick);

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


      //Serial.print("RIght Tick: ");
      //Serial.println(tick);

      if(tick <= firstInterval){
        Backward();
      }
      else if(tick > firstInterval && tick < secondInterval){
        TurnRight();
      } else{
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

void parseData(char * data){
  int count = 0;
  int isX = 0; //if 0 then its the x value, if 1 then its y
  while(data[count] != '&' || (data[0] == '/' && count < 32)){
    if(count == 1){
        mode = data[1] - '0';
        if(mode == 1) {
          state = JOYSTICK;
        } else {
          state = STOP;
        }

      }else if(data[count] == ',' && isX == 0){
        int internalCount = 1;
        isX = 1;
        int isMinus = 0;
        if(data[count+1] == '-'){
          isMinus = 1;
          count++;
          }
        while(data[count+internalCount] != ','){
          internalCount++;
        }
        if(internalCount == 2){ //X är en siffra
          xJoystick = (data[count+1] - '0');
          if(isMinus){
            yJoystick *= -1;
            }
        }
        if(internalCount == 3){ //X är två siffor
          xJoystick = ((data[count+1] - '0')*10) + (data[count+2] - '0');
          if(isMinus){
            yJoystick *= -1;
            }
        }
        if(internalCount == 4){ //X är tre siffror
          xJoystick = ((data[count+1] - '0')*100) + ((data[count+2] - '0')*10) + (data[count+3] - '0');
          if(isMinus){
            yJoystick *= -1;
            }
        }
        count ++;
      }else if(data[count] == ','){
        int internalCount = 1;
        int isMinus = 0;
        if(data[count+1] == '-'){
          isMinus = 1;
          count++;
          }
        while(data[count+internalCount] != '&'){
          internalCount++;
        }
        if(internalCount == 2){ //Y är en siffra
          yJoystick = (data[count+1] - '0');
          if(isMinus){
            yJoystick *= -1;
            }
        }
        if(internalCount == 3){ //Y är två siffor
          yJoystick = ((data[count+1] - '0')*10) + (data[count+2] - '0');
          if(isMinus){
            yJoystick *= -1;
            }
        }
        if(internalCount == 4){ //Y är tre siffror
          yJoystick = ((data[count+1] - '0')*100) + ((data[count+2] - '0')*10) + (data[count+3] - '0');
          if(isMinus){
            yJoystick *= -1;
            }
        }
        count ++;
      }
    count++;
    }
    free(data);
  }
      
