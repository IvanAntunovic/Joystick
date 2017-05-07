#include <iostream>
#include "Joystick.h"

using namespace std;

Joystick joystick;

void start(void)
{
	uint8_t nKeyPressed;
	Joystick tempJoystick;

	Serial.println("Enter the key: ");
	cin >> nKeyPressed;

	if (nKeyPressed == 'P')
	{
		Serial.println("Postavi Mode running!");
		joystick.setMode(MODE_POSTAVI);
	}
	else if (nKeyPressed == 'K')
	{
		Serial.println("Koristi Mode running!" );
		joystick.setMode(MODE_KORISTI);
	}

	tempJoystick.handlePositions();

	if (joystick.getMode() == MODE_POSTAVI)
	{
		// Copy values from one object to another
		joystick = tempJoystick;
	}
	else if (joystick.getMode() == MODE_KORISTI)
	{
		// Check if user entered right combination
		if (joystick == tempJoystick)
		{
			Serial.println("Suitcase opened" );
		}
		else
		{
			Serial.println("Invalid combination" );
		}
	}
	else
	{
		// Handle error
	}

	cout );
}

int main(void)
{
	while (true)
	{
		start();
	}
	
}