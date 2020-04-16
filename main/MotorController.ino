#include <MeAuriga.h>

MeEncoderOnBoard Encoder_1(SLOT1);
MeEncoderOnBoard Encoder_2(SLOT2);


int16_t moveSpeed = 150;
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
  Encoder_2.setMotorPwm(moveSpeed/2);
}
void TurnRight(void)
{
  Encoder_1.setMotorPwm(-moveSpeed/2);
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
