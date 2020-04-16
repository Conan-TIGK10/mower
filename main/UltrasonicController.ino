#include <MeAuriga.h>
#include <MeUltrasonicSensor.h>

MeUltrasonicSensor ultrasonic(PORT_10);

// returns value between 3-400cm, distance measured in cm
double GetUltrasonicDistance() {
  return ultrasonic.distanceCm();
  // delay for 50ms before calling again
  //delay(50); 
}

// MaxInch = 180
double GetUltraSonicDistanceInInches() {
  return ultrasonic.distanceInch();
}

// Returns the ultrasonic duration, usually used to convert to distance
long GetUltraSonicMeasure() {
  return ultrasonic.measure();
}
