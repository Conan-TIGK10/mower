#include <MeAuriga.h>

MeEncoderOnBoard Encoder_1(SLOT1);
MeEncoderOnBoard Encoder_2(SLOT2);


int16_t moveSpeed = 120;
int16_t randomSpeed = 0;
int16_t randomDirection = 0;
float motorCounterL = 0;
float motorCounterR = 0;

void MotorLoop(){
  Encoder_1.loop();
  Encoder_2.loop();
}

void incrementCount() {
  if (digitalRead(Encoder_1.getPortA())){
    motorCounterL ++;
  }
  if (digitalRead(Encoder_2.getPortA())) {
    motorCounterR ++;
  }
}

void Forward(void)
{
  Encoder_1.setMotorPwm(-moveSpeed);
  Encoder_2.setMotorPwm(moveSpeed);
}
void Backward(void)
{
  Encoder_1.setMotorPwm(moveSpeed);
  Encoder_2.setMotorPwm(-moveSpeed);
}
  
void TurnLeft(void)
{
  ResetDistance();
  Encoder_1.setMotorPwm(-moveSpeed);
  Encoder_2.setMotorPwm(-moveSpeed);
}
void TurnRight(void)
{
  ResetDistance();
  Encoder_1.setMotorPwm(moveSpeed);
  Encoder_2.setMotorPwm(moveSpeed);
}

void Stop(void)
{
  Encoder_1.setMotorPwm(0);
  Encoder_2.setMotorPwm(0);
}


void SetMoveSpeed (int16_t newSpeed) {
  moveSpeed = newSpeed;
}

void SetupTTC() {
  // sets to 8KHz
 TCCR1A = _BV(WGM10);
 TCCR1B = _BV(CS11) | _BV(WGM12);
 TCCR2A = _BV(WGM21) | _BV(WGM20);
 TCCR2B = _BV(CS21); 
}

float GetDistance() {
  float distance = 0;
  if (motorCounterL >= motorCounterR){
     distance = motorCounterL / 6,5;
  } /*
  else {
    distance = motorCounterR / 6,5;
  } */
  distance = distance * 11,9;
  return distance;
}

float GetNegativeDistance() {
  float distance = 0;
  if (motorCounterL >= motorCounterR){
     distance = motorCounterL / 6,5;
  } /*
  else {
    distance = motorCounterR / 6,5;
  } */
  distance = distance * 11,9;
  distance *= -1;
  return distance;
}


void ResetDistance() {
  motorCounterL = 0;
  motorCounterR = 0;
}
