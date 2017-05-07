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
		nX = analogRead(A0);
		Serial.print( "Coordinate nX: ");
		//Serial.println( map(nX, 0, 530, 0, 1023) );
		Serial.println(nX);
		nY = analogRead(A1);
		Serial.print("Coordinate nY: ");
		Serial.println(nY);
		//Serial.println( map(nY, 0, 521, 0, 1023) );
		//_delay_ms(1500);
		
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

void Joystick::printCurrentPositions(void)
{
	Serial.println("You have entered the following positions: ");
	for (uint8_t currentPosition = 0; currentPosition < POSITIONS_LENGTH - 1; ++currentPosition)
	{
		Serial.print(currentPosition);
		Serial.print(".: ");
		if (this->position_states[currentPosition] == RightJoystickState::getInstance())
		{
			Serial.println("Right Position");
		}
		else if (this->position_states[currentPosition] == LeftJoystickState::getInstance())
		{
			Serial.println("Left Position");
		}
		else if (this->position_states[currentPosition] == UpJoystickState::getInstance())
		{
			Serial.println("Up Position");
		}
		else if (this->position_states[currentPosition] == DownJoystickState::getInstance()) 
		{
			Serial.println("Down Position");
		}
		else
		{
			Serial.println("Unknown Position");
		}
	}
	Serial.println("");
}

void Joystick::storePasswordInEEPROM(void)
{
	for (uint8_t currentPosition = 0; currentPosition < POSITIONS_LENGTH - 1; ++currentPosition)
	{
		Serial.print(currentPosition);
		Serial.print(".: ");
		if (this->position_states[currentPosition] == RightJoystickState::getInstance())
		{
			EEPROM.write(currentPosition, eRIGHT);
		}
		else if (this->position_states[currentPosition] == LeftJoystickState::getInstance())
		{
			EEPROM.write(currentPosition, eLEFT);
		}
		else if (this->position_states[currentPosition] == UpJoystickState::getInstance())
		{
			EEPROM.write(currentPosition, eUP);
		}
		else if (this->position_states[currentPosition] == DownJoystickState::getInstance()) 
		{
			EEPROM.write(currentPosition, eDOWN);
		}
		else
		{
			Serial.println("Unknown Position");
		}
	}
}

bool Joystick::isEqualToEEPROM(void)
{
	uint8_t tempBuffer[3];
	for (int currentPosition = 0; currentPosition < POSITIONS_LENGTH - 1; ++currentPosition)
	{
		if (this->position_states[currentPosition] == RightJoystickState::getInstance())
		{
			tempBuffer[currentPosition] = eRIGHT;
		}
		else if (this->position_states[currentPosition] == LeftJoystickState::getInstance())
		{
			tempBuffer[currentPosition] = eLEFT;
		}
		else if (this->position_states[currentPosition] == UpJoystickState::getInstance())
		{
			tempBuffer[currentPosition] = eUP;
		}
		else if (this->position_states[currentPosition] == DownJoystickState::getInstance()) 
		{
			tempBuffer[currentPosition] = eDOWN;
		}
		else
		{
			tempBuffer[currentPosition] = eIDLE;
		}	
		
		if (EEPROM.read(currentPosition) != tempBuffer[currentPosition])
		{
			return false;
		}
	}
	return true;
}

bool operator==(const Joystick & joystickOne, const Joystick & joystickTwo)
{
/*	for (int positionCounter = 0; positionCounter < POSITIONS_LENGTH - 1; ++positionCounter)
	{
		if (joystickOne.position_states[positionCounter] != joystickTwo.position_states[positionCounter])
		{
			return false;
		}
	}
	return true;
*/
}
