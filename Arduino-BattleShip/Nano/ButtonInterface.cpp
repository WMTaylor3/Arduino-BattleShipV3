/*
*	Arduino BattleShip game.
*
*	Source file for communication witht he three buttons at the bottom of the board.
*
*	By William Taylor https://github.com/WMTaylor3
*/

#include "ButtonInterface.h"
ButtonInterface* ButtonInterface::instance = 0;

//Constructor
ButtonInterface::ButtonInterface()
{
	pinMode(buttonLeft, INPUT);
	pinMode(buttonCenter, INPUT);
	pinMode(buttonRight, INPUT);
}

//Destructor
ButtonInterface::~ButtonInterface()
{

}

//In accordance to singleton pattern this method is used instead of a public constructor to ensure only one instance exists.
ButtonInterface* ButtonInterface::getInstance()
{
	if (instance == 0)
	{
		instance = new ButtonInterface();
	}

	return instance;
}

buttonPress ButtonInterface::getButtonPress(buttonPress previousState = NoButton)
{
	//No button selected
	if ((digitalRead(buttonLeft) == LOW) && (digitalRead(buttonCenter) == LOW) && (digitalRead(buttonRight) == LOW))
	{
		return NoButton;
	}
	//Left button
	if ((digitalRead(buttonLeft) == HIGH) && (digitalRead(buttonCenter) == LOW) && (digitalRead(buttonRight) == LOW) && (previousState == NoButton))
	{
		while (digitalRead(buttonLeft) == HIGH) { delay(10); }
		Serial.println("Left");
		return Left;
	}
	//Center button
	if ((digitalRead(buttonLeft) == LOW) && (digitalRead(buttonCenter) == HIGH) && (digitalRead(buttonRight) == LOW) && (previousState == NoButton))
	{
		unsigned long startTime = millis();
		while (digitalRead(buttonCenter) == HIGH) { delay(10); }
		unsigned long endTime = millis();
		if (endTime - startTime >= 500)
		{
			Serial.println("Held");
			return CenterHeld;
		}
		else
		{
			Serial.println("Pushed");
			return CenterPushed;
		}
	}
	//Right button
	if ((digitalRead(buttonLeft) == LOW) && (digitalRead(buttonCenter) == LOW) && (digitalRead(buttonRight) == HIGH) && (previousState == NoButton))
	{
		while (digitalRead(buttonRight) == HIGH) { delay(10); }
		Serial.println("Right");
		return Right;
	}
}