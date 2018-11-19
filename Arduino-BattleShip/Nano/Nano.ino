/*
 Name:		Nano.ino
 Created:	11/19/2018 12:13:19 AM
 Author:	William Taylor
*/

#include <Adafruit_SSD1306.h>
#include <gfxfont.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_GFX.h>

#include <BattleShipCommonTypes.h>
#include "InchDisplay.h"

InchDisplay display;

// the setup function runs once when you press reset or power the board
void setup()
{
	display.initializeDisplay();
	position a;
	a.x = 'H';
	a.y = 88;
	display.drawEnterTarget(a, 1);
}

// the loop function runs over and over again until power down or reset
void loop()
{
	
}