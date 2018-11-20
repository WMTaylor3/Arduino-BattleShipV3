/*
 Name:		Nano.ino
 Created:	11/19/2018 12:13:19 AM
 Author:	William Taylor
*/

#include "Ship.h"
#include <Adafruit_SSD1306.h>
#include <gfxfont.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_GFX.h>

#include <BattleShipCommonTypes.h>
#include "InchDisplay.h"

#define buttonLeft A1
#define buttonCenter A2
#define buttonRight A3

InchDisplay display;


// the setup function runs once when you press reset or power the board
void setup()
{
	pinMode(buttonLeft, INPUT);
	pinMode(buttonCenter, INPUT);
	pinMode(buttonRight, INPUT);

	Serial.begin(9600);

	display.initializeDisplay();
	//display.drawBattleShipLogo();
	layoutShips();
}

// the loop function runs over and over again until power down or reset
void loop()
{
	
}

void layoutShips()
{
	//display.drawPlaceYourShips();
	
	//delay(1500);
	Ship carrier(Carrier);
	setShipSingleCoordinate(Carrier, X);
	setShipSingleCoordinate(Carrier, Y);
}

void setShipSingleCoordinate(Ship ship, positionType coordinate)
{
	buttonPress previousState = NoButton;
	buttonPress selectedButton;

	while (true) //Loop until the user presses the center button.
	{
		switch (ship.getShipType())
		{
		case(Carrier):
			display.drawPlaceCarrier(ship.getShipPosition().startPosition, ship.getShipPosition().endPosition, coordinate);
			break;
		case(Battleship):
			display.drawPlaceBattleShip(ship.getShipPosition().startPosition, ship.getShipPosition().endPosition, coordinate);
			break;
		case(Cruiser):
			display.drawPlaceCruiser(ship.getShipPosition().startPosition, ship.getShipPosition().endPosition, coordinate);
			break;
		case(Submarine):
			display.drawPlaceSubmarine(ship.getShipPosition().startPosition, ship.getShipPosition().endPosition, coordinate);
			break;
		case(Destroyer):
			display.drawPlaceDestroyer(ship.getShipPosition().startPosition, ship.getShipPosition().endPosition, coordinate);
			break;
		}

		selectedButton = getButtonPress(previousState);

		if (selectedButton == CenterPushed)
		{
			ship.attemptRotation();
		}
		else if (selectedButton == Left)
		{
			if (coordinate == X)
			{
				ship.incrementXPosition();
			}
			else if(coordinate == Y)
			{
				ship.incrementYPosition();
			}
		}
		else if (selectedButton == Right)
		{
			if (coordinate == X)
			{
				ship.decrementXPosition();
			}
			else if (coordinate == Y)
			{
				ship.decrementYPosition();
			}
		}
		else if (selectedButton == CenterHeld)
		{
			return;
		}
		else
		{
			//Do nothing.
		}

		previousState = selectedButton;
	}
}

buttonPress getButtonPress(buttonPress previousState)
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
		if (endTime - startTime >= 1000)
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
