# Motor Controller

## `MotorLoop(void) : void`
**Description** : executes encoders loop and reads the motor rotation for increasing motor counter.
### Use:
```c++
MotorLoop();
```

## `Forward(void) : void`

**Description** : Moves motor forward with PWM.
### Use:
```c++
Forward();
```
## `Backward(void) : void`
**Description** : Moves motor backward with PWM.
### Use:
```c++
Backward();
```
## `BackwardAndTurnLeft(void) : void`
**Description** : Moves motor backward and left with PWM.
### Use:
```c++
BackwardAndTurnLeft();
```
## `BackwardAndTurnRight(void) : void`
**Description** : Moves motor backward and right with PWM.
### Use:
```c++
BackwardAndTurnRight();
```
## `TurnLeft(void) : void`
**Description** : Moves motor left with PWM.
### Use:
```c++
TurnLeft();
```
## `TurnRight(void) : void`
**Description** : Moves motor right with PWM.
### Use:
```c++
TurnRight();
```
## `Stop(void) : void`
**Description** : Stops motor.
### Use:
```c++
Stop();
```
## `StopBackwardAndTurnRight(void) : void`
**Description** : Stops motor, reverses while turning right with PWM.
### Use:
```c++
StopBackwardAndTurnRight();
```
## `StopBackwardAndTurnLeft(void) : void`
**Description** : Stops motor, reverses while turning left with PWM.
### Use:
```c++
StopBackwardAndTurnLeft();
```
## `SetMoveSpeed(int16_t any) : void`
**Description** : Asigns new speed to the motor pwm variable.
### Use:
```c++
SetMoveSpeed(int16_t any);
```
## `ChangeDirectionRandom(void) : void`
**Description** : Changes motor direction at random, eventual delays should be called outside function.
### Use:
```c++
ChangeDirectionRandom();
```
## `ChangeSpeedRandom(void) : void`
**Description** : Changes motor pwm speed at random, eventual delays should be called outside function.
### Use:
```c++
ChangeSpeedRandom();
```

## `SetupTTC(void) : void`
**Description** : Sets up the PWM freq to 8KHz.
### Use:
```c++
SetupTTC();
```

## `GetDistance(void) : float`
**Description** : Utilizes the motor counter to calculate distance in cm.
### Use:
```c++
float distanceForward = GetDistance();
```

## `GetNegativeDistance(void) : float`
**Description** : Utilizes the motor counter to calculate distance in cm, sets value to negative. Useful when robot is reversing.
### Use:
```c++
float distanceBackwards = GetNegativeDistance();
```

## `ResetDistance(void) : void`
**Description** :Resets the motor counter.
### Use:
```c++
ResetDistance();
```
