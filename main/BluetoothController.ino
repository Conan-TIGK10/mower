//#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <MeBluetooth.h>

/*
Blue module can only be connected to port 3, 4, 5, 6 of base shield.

I/GATT: 00001801-0000-1000-8000-00805f9b34fb
I/GATT: 00001800-0000-1000-8000-00805f9b34fb
I/GATT: 0000ffe1-0000-1000-8000-00805f9b34fb
I/GATT: 0000ffe4-0000-1000-8000-00805f9b34fb
    9e5d1e47-5c13-43a0-8635-82ad38a1386f
*/
MeBluetooth bluetooth(PORT_5);
unsigned char table[128] = {0};
void bluetoothSetup()
{
    bluetooth.begin(115200);
    Serial.println("Bluetooth Start!");
}

void btEnd() {
 bluetooth.end(); 
}

// needs to be called mutiple times for sending multiple data values
void btSendPosData(int gyro, int motor, int ultra, int lightH, unsigned long milli) {

    Serial.print("/");
    Serial.print(gyro);
    Serial.print(",");
    Serial.print(motor);
    Serial.print(",");
    Serial.print(ultra);
    Serial.print(",");
    Serial.print(lightH);
    Serial.print(",");
    Serial.print(milli);
    Serial.print("&");
}

//Use incase btSendMultiplePosData() does not work as intended
void btSendPosData(int protocol, double x, double y) {
      //println incase application expects \n, might need adjustments.
      bluetooth.println(protocol);
      bluetooth.println(x);
      bluetooth.println(y);
      delay(20); // Might work without delay, need to ensure that its not called constantly
}
  
// Returns unsigne char table of bt data
char * btReadData() {
 char *data = (char*) malloc(32);
 int readdata = 0,i = 0,count = 0;

  while(Serial.available() > 0){
      data[count] = Serial.read();
      count++;
  }
  
  return data;
}

void parseData(char * data){
  int count = 0;
  int isX = 0; //if 0 then its the x value, if 1 then its y
  while(data[count] != '&' || (data[0] == '/' && count < 32)){
    if(count == 1){
        mode = data[1] - '0';
        if(mode == 1) {
          state = JOYSTICK;
        } else {
          state = STOP;
        }

      }else if(data[count] == ',' && isX == 0){
        int internalCount = 1;
        isX = 1;
        int isMinus = 0;
        if(data[count+1] == '-'){
          isMinus = 1;
          count++;
          }
        while(data[count+internalCount] != ','){
          internalCount++;
        }
        if(internalCount == 2){ //X är en siffra
          xJoystick = (data[count+1] - '0');
          if(isMinus){
            yJoystick *= -1;
            }
        }
        if(internalCount == 3){ //X är två siffor
          xJoystick = ((data[count+1] - '0')*10) + (data[count+2] - '0');
          if(isMinus){
            yJoystick *= -1;
            }
        }
        if(internalCount == 4){ //X är tre siffror
          xJoystick = ((data[count+1] - '0')*100) + ((data[count+2] - '0')*10) + (data[count+3] - '0');
          if(isMinus){
            yJoystick *= -1;
            }
        }
        count ++;
      }else if(data[count] == ','){
        int internalCount = 1;
        int isMinus = 0;
        if(data[count+1] == '-'){
          isMinus = 1;
          count++;
          }
        while(data[count+internalCount] != '&' && internalCount < 6){
          internalCount++;
        }
        if(internalCount == 2){ //Y är en siffra
          yJoystick = (data[count+1] - '0');
          if(isMinus){
            yJoystick *= -1;
            }
        }
        if(internalCount == 3){ //Y är två siffor
          yJoystick = ((data[count+1] - '0')*10) + (data[count+2] - '0');
          if(isMinus){
            yJoystick *= -1;
            }
        }
        if(internalCount == 4){ //Y är tre siffror
          yJoystick = ((data[count+1] - '0')*100) + ((data[count+2] - '0')*10) + (data[count+3] - '0');
          if(isMinus){
            yJoystick *= -1;
            }
        }
        count ++;
      }
    count++;
    }
    free(data);
}
