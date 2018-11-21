/*
*	Arduino BattleShip game.
*
*	Source file for interfacing with the LED Grid.
*
*	By William Taylor https://github.com/WMTaylor3
*/

#include <BattleShipCommonTypes.h>

#ifndef _LEDMATRIX_h
#define _LEDMATRIX_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class LEDMatrix
{
private:
	gridReferenceState grid[10][10];	//Representation of the board to be drawn on the grid.
	uint8_t columnConnections[10][3];	//The addresses of the pins of each of the columns (10) and their colors (3).
	uint8_t layerConnection;			//The address of the pin which triggers the decade counter.
	uint8_t layerReset;					//The address of the pin which resets the decade counter to 0.
	void initializeSoftConnections();	//Assigns the correct number to each of the columnConnections array members and layerConnection.
	void initializeHardConnections();	//Configures the Arduino I/O according to columnConnections and layerConnection.
public:
	LEDMatrix();
	~LEDMatrix();
	void RefreshGrid();
};

#endif