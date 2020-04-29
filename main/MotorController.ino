#include <MeAuriga.h>

MeEncoderOnBoard Encoder_1(SLOT1);
MeEncoderOnBoard Encoder_2(SLOT2);


int16_t moveSpeed = 120;
int16_t randomSpeed = 0;
int16_t randomDirection = 0;

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
  Encoder_1.setMotorPwm(-moveSpeed);
  Encoder_2.setMotorPwm(-moveSpeed);
}
void TurnRight(void)
{
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

void ChangeDirectionRandom(void) {
  // Might be better to just change direction when hitting the boundery area, and exclude going forward again.
  randomSeed(millis());
  randomDirection = random(255);

  if (randomDirection <= 65 ){
    TurnRight();
  }
  else if (randomDirection <= 128){
    TurnLeft();
  }
  else if (randomDirection <= 193){
    Forward();
  }
  else if (randomDirection <= 255) {
    Backward(); // Maybe not randomly reverse?
  }
}

void ChangeSpeedRandom(void) {
  randomSeed(millis());
  randomSpeed = random(255);
  if (randomSpeed < 200){
  moveSpeed = 200;
  } else {
    moveSpeed = randomSpeed;
  }
}

void SetupTTC() {
  // sets to 8KHz
 TCCR1A = _BV(WGM10);
 TCCR1B = _BV(CS11) | _BV(WGM12);
 TCCR2A = _BV(WGM21) | _BV(WGM20);
 TCCR2B = _BV(CS21); 
}

// Pulse per revolution seems to be 9, but not certain as of yet. I sugest measuring the distance traveled and deviding by circumference and deviding pulse count with the result. Pulse Count / (Distance / Circumference)
long GetEncoderPulseCounterL() {
  return Encoder_1.getPulsePos();
}

long GetEncoderPulseCounterR() {
  return Encoder_2.getPulsePos();
}

// Used to reset distance counter, could perhaps be called when changing direction to keep track of how long the robot has moven in a given direction.
void setEncoderPulseCounterL (int16_t pulse) {
    Encoder_1.setPulsePos(pulse);
}

void setEncoderPulseCounterR (int16_t pulse) {
    Encoder_2.setPulsePos(pulse);
}
