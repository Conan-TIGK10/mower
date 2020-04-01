#include "Makeblock.h"
#include <SoftwareSerial.h>
#include <Wire.h>

MeDCMotor MotorL(M1);  
MeDCMotor MotorR(M2);
int _randomDirection;
int _randomSpeed;
int _moveSpeed = 0;
int _turnSpeed = 0;
int _minSpeed = 0;

void loop() {
 
  //bluetooth get data (BluetoothController.btGetData())
    
    //MotorL.run(s1);
    //MotorR.run(s2);
}

void Forward() {
  MotorL.run(_moveSpeed);
  MotorR.run(_moveSpeed);
}

void Reverse() {
  MotorL.run(-_moveSpeed);
  MotorR.run(-_moveSpeed);
}

void TurnLeft() {
 MotorL.run(-_moveSpeed);
 MotorR.run(_moveSpeed);
}

void TurnRight() {
 MotorL.run(_moveSpeed);
 MotorR.run(-_moveSpeed);
}

void ChangeDirectionRandom() {
  // Might be better to just change direction when hitting the boundery area, and exclude going forward again.
  randomSeed(millis());
  _randomDirection = random(255);
  
  if (_randomDirection <= 65 )
    TurnRight();
  else if (_randomDirection <= 128)
    TurnLeft();
  else if (_randomDirection <= 193)
    Forward();
  else if (_randomDirection <= 255)
    Reverse(); // Maybe not randomly reverse?
}

void ChangeSpeedRandom() {
  randomSeed(millis());
  _randomSpeed = random(255);
  if (_randomSpeed < 200){
  _moveSpeed = 200;
  } else {
    _moveSpeed = _randomSpeed;
  }
}
