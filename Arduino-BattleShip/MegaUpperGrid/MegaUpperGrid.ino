/*
 Name:		MegaUpperGrid.ino
 Created:	11/22/2018 1:19:41 AM
 Author:	William Taylor
*/

// the setup function runs once when you press reset or power the board
#include <BattleShipCommonTypes.h>
#include "LEDMatrix.h"

LEDMatrix grid;

void setup()
{

}

// the loop function runs over and over again until power down or reset
void loop()
{
	grid.RefreshGrid();
}
