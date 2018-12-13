/*
*	Arduino BattleShip game.
*
*	Source file for representation of the lower game grid.
*	Note: This only includes the vitual representation of the grid and the functions needed to maintain it.
*		  All methods related to drawing on the LED grid can be found in MegaUpperGrid.ino.
*		  All functions related to the logical running of the game can be found in GameLogic.cpp and GameLogic.h
*
*	By William Taylor https://github.com/WMTaylor3
*/
#include <MemoryFree.h>

#include "LowerGrid.h"
#include "ButtonInterface.h"

//Constructor. Creates a ship of each type and sets all grid references to empty.
LowerGrid::LowerGrid() : ship{ Carrier, Battleship, Cruiser, Submarine, Destroyer }
{
	Serial.print(F("LowerGrid.cpp: Beginning Construction of LowerGrid. FreeMemory = "));
	Serial.println(freeMemory());
	delay(300);
	for (uint8_t i = 0; i < 10; i++)	//For each row in the upper grid...
	{
		for (uint8_t j = 0; j < 10; j++)	//For each column in that row...
		{
			grid[i][j] = Empty;
		}
	}

	display = InchDisplay::getInstance();
	Serial.print(F("LowerGrid.cpp: Completed Construction of LowerGrid. FreeMemory = "));
	Serial.println(freeMemory());
	delay(300);
}

//Destructor
LowerGrid::~LowerGrid()
{
	//Empty, nothing to be freed.
}

//Assigns each ship its position, should be called from GameLogic suring inital game set up.
void LowerGrid::initializeShipLocations()
{
	display->drawPlaceYourShips();
	delay(1500);

	for (int i = 0; i < 5; i++)
	{
		buttonPress result = setShipLocation(ship[i], X);
		while (true)
		{
			if (result == LeftHeld)
			{
				result = setShipLocation(ship[i], X);
			}
			else if (result == RightHeld)
			{
				result = setShipLocation(ship[i], Y);
			}
			else
			{
				break;
			}
		}
		if (!checkSpaceIsUnoccupied(ship[i]))
		{
			i--;
		}
		else
		{
			pullShipLocationsIntoLowerGrid(ship[i]);
		}
	}
}

//Communicates with the user to set the location and rotation of a specific ship on the board.
buttonPress LowerGrid::setShipLocation(Ship& currentShip, positionType coordinate)
{
	Serial.println("Placing Ship");
	InchDisplay* display = InchDisplay::getInstance();
	ButtonInterface* buttons = ButtonInterface::getInstance();
	buttonPress previousState = NoButton;
	buttonPress selectedButton;
	displayShipGhostOutline(currentShip);

	while (true)
	{
		switch (currentShip.getShipType())
		{
		case(Carrier):
			display->drawPlaceCarrier(currentShip.getShipPosition().startPosition, currentShip.getShipPosition().endPosition, coordinate);
			break;
		case(Battleship):
			display->drawPlaceBattleShip(currentShip.getShipPosition().startPosition, currentShip.getShipPosition().endPosition, coordinate);
			break;
		case(Cruiser):
			display->drawPlaceCruiser(currentShip.getShipPosition().startPosition, currentShip.getShipPosition().endPosition, coordinate);
			break;
		case(Submarine):
			display->drawPlaceSubmarine(currentShip.getShipPosition().startPosition, currentShip.getShipPosition().endPosition, coordinate);
			break;
		case(Destroyer):
			display->drawPlaceDestroyer(currentShip.getShipPosition().startPosition, currentShip.getShipPosition().endPosition, coordinate);
			break;
		}

		selectedButton = buttons->getButtonPress(previousState);

		if (selectedButton != NoButton)
		{
			removeShipGhostOutline(currentShip);
			if (selectedButton == CenterPushed)
			{
				currentShip.attemptRotation();
			}
			else if (selectedButton == LeftPushed)
			{
				if (coordinate == X)
				{
					currentShip.decrementXPosition();
				}
				else if (coordinate == Y)
				{
					currentShip.decrementYPosition();
				}
			}
			else if (selectedButton == RightPushed)
			{
				if (coordinate == X)
				{
					currentShip.incrementXPosition();
				}
				else if (coordinate == Y)
				{
					currentShip.incrementYPosition();
				}
			}
			else if (selectedButton == CenterHeld)
			{
				return CenterHeld;
			}
			else if (selectedButton == LeftHeld)
			{
				return LeftHeld;
			}
			else if (selectedButton == RightHeld)
			{
				return RightHeld;
			}
			displayShipGhostOutline(currentShip);
		}

		previousState = selectedButton;
	}
}

