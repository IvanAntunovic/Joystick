#include "UpJoystickState.h"

JoystickState * UpJoystickState::getInstance()
{
	if (UpJoystickState::sInstance == NULL)
	{
		UpJoystickState::sInstance = new UpJoystickState();
	}
	return UpJoystickState::sInstance;
}

void UpJoystickState::handleCoordinates(int nX, int nY, Joystick & joystick)
{
	int8_t retVal = joystick.getZone(nX, nY);
	if (retVal == IN_DEADZONE)
	{
		joystick.changeState(IdleJoystickState::getInstance());
		if (joystick.isPasswordSet())
		{
			joystick.position_states[3] = IdleJoystickState::getInstance();
		}
		Serial.println( "Joystick moved to Idle Position!");
	}
	else if (retVal == NOT_IN_DEADZONE)
	{
		Serial.println("Joystick is not in Deadzone! - Up");
	}
	else if (retVal == INVALID_PARAMETER)
	{
		Serial.println("Invalid parameters!");
	}
}
JoystickState* UpJoystickState::sInstance = NULL;
