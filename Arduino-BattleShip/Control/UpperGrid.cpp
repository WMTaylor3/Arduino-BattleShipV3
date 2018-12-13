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
#include "UpperGrid.h"

//Constructor. Creates a ship of each type and sets all grid references to empty.
UpperGrid::UpperGrid()
{
	for (uint8_t i = 0; i < 10; i++)	//For each row in the upper grid...
	{
		for (uint8_t j = 0; j < 10; j++)	//For each column in that row...
		{
			grid[i][j] = Empty;
		}
	}
}

//Destructor
UpperGrid::~UpperGrid()
{
	//Empty, nothing to be freed.
}

//Records a grid state at a location on the local grid.
void UpperGrid::recordStateToLocalGrid(gridReferenceState state, singleLocation gridPosition)
{
	//Minus one to translate between the 1-10 notation of the players view of the grid and the 0-9 representation of the array.
	grid[gridPosition.x - 1][gridPosition.y - 1] = state;
	transmitToMatrix(state, gridPosition);
}

//Adds a temporary mark to the LED matrix during the targeting process, not stored to the local grid.
void UpperGrid::displayGhostMark(singleLocation strikePosition)
{
	transmitToMatrix(Occupied, strikePosition);
	delay(15);
}

//Clears the temporary mark of the strikePosition from the LED matrix.
void UpperGrid::removeGhostMark(singleLocation strikePosition)
{
	transmitToMatrix(grid[strikePosition.x-1][strikePosition.y-1], strikePosition);
	delay(15);
}

//Method to transmit data to the grid Mega.
bool UpperGrid::transmitToMatrix(gridReferenceState state, singleLocation gridPosition)
{
	uint8_t message[3];

	//Construct message.
	message[0] = gridPosition.x - 1;
	message[1] = gridPosition.y - 1;
	message[2] = state;

	//Transmit to the grid.
	Serial2.write(message[0]);
	Serial2.write(message[1]);
	Serial2.write(message[2]);

	//Attempt to retrieve and validate confirmation message.
	for (uint8_t readAttempt = 0; readAttempt < 10; readAttempt++)
	{
		if (Serial2.read() == '-')
		{
			return true;
		}
		else
		{
			delay(1);
		}
	}
	return false;
}