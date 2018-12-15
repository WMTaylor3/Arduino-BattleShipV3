/*
*	Arduino BattleShip game.
*
*	Source file for representation of the upper game grid.
*	Note: This only includes the vitual representation of the grid and the functions needed to maintain it.
*		  All methods related to drawing on the LED grid can be found in Grid.ino.
*		  All functions related to the logical running of the game can be found in GameLogic.cpp and GameLogic.h
*
*	By William Taylor https://github.com/WMTaylor3
*/

#ifndef _UPPERGRID_h
#define _UPPERGRID_h

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

class UpperGrid
{
private:
	gridReferenceState grid[10][10];
public:
	UpperGrid();
	~UpperGrid();
	void displayGhostMark(singleLocation strikePosition);
	void removeGhostMark(singleLocation strikePosition);
	void recordStateToLocalGrid(gridReferenceState state, singleLocation gridPosition);
	bool transmitToMatrix(gridReferenceState state, singleLocation gridPosition);
};

#endif

