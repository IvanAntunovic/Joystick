#pragma once
#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include "JoystickState.h"
#include "IdleJoystickState.h"


#define POSITIONS_LENGTH	4

#define MAX_X_POSITION		1000
#define MIN_X_POSITION		20
#define MAX_Y_POSITION		1000
#define MIN_Y_POSITION		20

#define MODE_KORISTI        0
#define MODE_POSTAVI		1

#define INVALID_PARAMETER   -1
#define IN_DEADZONE          0
#define NOT_IN_DEADZONE      1

class Joystick
{

private:
	uint8_t currentMode;
	JoystickState* currentState;
public:
	JoystickState* position_states[POSITIONS_LENGTH];

public:
	Joystick();

	void setMode(int newMode);
	int getMode();

	Joystick& operator=(const Joystick& other);
	friend bool operator==(const Joystick& joystickOne, const Joystick& joystickTwo);

	int8_t getStateBufferFreeIndex(void);

	void handlePositions(void);
	int8_t getZone(int nX, int nY);
	void changeState(JoystickState* newState);
	bool isPasswordSet(void);

	void printCurrentPositions(void);

};

#endif // !_JOYSTICK_H_
