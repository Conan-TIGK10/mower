#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <MeBluetooth.h>

/*
Blue module can only be connected to port 3, 4, 5, 6 of base shield.
*/
MeBluetooth bluetooth(PORT_3);
unsigned char table[128] = {0};
void setup()
{
    Serial.begin(9600);
    bluetooth.begin(9600);
    Serial.println("Bluetooth Start!");
}

void btEnd() {
 bluetooth.end(); 
}

// needs to be called mutiple times for sending multiple data values
void btSendPosData(int protocol, double outData) {
  if(bluetooth.available()) {
    bluetooth.write(protocol);
    bluetooth.write(",");
    bluetooth.write(outData);
    bluetooth.write(",");
    delay(20); // Might work without delay, need to ensure that its not called constantly
  }
}

//sending multiple data, needs size of array/pointer.
void btSendMultiplePosData(int protocol, double* outData, int size) {
  if(bluetooth.available()) {
    bluetooth.write(protocol);
    bluetooth.write(",");
    for (int i = 0; i < size; i++){
      bluetooth.write(outData[i]);
      bluetooth.write(",");
    }
    delay(20); // Might work without delay, need to ensure that its not called constantly
  }
}

// Returns unsigne char table of bt data
unsigned char btReadData() {
 int readdata = 0,i = 0,count = 0;
 if(bluetooth.available()) {
   while((readdata = bluetooth.read()) != (int)-1) {
      table[count] = readdata;
      count++;
      delay(1);
    }
    for(i = 0;i<count;i++) {
      Serial.write(table[i]);
    }
 } 
 return = table;
}


