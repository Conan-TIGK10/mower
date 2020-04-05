


MeGyro gyro(1,0x69);

//these are the variables the different values will be stored in
double gyroX;
double gyroY;
double gyroZ; 

//gyro setup 
void gyroSetup(){
  Serial.begin(9600);
  gyro.begin();
}

//run this in the loop
void runGyro(){
  
  gyro.update();

  gyroX = gyro.getAngleX();
  gyroY = gyro.getAngleY();
  gyroZ = gyro.getAngleZ();
   
}
