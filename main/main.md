# Main

## `setup(void) : void`

**Description** : Default project setup, should never be target called. Contains project setup and eventual additional functions from tabs.
### Use:
```c++
none
```
## `loop(void) : void`

**Description** : Default project loop, should never be target called. Contains main loop and calls to state machine or additional functions from tabs.
### Use:
```c++
none
```

## `pulseTickSeconds(void) : void`

**Description** : increments timer ticks every seconds.
### Use:
```c++
timer.every(tickrateSeconds, pulseTickSeconds);
```

## `pulseTickBluetooth(void) : void`

**Description** : Sends bluetooth data each 20ms..
### Use:
```c++
timer.every(tickrate20ms, pulseTickBluetooth);
```

## `pulseTickUltrasonic(void) : void`

**Description** : Updates the ultrasonic distance every 50ms
### Use:
```c++
t.every(ultrasonicTick, pulseTickUltrasonic);
```

## `state_machine(int16_t any) : void`

**Description** : Default project state machine, expects sensor data as int16_t. Handles directional states dependant on sensor state data. Also handles directional control from application through bluetooth.
### Use:
```c++
int16_t sensors = LT_IsInside();
state_machine(sensors);
```

## `parseData(char * any) : void`

**Description** : Default project parse data. Gets a char array of the message and parses it into 3 different integers that we can read for robot instruction.
### Use:
```c++
int mode = 0;
int xJoystick = 0;
int yJoystick = 0;
```


## `getState(void) : States`

**Description** : Returns the current state of the state machine
### Use:
```c++
States state;
```


