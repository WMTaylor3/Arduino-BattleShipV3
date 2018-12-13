/*
*	Arduino BattleShip game.
*
*	Source file for communication with the three buttons at the bottom of the board.
*
*	By William Taylor https://github.com/WMTaylor3
*/

#ifndef _BUTTONINTERFACE_h
#define _BUTTONINTERFACE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <BattleShipCommonTypes.h>

class ButtonInterface
{
private:
	ButtonInterface();
	static ButtonInterface* instance;
	uint8_t buttonLeft = A1;
	uint8_t buttonCenter = A2;
	uint8_t buttonRight = A3;
public:
	~ButtonInterface();
	static ButtonInterface* getInstance();
	buttonPress getButtonPress(buttonPress previousState);
};

#endif-