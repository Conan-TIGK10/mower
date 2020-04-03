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
#include <SoftwareSerial.h>


int turnSpeed = 200;
int distance=0;
int randnum = 0;
boolean leftflag,rightflag;
int minSpeed = 48;
int factor = 23;

void setup()
{
  gyroSetup();
}

void loop()
{
  // ChangeDirectionRandom();
  runGyro();
}
