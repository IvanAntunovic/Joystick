#pragma once

#ifndef _LEFT_JOYSTICK_STATE_H_
#define _LEFT_JOYSTICK_STATE_H_

#include "JoystickState.h"
#include "Joystick.h"
#include "IdleJoystickState.h"

class LeftJoystickState : public JoystickState
{
private:
	static JoystickState* sInstance;
public:
	static JoystickState* getInstance();
	void handleCoordinates(int nX, int nY, Joystick& joystick);
};

#endif