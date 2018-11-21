/*
*	Arduino BattleShip game.
*
*	The source file that contains the basic game logic.
*	This includes the functions that make up the inital set up as well as the turn by turn play of the game.
*
*	By William Taylor https://github.com/WMTaylor3
*/
#include <MemoryFree.h>

#include "GameLogic.h"
GameLogic* GameLogic::instance = 0;

//Constructor
GameLogic::GameLogic()
{
	//Empty
}

//Destructor.
GameLogic::~GameLogic()
{
	free(instance);
}

//In accordance to singleton pattern this method is used instead of a public constructor to ensure only one instance exists.
GameLogic* GameLogic::getInstance()
{
	Serial.print(F("GameLogic.cpp: Entered getInstance. FreeMemory = "));
	Serial.println(freeMemory());
	delay(300);
	if (instance == 0)
	{
		instance = new GameLogic();
	}
	Serial.print(F("GameLogic.cpp: Returning from getInstance. FreeMemory = "));
	Serial.println(freeMemory());
	delay(300);
	return instance;
}

void GameLogic::initializeGame()
{
	Serial.print(F("GameLogic.cpp: Initalizing Ship Locations. FreeMemory = "));
	Serial.println(freeMemory());
	delay(300);
	lowerGrid.initializeShipLocations();
}