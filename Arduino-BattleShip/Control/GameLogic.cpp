/*
*	Arduino BattleShip game.
*
*	The source file that contains the basic game logic.
*	This includes the functions that make up the inital set up as well as the turn by turn play of the game.
*
*	By William Taylor https://github.com/WMTaylor3
*/

#include "GameLogic.h"
GameLogic* GameLogic::instance = 0;

//Constructor
GameLogic::GameLogic()
{
	display = InchDisplay::getInstance();
	buttons = ButtonInterface::getInstance();
	bluetooth = BluetoothModule::getInstance();
	remainingHomeShips = 5;
	remainingAwayShips = 5;
}

//Destructor.
GameLogic::~GameLogic()
{
	free(instance);
}

//In accordance to singleton pattern this method is used instead of a public constructor to ensure only one instance exists.
GameLogic* GameLogic::getInstance()
{
	if (instance == 0)
	{
		instance = new GameLogic();
	}
	return instance;
}

void GameLogic::initializeGame()
{
	lowerGrid.initializeShipLocations();
}

void GameLogic::homeTurn()
{
	display->drawYourTurn();
	delay(750);
	singleLocation strikePosition = targetOpponent();
	display->drawFire();
	bluetooth->transmitStrike(strikePosition);
	gridReferenceState strikeResponse = bluetooth->receiveResponse();
	updateDisplayWithStrikeResponse(strikeResponse);
	upperGrid.recordStateToLocalGrid(strikeResponse, strikePosition);
	if (strikeResponse == HitAndSunk) { remainingAwayShips--; }
}

singleLocation GameLogic::targetOpponent()
{
	//Configure an initial strike position.
	singleLocation strikePosition;
	buttonPress selectedButton;
	buttonPress previousState = NoButton;

	strikePosition.x = 1;
	strikePosition.y = 1;

	upperGrid.displayGhostMark(strikePosition);

	//Target opponent.
	while (true)
	{
		display->drawEnterTarget(strikePosition);

		selectedButton = buttons->getButtonPress(previousState);

		if (selectedButton != NoButton)
		{
			upperGrid.removeGhostMark(strikePosition);
			if (selectedButton == CenterPushed)
			{
				return strikePosition;
			}
			else if (selectedButton == LeftPushed)
			{
				strikePosition.x = ((strikePosition.x < 10) ? strikePosition.x + 1 : 1);
			}
			else if (selectedButton == RightPushed)
			{
				strikePosition.y = ((strikePosition.y < 10) ? strikePosition.y + 1 : 1);
			}
			upperGrid.displayGhostMark(strikePosition);
		}

		previousState = selectedButton;
	}
}

void GameLogic::awayTurn()
{
	display->drawTheirTurn();
	delay(750);
	singleLocation strikePosition = bluetooth->receiveStrike();
	gridReferenceState strikeResponse = lowerGrid.checkIncomingStrike(strikePosition);
	bluetooth->transmitResponse(strikeResponse);
	updateDisplayWithStrikeResponse(strikeResponse);
	lowerGrid.recordStateToLocalGrid(strikeResponse, strikePosition);
	if (strikeResponse == HitAndSunk) { remainingHomeShips--; }
}

void GameLogic::updateDisplayWithStrikeResponse(gridReferenceState response)
{
	switch (response)
	{
	case(Hit):
		display->drawHit();
		break;
	case(HitAndSunk):
		display->drawHitAndSunk();
		break;
	case(Miss):
		display->drawHit();
		break;
	}
}

winner GameLogic::endGameCheck()
{
	if ((remainingHomeShips == 0) || (remainingAwayShips == 0))
	{
		if (remainingHomeShips == 0)
		{
			return Loser;
		}
		else if (remainingAwayShips == 0)
		{
			return Winner;
		}
	}
	else
	{
		return GameInProgress;
	}
}