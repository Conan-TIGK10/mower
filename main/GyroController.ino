


#include "MeOrin.h"
#include <Wire.h>

MeGyro gyro;

//these are the variables the different values will be stored in
uint16 gyroX;
uint16 gyroY;
uint16 gyroZ; 

//run this in the loop
void runGyro(){
  
  gyro.update();

  gyroX = gyro.getAngleX();
  gyroY = gyro.getAngleY();
  gyroZ = gyro.getAngleZ();
   
}

//gyro setup
void gyroSetup(){
  Serial.begin(115200);
  gyro.begin();

}
