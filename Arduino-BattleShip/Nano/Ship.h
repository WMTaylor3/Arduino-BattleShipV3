/*
*	Arduino BattleShip game.
*
*	Source file for representation of the players ship.
*
*	By William Taylor https://github.com/WMTaylor3
*/

#ifndef _SHIP_h
#define _SHIP_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <BattleShipCommonTypes.h>

class Ship
{
private:
	shipType name;
	uint8_t maxSections;	//Number of sections on the ship 5, 4, 3 or 2. Essentially the ships Hit Points (HP)
	uint8_t remainingSections;	//Remaining sections on the ship not yet hit. Essentially the "Remaining HP"
	shipLocation position;
public:
	Ship(shipType type);
	~Ship();
	shipType getShipType();
	shipLocation getShipPosition();
	uint8_t getShipLength();
	void incrementXPosition();
	void decrementXPosition();
	void incrementYPosition();
	void decrementYPosition();
	void attemptRotation();
	singleLocation returnShipGridReference(uint8_t sectionNumber);
	bool isShipLocatedAtPosition(singleLocation strikePosition);
	bool isShipSunk();
};

#endif