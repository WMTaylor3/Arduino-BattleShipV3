/*
*	Arduino BattleShip game.
*
*	Source file for representation of the lower game grid.
*	Note: This only includes the vitual representation of the grid and the functions needed to maintain it.
*		  All methods related to drawing on the LED grid can be found in Grid.ino.
*		  All functions related to the logical running of the game can be found in GameLogic.cpp and GameLogic.h
*
*	By William Taylor https://github.com/WMTaylor3
*/

#ifndef _LOWERGRID_h
#define _LOWERGRID_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <BattleShipCommonTypes.h>

#include "Ship.h"
#include "InchDisplay.h"
#include "ButtonInterface.h"
#include "BluetoothModule.h"

class LowerGrid
{
private:
	gridReferenceState grid[10][10];
	Ship ship[5];
	InchDisplay* display;
	ButtonInterface* buttons;
	buttonPress setShipLocation(Ship& currentShip, positionType coordinate);
	bool checkSpaceIsUnoccupied(Ship currentShip);
	bool checkGridReferenceIsUnoccupied(Ship latestShipPlaced, singleLocation position);
	void pullShipLocationsIntoLowerGrid(Ship latestShipPlaced);
	void recordStateToLocalGrid(gridReferenceState state, singleLocation gridPosition);
public:
	LowerGrid();
	~LowerGrid();
	void initializeShipLocations();
	void displayShipGhostOutline(Ship ship);
	void removeShipGhostOutline(Ship ship);
	bool transmitToMatrix(gridReferenceState state, singleLocation gridPosition);
	gridReferenceState checkIncomingStrike(singleLocation strikePosition);
};

#endif

