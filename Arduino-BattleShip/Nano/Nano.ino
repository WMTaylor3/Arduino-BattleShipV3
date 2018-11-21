/*
 Name:		Nano.ino
 Created:	11/19/2018 12:13:19 AM
 Author:	William Taylor
*/

#include <MemoryFree.h>
#include "ButtonInterface.h"
#include "InchDisplay.h"
#include "LowerGrid.h"
#include "GameLogic.h"
#include "Ship.h"
#include <Adafruit_SSD1306.h>
#include <gfxfont.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_GFX.h>

#include <BattleShipCommonTypes.h>

InchDisplay* display;
GameLogic* game;

// the setup function runs once when you press reset or power the board
void setup()
{
	Serial.begin(9600);
	Serial.print(F("Nano.ino: Beginning Setup. FreeMemory = "));
	Serial.println(freeMemory());
	delay(300);
	display = InchDisplay::getInstance();
	display->initializeDisplay();
	display->drawBattleShipLogo();

	Serial.print(F("Nano.ino: Initialized Display. FreeMemory = "));
	Serial.println(freeMemory());
	delay(300);
	game = GameLogic::getInstance();
	Serial.print(F("Nano.ino: Completed Construction of GameLogic. FreeMemory = "));
	Serial.println(freeMemory());
	delay(300);
	game->initializeGame();
	Serial.print("Nano.ino: Completed Initialization of GameLogic. FreeMemory = ");
	Serial.println(freeMemory());
	delay(300);
}

// the loop function runs over and over again until power down or reset
void loop()
{
	
}
