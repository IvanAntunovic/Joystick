#include "LeftJoystickState.h"

JoystickState * LeftJoystickState::getInstance()
{
	if (LeftJoystickState::sInstance == NULL)
	{
		LeftJoystickState::sInstance = new LeftJoystickState();
	}
	return LeftJoystickState::sInstance;
}

void LeftJoystickState::handleCoordinates(int nX, int nY, Joystick & joystick)
{
	int8_t retVal = joystick.getZone(nX, nY);
	if (retVal == IN_DEADZONE)
	{
		joystick.changeState(IdleJoystickState::getInstance());
		if (joystick.isPasswordSet())
		{
			joystick.position_states[3] = IdleJoystickState::getInstance();
		}
		cout << "Joystick moved to Idle Position!" << endl;
	}
	else if (retVal == NOT_IN_DEADZONE)
	{
		cout << "Joystick is not in Deadzone!" << endl;
	}
	else if (retVal == INVALID_PARAMETER)
	{
		cout << "Invalid parameters!" << endl;
	}
}
JoystickState* LeftJoystickState::sInstance = NULL;