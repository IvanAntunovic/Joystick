#include <iostream>
#include "Joystick.h"

using namespace std;

Joystick joystick;

void start(void)
{
	uint8_t nKeyPressed;
	Joystick tempJoystick;

	cout << "Enter the mode: ";
	cin >> nKeyPressed;

	if (nKeyPressed == 'P')
	{
		cout << "Postavi Mode running!" << endl;
		joystick.setMode(MODE_POSTAVI);
	}
	else if (nKeyPressed == 'K')
	{
		cout << "Koristi Mode running!" << endl;
		joystick.setMode(MODE_KORISTI);
	}

	tempJoystick.handlePositions();
	tempJoystick.printCurrentPositions();

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
			cout << "Suitcase opened" << endl;
		}
		else
		{
			cout << "Invalid combination" << endl;
		}
	}
	else
	{
		// Handle error
	}

	cout << endl;
}

int main(void)
{
	while (true)
	{
		start();
	}
	
}