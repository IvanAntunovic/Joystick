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
		Serial.println( "Joystick moved to Idle Position! - Left");
	}
	else if (retVal == NOT_IN_DEADZONE)
	{
		Serial.println("Joystick is not in Deadzone!");
	}
	else if (retVal == INVALID_PARAMETER)
	{
		Serial.println("Invalid parameters!");
	}
}
JoystickState* LeftJoystickState::sInstance = NULL;