


#include "MeAuriga.h"
//#include <Wire.h>

MeGyro gyro;

//these are the variables the different values will be stored in
double gyroX;
double gyroY;
double gyroZ; 

//run this in the loop
void runGyro(){
  
  gyro.update();

  gyroX = gyro.getAngleX();
  gyroY = gyro.getAngleY();
  gyroZ = gyro.getAngleZ();

  Serial.print(gyroX);
  Serial.print(gyroY);
  Serial.print(gyroZ);
   
}

//gyro setup 
void gyroSetup(){
  Serial.begin(115200);
  gyro.begin();

}
