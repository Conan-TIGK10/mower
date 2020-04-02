/*
 * Includes
 */
 
#include <SoftwareSerial.h>

#define NO_SENSOR_DETECTED = 0;
#define SENSOR_R_DETECTED = 1;
#define SENSOR_L_DETECTED = 2;
#define SENSOR_LR_DETECTED = 3;

MeLineFollower lineFinder(PORT_9);

void LineTrackerControllerSetup(){
  
}

int16_t LT_IsInside() {
  int sensorState = lineFinder.readSensors();
  Serial.println(sensorState);
 
  switch(sensorState)
  {
    case S1_IN_S2_IN:   return NO_SENSOR_DETECTED; break;
    case S1_IN_S2_OUT:  return SENSOR_R_DETECTED; break;
    case S1_OUT_S2_IN:  return SENSOR_L_DETECTED; break;
    case S1_OUT_S2_OUT: return SENSOR_LR_DETECTED; break;
    
    default: break;
  }
}
