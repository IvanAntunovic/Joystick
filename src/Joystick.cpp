#include "Joystick.h"

Joystick::Joystick()
{
	for (int positionCounter = 0; positionCounter < POSITIONS_LENGTH - 1; ++positionCounter)
	{
		position_states[positionCounter] = NULL;
	}
	this->currentState = IdleJoystickState::getInstance();
	this->currentMode = -1;
}

void Joystick::setMode(int newMode)
{
	this->currentMode = newMode;
}

int Joystick::getMode()
{
	return this->currentMode;
}

Joystick & Joystick::operator=(const Joystick & other)
{
	if (this == &other)
	{
		return *this;
	}

	for (int positionCounter = 0; positionCounter < POSITIONS_LENGTH - 1; ++positionCounter)
	{
		this->position_states[positionCounter] = other.position_states[positionCounter];
	}
	return *this;
}

void Joystick::handlePositions(void)
{
	int nX = -1;
	int nY = -1;

	while (this->position_states[2] == NULL || this->position_states[3] != IdleJoystickState::getInstance())
	{
		cout << "Enter coordinate nX: ";
		cin >> nX;
		cout << "Enter coordinate nY: ";
		cin >> nY;
		this->currentState->handleCoordinates(nX, nY, *this);
	}
}

int8_t Joystick::getZone(int nX, int nY)
{
	if (nX < 0 && nX > 1023 || nY < 0 && nY > 1023)
	{
		return INVALID_PARAMETER;
	}

	if (nX > MAX_X_POSITION || nX < MIN_X_POSITION || nY > MAX_Y_POSITION || nY < MIN_Y_POSITION)
	{
		return NOT_IN_DEADZONE;
	}
	return IN_DEADZONE;
}

void Joystick::changeState(JoystickState * newState)
{
	this->currentState = newState;
}

bool Joystick::isPasswordSet(void)
{
	if (this->position_states[2] != NULL && this->position_states[3] != IdleJoystickState::getInstance())
	{
		return true;
	}
	return false;
}

int8_t Joystick::getStateBufferFreeIndex(void)
{
	if (this->isPasswordSet())
	{
		return NOK;
	}

	for (int8_t bufferFreeIndexNum = 0; bufferFreeIndexNum < POSITIONS_LENGTH; ++bufferFreeIndexNum)
	{
		if (this->position_states[bufferFreeIndexNum] == NULL)
		{
			return bufferFreeIndexNum;
		}
	}
	return NOK;
}

void Joystick::printCurrentPositions(void)
{
	cout << "You have entered the following positions: " << endl;
	for (uint8_t currentPosition = 0; currentPosition < POSITIONS_LENGTH - 1; ++currentPosition)
	{
		printf("%d: ", currentPosition);
		if (this->position_states[currentPosition] == RightJoystickState::getInstance())
		{
			cout << ("Right Position") << endl;
		}
		else if (this->position_states[currentPosition] == LeftJoystickState::getInstance())
		{
			cout << ("Left Position") << endl;
		}
		else if (this->position_states[currentPosition] == UpJoystickState::getInstance())
		{
			cout << ("Up Position") << endl;
		}
		else if (this->position_states[currentPosition] == DownJoystickState::getInstance())
		{
			cout << "Down Position" << endl;
		}
		else
		{
			cout << "Unknown Position" << endl;
		}
	}
}

bool operator==(const Joystick & joystickOne, const Joystick & joystickTwo)
{
	for (int positionCounter = 0; positionCounter < POSITIONS_LENGTH - 1; ++positionCounter)
	{
		if (joystickOne.position_states[positionCounter] != joystickTwo.position_states[positionCounter])
		{
			return false;
		}
	}
	return true;
}
