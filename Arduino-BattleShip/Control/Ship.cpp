/*
*	Arduino BattleShip game.
*
*	Source file for representation of the players ship.
*
*	By William Taylor https://github.com/WMTaylor3
*/

#include <MemoryFree.h>

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

	position.startPosition.x = 0;
	position.startPosition.y = 0;
	position.endPosition.x = position.startPosition.x + (getShipLength() - 1);
	position.endPosition.y = 0;
}

//Destructor
Ship::~Ship()
{
	//Empty, nothing to be freed.
}

shipType Ship::getShipType()
{
	return name;
}

//Returns the position of the ship.
shipLocation Ship::getShipPosition()
{
	return position;
}

//Returns the length of the ship.
uint8_t Ship::getShipLength()
{
	return maxSections;
}

bool Ship::isShipVertical()
{
	return vertical;
}

void Ship::incrementXPosition()
{
	if ((position.startPosition.x + 1 >= 0) && (position.endPosition.x + 1 <= 9))
	{
		position.startPosition.x++;
		position.endPosition.x++;
	}
}

void Ship::decrementXPosition()
{
	if ((position.startPosition.x - 1 >= 0) && (position.endPosition.x - 1 <= 9))
	{
		position.startPosition.x--;
		position.endPosition.x--;
	}
}

void Ship::incrementYPosition()
{
	if ((position.startPosition.y + 1 >= 0) && (position.endPosition.y + 1 <= 9))
	{
		position.startPosition.y++;
		position.endPosition.y++;
	}
}

void Ship::decrementYPosition()
{
	if ((position.startPosition.y - 1 >= 0) && (position.endPosition.y - 1 <= 9))
	{
		position.startPosition.y--;
		position.endPosition.y--;
	}
}

bool Ship::attemptRotation()
{
	if (vertical) //Ship is vertical and should be rotated horizontally.
	{
		uint8_t length = position.endPosition.y - position.startPosition.y;
		if (position.endPosition.x + length <= 9)
		{
			position.endPosition.x = position.startPosition.x + length;
			position.endPosition.y = position.startPosition.y;
			vertical = false;
			return true;
		}
	}
	else //Ship is horizontal and should be rotated vertically.
	{
		uint8_t length = position.endPosition.x - position.startPosition.x;
		if (position.endPosition.y + length <= 9)
		{
			position.endPosition.y = position.startPosition.y + length;
			position.endPosition.x = position.startPosition.x;
			vertical = true;
			return true;
		}
		else
		{
			return false;
		}
	}
}

//Returns a structure containing a specified ship sections grid reference.
singleLocation Ship::getShipSectionGridReference(uint8_t sectionNumber)
{
	singleLocation sectionLocation;
	if (vertical)	//Ship is placed vertically.
	{
		sectionLocation.x = position.startPosition.x;
		sectionLocation.y = position.startPosition.y + sectionNumber;
	}
	else	//Ship is placed horizontally.
	{
		sectionLocation.x = position.startPosition.x + sectionNumber;
		sectionLocation.y = position.startPosition.y;
	}
	return sectionLocation;
}

//Based on the location provided as arguments, returns whether any part of the ship was located at the position, returns true if so, false if not.
bool Ship::isShipLocatedAtPosition(singleLocation strikePosition)
{
	if (((strikePosition.x >= position.startPosition.x) && (strikePosition.x <= position.endPosition.x) &&
		(strikePosition.y >= position.startPosition.y) && (strikePosition.y <= position.endPosition.y)))
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