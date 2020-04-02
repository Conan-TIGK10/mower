/*
 * Includes
 */
 
#include <SoftwareSerial.h>

#include "LineTrackerController.h"


MeLineFollower lineFinder(PORT_9);

void LineTrackerControllerSetup(){
  
}

int16_t LT_IsInside(void) {
  int sensorState = lineFinder.readSensors();
 
  switch(sensorState)
  {
    case S1_IN_S2_IN:   return BOTH; break;
    case S1_IN_S2_OUT:  return SENSOR_RIGHT; break;
    case S1_OUT_S2_IN:  return SENSOR_LEFT; break;
    case S1_OUT_S2_OUT: return NONE; break;
    
    default: break;
  }
}
