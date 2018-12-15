/*
*	Arduino BattleShip game.
*
*	Source file for representation of the 0.96" OLED Display connected.
*
*	By William Taylor https://github.com/WMTaylor3
*/
#include <gfxfont.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <Adafruit_GFX.h>

#include "InchDisplay.h"
InchDisplay* InchDisplay::instance = 0;

InchDisplay::InchDisplay() : display(-1)
{
	//Empty
}

InchDisplay::~InchDisplay()
{

}

//In accordance to singleton pattern this method is used instead of a public constructor to ensure only one instance exists.
InchDisplay* InchDisplay::getInstance()
{
	if (instance == 0)
	{
		instance = new InchDisplay();
	}

	return instance;
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

void InchDisplay::drawStartAndEnd(singleLocation startPosition, singleLocation endPosition, positionType coordinate)
{
	if (startPosition.y == 9 && endPosition.y == 9)
	{
		if (coordinate == X)
		{
			display.fillRect(9, 38, 12, 16, 1);
			display.setTextColor(0);
		}
		display.setCursor(10, 39);
		display.write(startPosition.x + 65);
		display.setTextColor(1);

		if (coordinate == Y)
		{
			display.fillRect(21, 38, 24, 16, 1);
			display.setTextColor(0);
		}
		display.setCursor(22, 39);
		display.print(startPosition.y + 1);
		display.setTextColor(1);

		display.setCursor(40, 39);
		display.print(F(" TO "));

		display.setCursor(82, 39);
		display.write(endPosition.x + 65);
		display.setCursor(94, 39);
		display.print(endPosition.y + 1);
	}
	else if (startPosition.y >= 9 && endPosition.y < 9)
	{
		if (coordinate == X)
		{
			display.fillRect(15, 38, 12, 16, 1);
			display.setTextColor(0);
		}
		display.setCursor(16, 39);
		display.write(startPosition.x + 65);
		display.setTextColor(1);

		if (coordinate == Y)
		{
			display.fillRect(27, 38, 24, 16, 1);
			display.setTextColor(0);
		}
		display.setCursor(28, 39);
		display.print(startPosition.y + 1);
		display.setTextColor(1);

		display.setCursor(46, 39);
		display.print(F(" TO "));

		display.setCursor(88, 39);
		display.write(endPosition.x + 65);
		display.setCursor(100, 39);
		display.print(endPosition.y + 1);
	}
	else if (startPosition.y < 9 && endPosition.y >= 9)
	{
		if (coordinate == X)
		{
			display.fillRect(15, 38, 12, 16, 1);
			display.setTextColor(0);
		}
		display.setCursor(16, 39);
		display.write(startPosition.x + 65);
		display.setTextColor(1);

		if (coordinate == Y)
		{
			display.fillRect(27, 38, 12, 16, 1);
			display.setTextColor(0);
		}
		display.setCursor(28, 39);
		display.print(startPosition.y + 1);
		display.setTextColor(1);

		display.setCursor(34, 39);
		display.print(F(" TO "));

		display.setCursor(76, 39);
		display.write(endPosition.x + 65);
		display.setCursor(88, 39);
		display.print(endPosition.y + 1);
	}
	else
	{
		if (coordinate == X)
		{
			display.fillRect(21, 38, 12, 16, 1);
			display.setTextColor(0);
		}
		display.setCursor(22, 39);
		display.write(startPosition.x + 65);
		display.setTextColor(1);

		if (coordinate == Y)
		{
			display.fillRect(33, 38, 12, 16, 1);
			display.setTextColor(0);
		}
		display.setCursor(34, 39);
		display.print(startPosition.y + 1);
		display.setTextColor(1);

		display.setCursor(40, 39);
		display.print(F(" TO "));

		display.setCursor(82, 39);
		display.write(endPosition.x + 65);
		display.setCursor(94, 39);
		display.print(endPosition.y + 1);
	}
}

void InchDisplay::drawTargetPosition(singleLocation position)
{
	display.setCursor(52, 39);
	display.write(position.x + 65);
	display.setTextColor(1);

	display.setCursor(64, 39);
	display.print(position.y + 1);
	display.setTextColor(1);
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
	display.print(F("BATTLE"));
	display.setCursor(30, 39);
	display.print(F("SHIP"));
	display.display();
	delay(2000);
}

void InchDisplay::drawConnectionScreen()
{
	prepareForDraw(2);
	display.setCursor(22, 14);
	display.print(F("SEEKING"));
	display.setCursor(22, 39);
	display.print(F("PARTNER"));
	display.display();
}

void InchDisplay::drawConnectionFailed()
{
	prepareForDraw(2);
	display.setCursor(22, 14);
	display.print(F("SEEKING"));
	display.setCursor(28, 39);
	display.print(F("FAILED"));
	display.display();
}

void InchDisplay::drawConnectionSucessful()
{
	prepareForDraw(2);
	display.setCursor(22, 14);
	display.print(F("SEEKING"));
	display.setCursor(18, 39);
	display.print(F("COMPLETE"));
	display.display();
}

void InchDisplay::drawPlaceYourShips()
{
	prepareForDraw(2);
	display.setCursor(4, 14);
	display.print(F("PLACE YOUR"));
	display.setCursor(37, 39);
	display.print(F("SHIPS"));
	display.display();
}

void InchDisplay::drawPlaceCarrier(singleLocation startPosition, singleLocation endPosition, positionType coordinate)
{
	prepareForDraw(2);
	display.setCursor(22, 14);
	display.print(F("CARRIER"));
	drawStartAndEnd(startPosition, endPosition, coordinate);
	display.display();
}

void InchDisplay::drawPlaceBattleShip(singleLocation startPosition, singleLocation endPosition, positionType coordinate)
{
	prepareForDraw(2);
	display.setCursor(4, 14);
	display.print(F("BATTLESHIP"));
	drawStartAndEnd(startPosition, endPosition, coordinate);
	display.display();
}

void InchDisplay::drawPlaceCruiser(singleLocation startPosition, singleLocation endPosition, positionType coordinate)
{
	prepareForDraw(2);
	display.setCursor(22, 14);
	display.print(F("CRUISER"));
	drawStartAndEnd(startPosition, endPosition, coordinate);
	display.display();
}

void InchDisplay::drawPlaceSubmarine(singleLocation startPosition, singleLocation endPosition, positionType coordinate)
{
	prepareForDraw(2);
	display.setCursor(10, 14);
	display.print(F("SUBMARINE"));
	drawStartAndEnd(startPosition, endPosition, coordinate);
	display.display();
}

void InchDisplay::drawPlaceDestroyer(singleLocation startPosition, singleLocation endPosition, positionType coordinate)
{
	prepareForDraw(2);
	display.setCursor(10, 14);
	display.print(F("DESTROYER"));
	drawStartAndEnd(startPosition, endPosition, coordinate);
	display.display();
}

void InchDisplay::drawEnterTarget(singleLocation targetPosition)
{
	prepareForDraw(2);
	display.setCursor(28, 14);
	display.print(F("TARGET"));
	drawTargetPosition(targetPosition);
	display.display();
}

void InchDisplay::drawYourTurn()
{
	prepareForDraw(2);
	display.setCursor(41, 14);
	display.print(F("YOUR"));
	display.setCursor(41, 39);
	display.print(F("TURN"));
	display.display();
}

void InchDisplay::drawTheirTurn()
{
	prepareForDraw(2);
	display.setCursor(35, 14);
	display.print(F("THEIR"));
	display.setCursor(41, 39);
	display.print(F("TURN"));
	display.display();
}

void InchDisplay::drawFire()
{
	for (uint8_t i = 0; i < 5; i++)
	{
		prepareForDraw(4);
		display.setCursor(8, 18);
		display.print(F("FIRE!"));
		display.display();
		delay(200);
		display.clearDisplay();
		delay(200);
		display.display();
		delay(200);
		display.clearDisplay();
		delay(200);
	}
}

void InchDisplay::drawSending()
{
	for (uint8_t i = 0; i < 5; i++)
	{
		prepareForDraw(2);
		display.setCursor(4, 24);
		display.print(F("SENDING..."));
		display.display();
	}
}

void InchDisplay::drawHit()
{
	prepareForDraw(4);
	display.setCursor(20, 18);
	display.print(F("HIT!"));
	display.display();
}

void InchDisplay::drawHitAndSunk()
{
	prepareForDraw(2);
	display.setCursor(46, 14);
	display.print(F("HIT"));
	display.setCursor(16, 39);
	display.print(F("AND SUNK"));
	display.display();
}

void InchDisplay::drawMiss()
{
	prepareForDraw(4);
	display.setCursor(18, 18);
	display.print(F("MISS"));
	display.display();
}

void InchDisplay::drawYouWin()
{
	prepareForDraw(3);
	display.setCursor(38, 6);
	display.print(F("YOU"));
	display.setCursor(38, 39);
	display.print(F("WIN"));
	display.display();
}

void InchDisplay::drawYouLose()
{
	prepareForDraw(3);
	display.setCursor(38, 6);
	display.print(F("YOU"));
	display.setCursor(28, 39);
	display.print(F("LOSE"));
	display.display();
}