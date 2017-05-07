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
      joystick = tempJoystick;
    }
    else if (joystick.getMode() == MODE_KORISTI)
    {
      // Check if user entered right combination
      if (joystick == tempJoystick)
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
  //Serial.println("Calling Start function");
  start();

/*
  Serial.println( );
    
  Serial.print("A0: ");
  Serial.println(map(analogRead(A0), 0, 530, 0, 1023) );
  Serial.print("A1: ");
  Serial.println(map(analogRead(A1), 0, 521, 0, 1023));
  _delay_ms(1000);
  */
}