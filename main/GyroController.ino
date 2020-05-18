


MeGyro gyro(1,0x69);

//these are the variables the different values will be stored in
double gyroX;
double gyroY;
double gyroZ;

double gyroChangeX;
double gyroChangeY;



//gyro setup 
void gyroSetup(){
  gyro.begin();
}

//run this in the loop
void runGyro(){
  
  gyro.update();
  gyroZ = gyro.getAngleZ();
}

double GetGyro() {
  if (gyroZ < 0) {
   return (360 + gyroZ);
  } else {
    return gyroZ;
  }
}
