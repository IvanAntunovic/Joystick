#pragma once
#include <iostream>

using namespace std;
class Joystick;

class JoystickState
{
	protected:
		JoystickState() {};
	public:
		virtual void handleCoordinates(int, int, Joystick&) = 0;
};

