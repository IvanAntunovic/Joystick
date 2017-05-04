#pragma once
#include "JoystickState.h"
#include "Joystick.h"
#include <iostream>

class RightJoystickState : public JoystickState
{
private:
	static JoystickState* sInstance;
public:
	static JoystickState* getInstance();

	void handleCoordinates(int nX, int nY, Joystick& joystick);
};
