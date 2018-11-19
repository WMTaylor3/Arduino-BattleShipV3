/*
*	Arduino BattleShip game.
*
*	Source file for representation of the 0.96" OLED Display connected..
*
*	By William Taylor https://github.com/WMTaylor3
*/

#ifndef _INCHDISPLAY_h
#define _INCHDISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Adafruit_SSD1306.h>
#include <BattleShipCommonTypes.h>

class InchDisplay
{
private:
	Adafruit_SSD1306 display;
	void prepareForDraw(uint8_t size);
	void clearDisplay();
	void refreshDisplay();
	void drawStartAndEnd(position startPosition, position endPosition, positionType coordinate);
public:
	InchDisplay();
	~InchDisplay();
	void initializeDisplay();
	void drawBattleShipLogo();
	void drawConnectionScreen();
	void drawPlaceYourShips();
	void drawPlaceCarrier(position startPosition, position endPosition, positionType coordinate);
	void drawPlaceBattleShip(position startPosition, position endPosition, positionType coordinate);
	void drawPlaceCruiser(position startPosition, position endPosition, positionType coordinate);
	void drawPlaceSubmarine(position startPosition, position endPosition, positionType coordinate);
	void drawPlaceDestroyer(position startPosition, position endPosition, positionType coordinate);
	void drawEnterTarget(position startPosition, positionType coordinate);
	void drawYourTurn();
	void drawTheirTurn();
	void drawFire();
	void drawHit();
	void drawHitAndSunk();
	void drawMiss();
	void drawYouWin();
	void drawYouLose();
};

#endif

