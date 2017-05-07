#pragma once

#ifndef _JOYSTICK_STATE_H_
#define _JOYSTICK_STATE_H_

#include "HardwareSerial.h"
extern HardwareSerial Serial;

#include <stdint.h>
class Joystick;

#ifndef NULL
#define NULL 0
#endif


class JoystickState
{
	protected:
		JoystickState() {};
	public:
		virtual void handleCoordinates(int, int, Joystick&) = 0;
};

#endif

