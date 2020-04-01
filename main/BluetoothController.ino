#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

/*
Blue module can only be connected to port 3, 4, 5, 6 of base shield.
*/
MeBluetooth bluetooth(PORT_4);

void setup()
{
    Serial.begin(9600);
    bluetooth.begin(9600);
    Serial.println("Bluetooth Start!");
}

void btSendData(double[] outData) {
  if(bluetooth.available()) {
    bluetooth.write(outData);
  }
}

double btReadData() {
 if(bluetooth.available()) {
  return = bluetooth.read()
 } 
}
  


