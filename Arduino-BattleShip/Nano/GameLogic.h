/*
*	Arduino BattleShip game.
*
*	The source file that contains the basic game logic.
*	This includes the functions that make up the inital set up as well as the turn by turn play of the game.
*
*	By William Taylor https://github.com/WMTaylor3
*/

#ifndef _GAMELOGIC_h
#define _GAMELOGIC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <BattleShipCommonTypes.h>
#include "LowerGrid.h"

class GameLogic
{
	private:
		GameLogic();
		static GameLogic* instance;
		LowerGrid lowerGrid;
	public:
		~GameLogic();
		static GameLogic* getInstance();
		void initializeGame();
};

#endif