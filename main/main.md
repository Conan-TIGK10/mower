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
## `state_machine(int16_t any) : void`

**Description** : Default project state machine, expects sensor data as int16_t. Handles directional states dependant on sensor state data.
### Use:
```c++
int16_t sensors = LT_IsInside();
state_machine(sensors);
```
