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
	position startPosition;
	position endPosition;
public:
	Ship(shipType type);
	~Ship();
	void initializePosition(position startPosition, position endPosition);
	uint8_t getShipLength();
	position returnShipGridReference(uint8_t sectionNumber);
	bool isShipLocatedAtPosition(position strikePosition);
	bool isShipSunk();
};

#endif

