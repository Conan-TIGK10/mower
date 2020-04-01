#include "Makeblock.h"
#include <SoftwareSerial.h>
#include <Wire.h>

MeDCMotor MotorL(M1);  
MeDCMotor MotorR(M2);
int moveSpeed = 0;
int turnSpeed = 0;
int minSpeed = 0;

void loop()
{
 
  //bluetooth get data (BluetoothController.btGetData())
    
    //MotorL.run(s1);
    //MotorR.run(s2);
}

void Forward()
{
  MotorL.run(moveSpeed);
  MotorR.run(moveSpeed);
}

