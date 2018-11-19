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
	shipLocation location = placeShip(Carrier);
	
}

shipLocation placeShip(shipType ship)
{
	shipLocation location;
	location.startPosition.x = 1;
	location.startPosition.y = 1;

	switch (ship)
	{
	case(Carrier):
		location.endPosition.x = 5;
		location.endPosition.y = 1;
		location.startPosition.x = getShipSingleStartCoordinate(location, Carrier, StartX);
		location.startPosition.x = getShipSingleStartCoordinate(location, Carrier, StartY);
		break;
	}
}

char getShipSingleStartCoordinate(shipLocation location, shipType ship, positionType coordinate)
{
	uint8_t value = location.startPosition.x;
	while (true) //Loop until the user presses the center button, returning the value to the caller.
	{
		if (coordinate == StartX)
		{
			location.startPosition.x = value;
		}
		else if (coordinate == StartY)
		{
			location.startPosition.y = value;
		}

		switch (ship)
		{
		case(Carrier):
			display.drawPlaceCarrier(location.startPosition, location.endPosition, coordinate);
			break;
		case(Battleship):
			display.drawPlaceBattleShip(location.startPosition, location.endPosition, coordinate);
			break;
		case(Cruiser):
			display.drawPlaceCruiser(location.startPosition, location.endPosition, coordinate);
			break;
		case(Submarine):
			display.drawPlaceSubmarine(location.startPosition, location.endPosition, coordinate);
			break;
		case(Destroyer):
			display.drawPlaceDestroyer(location.startPosition, location.endPosition, coordinate);
			break;
		}

		buttonPress selection = getButtonPress();
		if (selection == Center)
		{
			return value;
		}
		else if ((selection == Left) && (value + 1 <= 10))
		{
			value++;
		}
		else if ((selection == Right) && (value - 1 >= 1))
		{
			value--;
		}
		else
		{
			//Do nothing.
		}
	}
}

buttonPress getButtonPress()
{
	while (true) //Wait for user input. Loop until one of the buttons is brought high.
	{
		//Leftmost button
		if ((digitalRead(buttonLeft) == HIGH) && (digitalRead(buttonCenter) == LOW) && (digitalRead(buttonRight) == LOW))
		{
			delay(150);
			return Left;
		}
		//Centermost button
		if ((digitalRead(buttonLeft) == LOW) && (digitalRead(buttonCenter) == HIGH) && (digitalRead(buttonRight) == LOW))
		{
			delay(150);
			return Center;
		}
		//Rightmost button
		if ((digitalRead(buttonLeft) == LOW) && (digitalRead(buttonCenter) == LOW) && (digitalRead(buttonRight) == HIGH))
		{
			delay(150);
			return Right;
		}
	}
}
