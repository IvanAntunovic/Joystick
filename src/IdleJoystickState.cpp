#include "IdleJoystickState.h"

int8_t IdleJoystickState::getBufferFreeIndex(Joystick & joystick)
{
	if (joystick.position_states[2] != NULL && joystick.position_states[3] == IdleJoystickState::getInstance())
	{
		return NOK;
	}

	for (int i = 0; i < POSITIONS_LENGTH; ++i)
	{
		if (joystick.position_states[i] == NULL)
		{
			return i;
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
				cout << "Joystick moved to Right Position!" << endl;
			}
		}
		else if (nX < MIN_X_POSITION)
		{
			bufferFreeIndexNum = this->getBufferFreeIndex(joystick);

			if (bufferFreeIndexNum != NOK)
			{
				joystick.changeState(LeftJoystickState::getInstance());
				joystick.position_states[bufferFreeIndexNum] = RightJoystickState::getInstance();
				cout << "Joystick moved to Left Position!" << endl;
			}
		}
		else if (nY > MAX_Y_POSITION)
		{
			bufferFreeIndexNum = this->getBufferFreeIndex(joystick);

			if (bufferFreeIndexNum != NOK)
			{
				joystick.changeState(UpJoystickState::getInstance());
				joystick.position_states[bufferFreeIndexNum] = UpJoystickState::getInstance();
				cout << "Joystick moved to Up Position!" << endl;
			}
		}
		else if (nY < MIN_Y_POSITION)
		{
			bufferFreeIndexNum = this->getBufferFreeIndex(joystick);

			if (bufferFreeIndexNum != NOK)
			{
				joystick.changeState(DownJoystickState::getInstance());
				joystick.position_states[bufferFreeIndexNum] = DownJoystickState::getInstance();
				cout << "Joystick moved to Down position!" << endl;
			}
		}
	}
	else if (retVal == IN_DEADZONE)
	{
		cout << "Joystick is in Deadzone!" << endl;
	}
	else if (retVal == INVALID_PARAMETER)
	{
		cout << "Invalid parameters!" << endl;
	}
	
}
JoystickState* IdleJoystickState::sInstance = NULL;