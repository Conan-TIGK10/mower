


MeGyro gyro(1,0x69);

//these are the variables the different values will be stored in
double gyroX;
double gyroY;
double gyroZ;

double gyroChangeX;
double gyroChangeY;



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

  gyroChangeX = gyro.getGyroX();
  gyroChangeY = gyro.getGyroY();

/*
  Serial.print("X: ");
  Serial.println(gyroX);
  Serial.print("Y: ");
  Serial.println(gyroY);
  Serial.print("Z: ");
  Serial.println(gyroZ);

  Serial.print("ChangeX: ");
  Serial.println(gyroChangeX);
  Serial.print("ChangeY: ");
  Serial.println(gyroChangeY);
  delay(500);*/

}
double getAngleZ(void){
  return gyro.getAngleZ();
  
  }
double getGyroChangeX(void){
  return gyroChangeX;
  }
double getGyroChangeY(void){
  return gyroChangeY;
  }
