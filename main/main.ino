/*************************************************************************
Makeblock bluetooth car controller test code, shoulde be replaced with project code.

I included all makeblock library files, which should be available in our project repo.
Library files should be placed into Arduino installation folder -> installation folder\Arduino\libraries\Makeblock\
**************************************************************************/
#include <MeAuriga.h>
#include <SoftwareSerial.h>
#include <Wire.h>

int turnSpeed = 200;
int distance=0;
int randnum = 0;
boolean leftflag,rightflag;
int minSpeed = 48;
int factor = 23;

void setup()
{
}

void loop()
{
  // ChangeDirectionRandom();

}
