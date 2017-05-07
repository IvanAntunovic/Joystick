#include "Joystick.h"

Joystick joystick;

void start(void)
{
  uint8_t nKeyPressed;
  Joystick tempJoystick;

  Serial.print( "Enter the key: ");
  while(!Serial.available());
  nKeyPressed = Serial.read();

  if (nKeyPressed == 'P')
  {
    Serial.println( "Postavi Mode running!" );
    joystick.setMode(MODE_POSTAVI);
  }
  else if (nKeyPressed == 'K')
  {
    Serial.println( "Koristi Mode running!" );
    joystick.setMode(MODE_KORISTI);
  }

  if (nKeyPressed == 'P' || nKeyPressed == 'K')
  {
    tempJoystick.handlePositions();
    tempJoystick.printCurrentPositions();
    if (joystick.getMode() == MODE_POSTAVI)
    {
      // Copy values from one object to another
      //joystick = tempJoystick;
	  tempJoystick.storePasswordInEEPROM();
    }
    else if (joystick.getMode() == MODE_KORISTI)
    {
      // Check if user entered right combination
      //if (joystick == tempJoystick)
	  if (tempJoystick.isEqualToEEPROM())
      {
        Serial.println( "Suitcase opened" );
      }
      else
      {
        Serial.println( "Invalid combination" );
      }
    }
    else
    {
      // Handle error
    }
  }
  else
  {
    Serial.println("Invalid Key entered! Enter either 'P' or 'K' key from your keyboard!");
  }
 

  Serial.println("");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}


void loop() 
{
  start();
}