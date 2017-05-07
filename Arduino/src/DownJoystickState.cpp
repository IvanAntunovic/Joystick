#include "DownJoystickState.h"


JoystickState* DownJoystickState::getInstance() {
	if (DownJoystickState::sInstance == NULL)
	{
		DownJoystickState::sInstance = new DownJoystickState();
	}
	return DownJoystickState::sInstance;
}

void DownJoystickState::handleCoordinates(int nX, int nY, Joystick & joystick)
{
	int8_t retVal = joystick.getZone(nX, nY);
	if (retVal == IN_DEADZONE)
	{
		joystick.changeState(IdleJoystickState::getInstance());
		if (joystick.isPasswordSet())
		{
			joystick.position_states[3] = IdleJoystickState::getInstance();
		}
		Serial.println("Joystick moved to Idle Position!");
	}
	else if (retVal == NOT_IN_DEADZONE)
	{
		Serial.println( "Joystick is not in Deadzone! - Down");
	}
	else if (retVal == INVALID_PARAMETER)
	{
		Serial.println("Invalid parameters!");
	}
}
JoystickState* DownJoystickState::sInstance = NULL;


