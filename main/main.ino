#include <Me4Button.h>
#include <Me7SegmentDisplay.h>
#include <MeAuriga.h>
#include <MeBaseBoard.h>
#include <MeBluetooth.h>
#include <MeBuzzer.h>
#include <MeColorSensor.h>
#include <MeCompass.h>
#include <MeConfig.h>
#include <MeDCMotor.h>
#include <MeEEPROM.h>
#include <MeEncoderMotor.h>
#include <MeEncoderNew.h>
#include <MeEncoderOnBoard.h>
#include <MeFlameSensor.h>
#include <MeGasSensor.h>
#include <MeGyro.h>
#include <MeHostParser.h>
#include <MeHumitureSensor.h>
#include <MeInfraredReceiver.h>
#include <MeIR.h>
#include <MeJoystick.h>
#include <MeLEDMatrix.h>
#include <MeLEDMatrixData.h>
#include <MeLightSensor.h>
#include <MeLimitSwitch.h>
#include <MeLineFollower.h>
#include <MeMbotDCMotor.h>
#include <MeMCore.h>
#include <MeMegaPi.h>
#include <MeMegaPiDCMotor.h>
#include <MeMegaPiPro.h>
#include <MeMegaPiPro4DcMotor.h>
#include <MeMegaPiProESCMotor.h>
#include <MeOnBoardTemp.h>
#include <MeOneWire.h>
#include <MeOrion.h>
#include <MePIRMotionSensor.h>
#include <MePm25Sensor.h>
#include <MePort.h>
#include <MePotentiometer.h>
#include <MePressureSensor.h>
#include <MePS2.h>
#include <MeRGBLed.h>
#include <MeSerial.h>
#include <MeShield.h>
#include <MeShutter.h>
#include <MeSmartServo.h>
#include <MeSoundSensor.h>
#include <MeStepper.h>
#include <MeStepperOnBoard.h>
#include <MeTemperature.h>
#include <MeTouchSensor.h>
#include <MeUltrasonicSensor.h>
#include <MeUSBHost.h>
#include <MeVoice.h>
#include <MeWifi.h>

/*  --Project Modules --
   -- Auto compiled --
   BluetoothController
*/

/*************************************************************************
Makeblock bluetooth car controller test code, shoulde be replaced with project code.

I included all makeblock library files, which should be available in our project repo.
Library files should be placed into Arduino installation folder -> installation folder\Arduino\libraries\Makeblock\
**************************************************************************/
#include "Makeblock.h"
#include <SoftwareSerial.h>
#include <Wire.h>

MeDCMotor MotorL(M1);  
MeDCMotor MotorR(M2);
MeBluetooth serial(PORT_4);
MeUltrasonicSensor UltrasonicSensor(PORT_3);
int moveSpeed = 190;
int turnSpeed = 200;
int distance=0;
int randnum = 0;
boolean leftflag,rightflag;
int minSpeed = 48;
int factor = 23;

void setup()
{
    leftflag=false;
    rightflag=false;
    serial.begin(115200);
    BluetoothController.setup()
}
int s1=0;
int s2=0;
int s3=0;

void loop()
{
  if(serial.paramAvailable()){
    s1 = serial.getParamValue("s1");
    s2 = serial.getParamValue("s2");
    if(serial.getParamValue("s3")>0){
      s3 = serial.getParamValue("s3");
    }
    MotorL.run(s1);
    MotorR.run(s2);
    return;
  }
   if(s3==2&&millis()%50 == 0)
   {
     Serial.println("ultrasonic");
      ultrCarProcess();
   }
}

void Forward()
{
  MotorL.run(moveSpeed);
  MotorR.run(moveSpeed);
}
void Backward()
{
  MotorL.run(-moveSpeed);
  MotorR.run(-moveSpeed);
}

void BackwardAndTurnLeft()
{
  MotorL.run(-moveSpeed/2);
  MotorR.run(-moveSpeed);
}
void BackwardAndTurnRight()
{
  MotorL.run(-moveSpeed);
  MotorR.run(-moveSpeed/2);
}
void TurnLeft()
{
  MotorL.run(-moveSpeed);
  MotorR.run(moveSpeed);
}
void TurnRight()
{
  MotorL.run(moveSpeed);
  MotorR.run(-moveSpeed);
}
void Stop()
{
  MotorL.run(0);
  MotorR.run(0);
}
void ChangeSpeed(int spd)
{
  moveSpeed = spd;
}

void ultrCarProcess()
{
  distance = UltrasonicSensor.distanceCm();
  randomSeed(analogRead(A4));
  if(distance>10&&distance<40)
  {
    randnum=random(300);
    if(randnum > 190 && !rightflag)
    {
      leftflag=true;
      TurnLeft();   
    }
    else
    {
      rightflag=true;
      TurnRight();  
    }
  }
  else if(distance<10)
  {
     randnum=random(300);
    if(randnum > 190)BackwardAndTurnLeft();
    else BackwardAndTurnRight();
  }
  else
  {
      leftflag=false;
      rightflag=false;
      Forward();
  }
}