//Checks if a ships placement conflicts with any preexisting placements.
bool LowerGrid::checkSpaceIsUnoccupied(Ship currentShip)
{
	for (uint8_t section = 0; section < currentShip.getShipLength(); section++) //For each section in this current ship being placed...
	{
		if (!checkGridReferenceIsUnoccupied(currentShip, currentShip.getShipSectionGridReference(section)))
		{
			return false;
		}
	}
	return true;
}

//Checks if a single grid reference is unoccupied.
bool LowerGrid::checkGridReferenceIsUnoccupied(Ship latestShipPlaced, singleLocation position)
{
	for (uint8_t inspectedShip = 0; inspectedShip < latestShipPlaced.getShipType(); inspectedShip++) //For each of the ships placed thus far...
	{
		if (ship[inspectedShip].isShipLocatedAtPosition(position)) //Ensure the current section is nowhere along an existing ship.
		{
			return false;
		}
	}
	return true;
}

//Pulls the locations data from the five ships into the lower grid.
void LowerGrid::pullShipLocationsIntoLowerGrid(Ship currentShip)
{
	for (uint8_t i = 0; i < currentShip.getShipLength(); i++)
	{
		recordStateToLocalGrid(Occupied, currentShip.getShipSectionGridReference(i));
		delay(20);
	}
}

//Records a grid state at a location on the local grid.
void LowerGrid::recordStateToLocalGrid(gridReferenceState state, singleLocation gridPosition)
{
	//Minus one to translate between the 1-10 notation of the players view of the grid and the 0-9 representation of the array.
	grid[gridPosition.x - 1][gridPosition.y - 1] = state;
	transmitToMatrix(state, gridPosition);
}

//Adds a temporary ship to the LED matrix suring the ship placement routine, not stored to the local grid.
void LowerGrid::displayShipGhostOutline(Ship ship)
{
	for (uint8_t section = 0; section < ship.getShipLength(); section++)
	{
		if (checkGridReferenceIsUnoccupied(ship, ship.getShipSectionGridReference(section)))
		{
			transmitToMatrix(Occupied, ship.getShipSectionGridReference(section));
			delay(15);
		}
		else
		{
			transmitToMatrix(Hit, ship.getShipSectionGridReference(section));
			delay(15);
		}
	}
}

//Clears the temporary outline of the ship from the LED matrix. (During ship placement)
void LowerGrid::removeShipGhostOutline(Ship ship)
{
	for (uint8_t section = 0; section < ship.getShipLength(); section++)
	{
		if (checkGridReferenceIsUnoccupied(ship, ship.getShipSectionGridReference(section)))
		{
			transmitToMatrix(Empty, ship.getShipSectionGridReference(section));
			delay(15);
		}
		else
		{
			transmitToMatrix(Occupied, ship.getShipSectionGridReference(section));
			delay(15);
		}
	}
}

//Method to transmit data to the grid Mega.
bool LowerGrid::transmitToMatrix(gridReferenceState state, singleLocation gridPosition)
{
	uint8_t message[3];

	//Construct message.
	message[0] = gridPosition.x - 1;
	message[1] = gridPosition.y - 1;
	message[2] = state;

	//Transmit to the grid.
	Serial1.write(message[0]);
	Serial1.write(message[1]);
	Serial1.write(message[2]);

	//Attempt to retrieve and validate confirmation message.
	for (uint8_t readAttempt = 0; readAttempt < 10; readAttempt++)
	{
		if (Serial1.read() == '-')
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

//Checks a strike coming in from the other game board.
gridReferenceState LowerGrid::checkIncomingStrike(singleLocation strikePosition)
{
	gridReferenceState result;
	bool missed = true;

	for (Ship s : ship)
	{
		if (s.isShipLocatedAtPosition(strikePosition))
		{
			missed = false;
			if (s.isShipSunk())
			{
				result = HitAndSunk;
			}
			else
			{
				result = Hit;
			}
		}
	}

	if (missed)
	{
		result = Miss;
	}

	recordStateToLocalGrid(result, strikePosition);

	return result;
}