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
void btSendPosData(int protocol, double outData) {
    //Serial.write("Sending ");
    //Serial.println(outData);
    Serial.print("Sending ");
    Serial.print(outData);
    delay(20); // Might work without delay, need to ensure that its not called constantly
}

//sending multiple data, needs size of array/pointer.
/* void btSendMultiplePosData(int protocol, double* outData, int size) {
    bluetooth.write(protocol);
    bluetooth.write(",");
    for (int i = 0; i < size; i++){
      bluetooth.write(outData[i]);
      bluetooth.write(",");
    }
    delay(20); // Might work without delay, need to ensure that its not called constantly
}
*/
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
 /*
 *(data) = '/';
 *(data+1) = '1';
 *(data+2) = ',';
 *(data+3) = '1';
 *(data+4) = ',';
 *(data+5) = '2';
 *(data+6) = '&';
 */

  while(Serial.available() > 0){
      data[count] = Serial.read();
      count++;
  }
  
  return data;
}
