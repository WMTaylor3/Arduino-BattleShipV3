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
	InchDisplay();
	static InchDisplay* instance;
	void prepareForDraw(uint8_t size);
	void clearDisplay();
	void refreshDisplay();
	void drawStartAndEnd(singleLocation startPosition, singleLocation endPosition, positionType coordinate);
	void drawTargetPosition(singleLocation position);
public:
	~InchDisplay();
	static InchDisplay* getInstance();
	void initializeDisplay();
	void drawBattleShipLogo();
	void drawConnectionScreen();
	void drawConnectionFailed();
	void drawConnectionSucessful();
	void drawPlaceYourShips();
	void drawPlaceCarrier(singleLocation startPosition, singleLocation endPosition, positionType coordinate);
	void drawPlaceBattleShip(singleLocation startPosition, singleLocation endPosition, positionType coordinate);
	void drawPlaceCruiser(singleLocation startPosition, singleLocation endPosition, positionType coordinate);
	void drawPlaceSubmarine(singleLocation startPosition, singleLocation endPosition, positionType coordinate);
	void drawPlaceDestroyer(singleLocation startPosition, singleLocation endPosition, positionType coordinate);
	void drawEnterTarget(singleLocation startPosition);
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

