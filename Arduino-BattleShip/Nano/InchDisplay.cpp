/*
*	Arduino BattleShip game.
*
*	Source file for representation of the 0.96" OLED Display connected.
*
*	By William Taylor https ://github.com/WMTaylor3
*/
#include <gfxfont.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_GFX.h>

#include "InchDisplay.h"

InchDisplay::InchDisplay() : display(-1)
{

}

InchDisplay::~InchDisplay()
{

}

void InchDisplay::prepareForDraw(uint8_t size)
{
	display.setTextSize(size);
	display.setTextColor(1);
	display.clearDisplay();
}

void InchDisplay::clearDisplay()
{
	display.clearDisplay();
}

void InchDisplay::refreshDisplay()
{
	display.display();
}

void InchDisplay::initializeDisplay()
{
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void InchDisplay::drawBattleShipLogo()
{
	prepareForDraw(3);
	for (uint8_t i = 0; i < display.height() / 2; i += 3)
	{
		display.fillRect(i, i, display.width() - i * 2, display.height() - i * 2, 1);
		display.display();
		delay(50);
		display.clearDisplay();
		delay(50);
	}
	display.setCursor(12, 6);
	display.print("BATTLE");
	display.setCursor(30, 39);
	display.print("SHIP");
	display.display();
	delay(2000);
}

void InchDisplay::drawConnectionScreen()
{
	prepareForDraw(2);
	display.setCursor(22, 14);
	display.print("SEEKING");
	display.setCursor(22, 39);
	display.print("PARTNER");
	display.display();
}

void InchDisplay::drawPlaceYourShips()
{
	prepareForDraw(2);
	display.setCursor(4, 14);
	display.print("PLACE YOUR");
	display.setCursor(37, 39);
	display.print("SHIPS");
	display.display();
}

void InchDisplay::drawPlaceCarrier(position startPosition, position endPosition)
{
	prepareForDraw(2);
	display.setCursor(22, 14);
	display.print("CARRIER");
	display.setCursor(22, 39);
	display.print(startPosition.y);
	display.setCursor(34, 39);
	display.print(startPosition.x);
	display.setCursor(40, 39);
	display.print(" TO ");
	display.setCursor(82, 39);
	display.print(endPosition.y);
	display.setCursor(94, 39);
	display.print(endPosition.x);
	display.display();
}

void InchDisplay::drawPlaceBattleShip(position startPosition, position endPosition)
{
	prepareForDraw(2);
	display.setCursor(4, 14);
	display.print("BATTLESHIP");
	display.setCursor(22, 39);
	display.print(startPosition.y);
	display.setCursor(34, 39);
	display.print(startPosition.x);
	display.setCursor(40, 39);
	display.print(" TO ");
	display.setCursor(82, 39);
	display.print(endPosition.y);
	display.setCursor(94, 39);
	display.print(endPosition.x);
	display.display();
}

void InchDisplay::drawPlaceCruiser(position startPosition, position endPosition)
{
	prepareForDraw(2);
	display.setCursor(22, 14);
	display.print("CRUISER");
	display.setCursor(22, 39);
	display.print(startPosition.y);
	display.setCursor(34, 39);
	display.print(startPosition.x);
	display.setCursor(40, 39);
	display.print(" TO ");
	display.setCursor(82, 39);
	display.print(endPosition.y);
	display.setCursor(94, 39);
	display.print(endPosition.x);
	display.display();
}

void InchDisplay::drawPlaceSubmarine(position startPosition, position endPosition)
{
	prepareForDraw(2);
	display.setCursor(10, 14);
	display.print("SUBMARINE");
	display.setCursor(22, 39);
	display.print(startPosition.y);
	display.setCursor(34, 39);
	display.print(startPosition.x);
	display.setCursor(40, 39);
	display.print(" TO ");
	display.setCursor(82, 39);
	display.print(endPosition.y);
	display.setCursor(94, 39);
	display.print(endPosition.x);
	display.display();
}

void InchDisplay::drawPlaceDestroyer(position startPosition, position endPosition)
{
	prepareForDraw(2);
	display.setCursor(10, 14);
	display.print("DESTROYER");
	display.setCursor(22, 39);
	display.print(startPosition.y);
	display.setCursor(34, 39);
	display.print(startPosition.x);
	display.setCursor(40, 39);
	display.print(" TO ");
	display.setCursor(82, 39);
	display.print(endPosition.y);
	display.setCursor(94, 39);
	display.print(endPosition.x);
	display.display();
}

void InchDisplay::drawEnterTarget(position targetPosition)
{
	prepareForDraw(2);
	uint8_t offset = 0;
	if (targetPosition.y == 10)
	{
		offset = 6;
	}
	display.setCursor(28, 14);
	display.print("TARGET");
	display.setCursor(52 - offset, 39);
	display.write(targetPosition.x);
	display.setCursor(64 - offset, 39);
	display.print(targetPosition.y + 0);
	display.display();
}

void InchDisplay::drawYourTurn()
{

}

void InchDisplay::drawTheirTurn()
{

}

void InchDisplay::drawFire()
{

}

void InchDisplay::drawHit()
{

}

void InchDisplay::drawHitAndSunk()
{

}

void InchDisplay::drawMiss()
{

}

void InchDisplay::drawYouWin()
{

}

void InchDisplay::drawYouLose()
{

}