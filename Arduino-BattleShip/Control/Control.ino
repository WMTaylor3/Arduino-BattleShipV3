/*
 Name:		Control.ino
 Created:	11/19/2018 12:13:19 AM
 Author:	William Taylor
*/

#include "UpperGrid.h"
#include "LowerGrid.h"
#include "BluetoothModule.h"
#include "ButtonInterface.h"
#include "Ship.h"
#include "InchDisplay.h"
#include "GameLogic.h"
#include <Adafruit_SSD1306.h>
#include <gfxfont.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_GFX.h>

#include <BattleShipCommonTypes.h>

//A constant char used to define the role of the board.
//This should be changed between uploads to each board.
const boardRole ROLE = Master;

uint16_t turnCount = 1;

InchDisplay* display;
ButtonInterface* buttons;
BluetoothModule* bluetooth;
GameLogic* game;

//The setup function runs once when you press reset or power the board
void setup()
{
	Serial.begin(9600);		//Computer Communication.
	Serial1.begin(115200);	//Lower Grid Communication.
	Serial2.begin(115200);	//Upper Grid Communication.
	Serial3.begin(38400);	//Bluetooth Communication.

	//Build inch display interface instance. Singleton object can be accessed throughout the project.
	display = InchDisplay::getInstance();
	display->initializeDisplay();
	display->drawBattleShipLogo();

	//Build button interface instance. Singleton object can be accessed throughout the project.
	buttons = ButtonInterface::getInstance();
	
	//Build bluetooth interface instance. Singleton object can be accessed throughout the project.
	bluetooth = BluetoothModule::getInstance();
	display->drawConnectionScreen();
	if (!bluetooth->establishConnection(ROLE))
	{
		display->drawConnectionFailed();
		delay(1000);
		exit(404);
	}
	display->drawConnectionSucessful();
	
	//Build game logic instance. Singleton object can be accessed throughout the project.
	game = GameLogic::getInstance();
	game->initializeGame();
}

//The loop function runs over and over again until power down or reset
void loop()
{
	if (turnCount % 2 == ROLE % 2)
	{
		game->homeTurn();
	}
	else
	{
		game->awayTurn();
	}

	turnCount++;
	
	winner gameStatus = game->endGameCheck();

	if (gameStatus == Winner)
	{
		display->drawYouWin();
		exit(10);
	}
	else if(gameStatus == Loser)
	{
		display->drawYouLose();
		exit(20);
	}
	else
	{
		//Continue game.
	}
}