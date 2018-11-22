/*
*	Arduino BattleShip game.
*
*	Source file for any user defined types or enums used within the project.
*
*	By William Taylor https://github.com/WMTaylor3
*/

#ifndef _USERDEFINEDTYPES_h
#define _USERDEFINEDTYPES_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//Represents a single position on one of the gameboards grids.
struct singleLocation
{
	uint8_t x;
	uint8_t y;
};

//Used to transmit the start and end positions of the ships during game set up.
struct shipLocation
{
	singleLocation startPosition;
	singleLocation endPosition;
};

//Used to initialize the LED grids.
struct gridConnections
{
	uint8_t layerTrigger;	//Identifies which pin the decade counter is connected to.
	uint8_t ledConnections[10][3];	//Identifies where each vLEDs anode is controlled from.
};

typedef enum { LeftPushed, LeftHeld, CenterPushed, CenterHeld, RightPushed, RightHeld, NoButton } buttonPress;
typedef enum { X, Y } positionType;
typedef enum { Carrier = 0, Battleship = 1, Cruiser = 2, Submarine = 3, Destroyer = 4 } shipType;
typedef enum { Hit = 0, HitAndSunk = 1, Miss = 2, Occupied = 3, Empty = 4 } gridReferenceState;

#endif