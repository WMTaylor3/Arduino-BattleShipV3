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
	Serial.begin(9600);
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
	Serial.print("Check0");
	homeTurn();
}

void GameLogic::homeTurn()
{
	display->drawYourTurn();
	delay(700);

	//Configure an initial strike position.
	singleLocation strikePosition;
	buttonPress selectedButton;
	buttonPress previousState = NoButton;

	strikePosition.x = 1;
	strikePosition.y = 1;

	upperGrid.displayGhostMark(strikePosition);

	while (true)
	{
		Serial.println("Check1");
		display->drawEnterTarget(strikePosition);

		selectedButton = buttons->getButtonPress(previousState);

		if (selectedButton != NoButton)
		{
			upperGrid.removeGhostMark(strikePosition);
			if (selectedButton == CenterPushed)
			{
				Serial.println("Center");
				bluetooth->transmitStrike(strikePosition);
			}
			else if (selectedButton == LeftPushed)
			{
				Serial.println("Left");
				strikePosition.x = ((strikePosition.x < 10) ? strikePosition.x + 1 : 1);
			}
			else if (selectedButton == RightPushed)
			{
				Serial.println("Right");
				strikePosition.y = ((strikePosition.y < 10) ? strikePosition.y + 1 : 1);
			}
			upperGrid.displayGhostMark(strikePosition);
		}

		previousState = selectedButton;
	}
}

void GameLogic::awayTurn()
{

}