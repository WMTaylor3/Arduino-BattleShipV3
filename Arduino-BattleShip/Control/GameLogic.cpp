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