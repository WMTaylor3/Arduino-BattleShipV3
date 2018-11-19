/*
*	Arduino BattleShip game.
*
*	Source file for representation of the players ship.
*
*	By William Taylor https://github.com/WMTaylor3
*/

#include <BattleShipCommonTypes.h>

#include "Ship.h"

//Constructor. Does not include ship locations, these are handled later after the user has performed input.
Ship::Ship(shipType typeOfShip)
{
	name = typeOfShip;	//Set ship type and therefore its name.

	switch (typeOfShip)	//Determine the length and therefore the maximum HP of the ship based on its type.
	{
	case(Carrier):
		maxSections = 5;
		break;
	case(Battleship):
		maxSections = 4;
		break;
	case(Cruiser):
		maxSections = 3;
		break;
	case(Submarine):
		maxSections = 3;
		break;
	case(Destroyer):
		maxSections = 2;
		break;
	}

	remainingSections = maxSections;	//Start Ship at full HP.
}

//Destructor
Ship::~Ship()
{
	//Empty, nothing to be freed.
}

void Ship::initializePosition(position newStartPosition, position newEndPosition)
{
	startPosition.x = newStartPosition.x;	//Set ship location values.
	endPosition.x = newEndPosition.x;
	startPosition.y = newStartPosition.y;
	endPosition.y = newEndPosition.y;
}

//Returns the length of the ship.
uint8_t Ship::getShipLength()
{
	return maxSections;
}

//Returns a structure containing a specified ship sections grid reference.
position Ship::returnShipGridReference(uint8_t sectionNumber)
{
	position sectionLocation;
	if (startPosition.x == endPosition.x)	//Ship is placed vertically.
	{
		sectionLocation.x = startPosition.x;
		sectionLocation.y = startPosition.y + sectionNumber;
	}
	else	//Ship is placed horizontally.
	{
		sectionLocation.x = startPosition.x + sectionNumber;
		sectionLocation.y = startPosition.y;
	}
	return sectionLocation;
}

//Based on the location provided as arguments, returns whether any part of the ship was located at the position, returns true if so, false if not.
bool Ship::isShipLocatedAtPosition(position strikePosition)
{
	if (((strikePosition.x >= startPosition.x) && (strikePosition.x <= endPosition.x) &&
		(strikePosition.y >= startPosition.y) && (strikePosition.y <= endPosition.y)))
	{
		remainingSections--;
		return true;
	}
	else
	{
		return false;
	}
}

//Should be called by caller only when "isShipLocatedAtPosition" returns true, evaluates if every section of the ship has been hit.
bool Ship::isShipSunk()
{
	if (remainingSections <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}