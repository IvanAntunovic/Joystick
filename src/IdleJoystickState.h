#pragma once
#ifndef _IDLE_JOYSTICK_STATE_H_
#define _IDLE_JOYSTICK_STATE_H_

#include "Joystick.h"
#include "JoystickState.h"
#include "DownJoystickState.h"
#include "RightJoystickState.h"
#include "LeftJoystickState.h"
#include "RightJoystickState.h"
#include "UpJoystickState.h"

#ifndef POSITIONS_LENGTH
#define POSITIONS_LENGTH	3
#endif // !POSITIONS_LENGTH

#ifndef MAX_X_POSITION
#define MAX_X_POSITION		1000
#endif // !1

#ifndef MIN_X_POSITION
#define MIN_X_POSITION		20
#endif // !

#ifndef MAX_Y_POSITION
#define MAX_Y_POSITION		1000
#endif // MAX_Y_POSITION

#ifndef MIN_Y_POSITION
#define MIN_Y_POSITION		20
#endif // !1

#ifndef MODE_KORISTI
#define MODE_KORISTI        0
#endif // !1

#ifndef MODE_POSTAVI
#define MODE_POSTAVI		1
#endif // !MODE_POSTAVI

#define NOK -1

class IdleJoystickState : public JoystickState
{
private:
	static JoystickState* sInstance;
	int8_t getBufferFreeIndex(Joystick& joystick);

public:
	static JoystickState* getInstance();

	void handleCoordinates(int nX, int nY, Joystick& joystick);
};
#endif