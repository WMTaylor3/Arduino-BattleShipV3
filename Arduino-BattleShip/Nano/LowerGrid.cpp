/*
*	Arduino BattleShip game.
*
*	Source file for representation of the lower game grid.
*	Note: This only includes the vitual representation of the grid and the functions needed to maintain it.
*		  All methods related to drawing on the LED grid can be found in LEDMatrix.cpp and LEDMatrix.h.
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
		setShipLocation(ship[i], X);
		setShipLocation(ship[i], Y);
		if (!checkSpaceIsUnoccupied(ship[i]))
		{
			i--;
		}
	}
}

//Communicates with the user to set the location and rotation of a specific ship on the board.
void LowerGrid::setShipLocation(Ship& currentShip, positionType coordinate)
{
	InchDisplay* display = InchDisplay::getInstance();
	ButtonInterface* buttons = ButtonInterface::getInstance();
	buttonPress previousState = NoButton;
	buttonPress selectedButton;

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

		if (selectedButton == CenterPushed)
		{
			currentShip.attemptRotation();
		}
		else if (selectedButton == Left)
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
		else if (selectedButton == Right)
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
		else if (selectedButton == CenterHeld)
		{
			return;
		}
		else
		{
			//Do nothing.
		}

		previousState = selectedButton;
	}
}

//Checks the current ship is not in a location occupied by another ship.
bool LowerGrid::checkSpaceIsUnoccupied(Ship currentShip)
{
	Serial.print(F("Checking ship placement conflicts for ship #"));
	Serial.println(currentShip.getShipType());
	singleLocation position;
	for (uint8_t i = 0; i < currentShip.getShipType(); i++) //For each of the ships placed thus far...
	{
		Serial.println(i);
		if (currentShip.isShipVertical()) //If the ship we are currently placing is vertical, fix the X value and iterate along the Y value.
		{
			position.x = currentShip.getShipPosition().startPosition.x;
			for (position.y = currentShip.getShipPosition().startPosition.y; position.y <= currentShip.getShipPosition().endPosition.y; position.y++)
			{
				if (ship[i].isShipLocatedAtPosition(position)) //Check for each section of the currently placing ship whether it overlaps with another ship, if not move onto the next ship and check all of the current ships sections again.
				{
					return false;
				}
			}
		}
		else //If the ship is horizontal, do the same as above but iterating along the X axes.
		{
			position.y = currentShip.getShipPosition().startPosition.y;
			for (position.x = currentShip.getShipPosition().startPosition.x; position.x <= currentShip.getShipPosition().endPosition.x; position.x++)
			{
				if (ship[i].isShipLocatedAtPosition(position))
				{
					return false;
				}
			}
		}
	}
	Serial.println(F("Conflict check sucessful"));
	return true;
}

//Pulls the locations data from the five ships into the lower grid.
void LowerGrid::pullShipLocationsIntoLowerGrid()
{
	singleLocation sectionLocation;
	for (uint8_t i = 0; i < ship[Carrier].getShipLength(); i++)		//Pull Carrier locations.
	{
		sectionLocation = ship[Carrier].returnShipGridReference(i);
		recordStateToLocalGrid(Occupied, sectionLocation);
	}

	for (uint8_t i = 0; i < ship[Battleship].getShipLength(); i++)	//Pull Battleship locations.
	{
		sectionLocation = ship[Battleship].returnShipGridReference(i);
		recordStateToLocalGrid(Occupied, sectionLocation);
	}

	for (uint8_t i = 0; i < ship[Cruiser].getShipLength(); i++)		//Pull Cruiser locations.
	{
		sectionLocation = ship[Cruiser].returnShipGridReference(i);
		recordStateToLocalGrid(Occupied, sectionLocation);
	}

	for (uint8_t i = 0; i < ship[Submarine].getShipLength(); i++)	//Pull Submarine locations.
	{
		sectionLocation = ship[Submarine].returnShipGridReference(i);
		recordStateToLocalGrid(Occupied, sectionLocation);
	}

	for (uint8_t i = 0; i < ship[Destroyer].getShipLength(); i++)	//Pull Destroyer locations.
	{
		sectionLocation = ship[Destroyer].returnShipGridReference(i);
		recordStateToLocalGrid(Occupied, sectionLocation);
	}
}

//Checks a strike coming in from the other game board and illuminates the bottom display as required.
gridReferenceState LowerGrid::checkIncomingStrike(singleLocation strikePosition)
{
	gridReferenceState result;
	bool missed = true;

	for(Ship s : ship)
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

	if(missed)
	{
		result = Miss;
	}

	recordStateToLocalGrid(result, strikePosition);

	return result;
}

//Records a grid state at a location on the local grid.
void LowerGrid::recordStateToLocalGrid(gridReferenceState state, singleLocation gridPosition)
{
	//Minus one to translate between the 1-10 notation of the players view of the grid and the 0-9 representation of the array.
	grid[gridPosition.x - 1][gridPosition.y - 1] = state;
}