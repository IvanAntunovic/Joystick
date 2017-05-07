#include "IdleJoystickState.h"

int8_t IdleJoystickState::getBufferFreeIndex(Joystick & joystick)
{
	if (joystick.position_states[2] != NULL && joystick.position_states[3] == IdleJoystickState::getInstance())
	{
		return NOK;
	}

	for (int8_t bufferFreeIndexNum = 0; bufferFreeIndexNum < POSITIONS_LENGTH; ++bufferFreeIndexNum)
	{
		if (joystick.position_states[bufferFreeIndexNum] == NULL)
		{
			return bufferFreeIndexNum;
		}
	}
	return NOK;
}

JoystickState * IdleJoystickState::getInstance()
{
	if (IdleJoystickState::sInstance == NULL)
	{
		IdleJoystickState::sInstance = new IdleJoystickState();
	}
	return IdleJoystickState::sInstance;
}

void IdleJoystickState::handleCoordinates(int nX, int nY, Joystick & joystick)
{
	int8_t retVal = joystick.getZone(nX, nY);
	
	if (retVal == NOT_IN_DEADZONE)
	{
		int8_t bufferFreeIndexNum;
		if (nX > MAX_X_POSITION)
		{
			bufferFreeIndexNum = this->getBufferFreeIndex(joystick);

			if (bufferFreeIndexNum != NOK)
			{
				joystick.changeState(RightJoystickState::getInstance());
				joystick.position_states[bufferFreeIndexNum] = RightJoystickState::getInstance();
				Serial.println( "Joystick moved to Right Position!");
			}
		}
		else if (nX < MIN_X_POSITION)
		{
			bufferFreeIndexNum = this->getBufferFreeIndex(joystick);

			if (bufferFreeIndexNum != NOK)
			{
				joystick.changeState(LeftJoystickState::getInstance());
				joystick.position_states[bufferFreeIndexNum] = LeftJoystickState::getInstance();
				Serial.println("Joystick moved to Left Position!");
			}
		}
		else if (nY > MAX_Y_POSITION)
		{
			bufferFreeIndexNum = this->getBufferFreeIndex(joystick);

			if (bufferFreeIndexNum != NOK)
			{
				joystick.changeState(UpJoystickState::getInstance());
				joystick.position_states[bufferFreeIndexNum] = UpJoystickState::getInstance();
				Serial.println("Joystick moved to Up Position!" );
			}
		}
		else if (nY < MIN_Y_POSITION)
		{
			bufferFreeIndexNum = this->getBufferFreeIndex(joystick);

			if (bufferFreeIndexNum != NOK)
			{
				joystick.changeState(DownJoystickState::getInstance());
				joystick.position_states[bufferFreeIndexNum] = DownJoystickState::getInstance();
				Serial.println( "Joystick moved to Down position!" );
			}
		}
	}
	else if (retVal == IN_DEADZONE)
	{
		Serial.println( "Joystick is in Deadzone! - Idle");
	}
	else if (retVal == INVALID_PARAMETER)
	{
		Serial.println("Invalid parameters!" );
	}
	
}
JoystickState* IdleJoystickState::sInstance = NULL;