/*
*	Arduino BattleShip game.
*
*	Source file for interfacing with the LED Grid.
*
*	By William Taylor https://github.com/WMTaylor3
*/

#include "LEDMatrix.h"

//Constructor
LEDMatrix::LEDMatrix()
{/*
	for (uint8_t i = 0; i < 10; i++)
	{
		grid[0][i] = Hit;
		grid[1][i] = Hit;
		grid[2][i] = Hit;
		grid[3][i] = Hit;
		grid[4][i] = Hit;
		grid[5][i] = Hit;
		grid[6][i] = Hit;
		grid[7][i] = Hit;
		grid[8][i] = Hit;
		grid[9][i] = Hit;
	}
	
	for (uint8_t i = 0; i < 10; i++)
	{
		grid[0][i] = Miss;
		grid[1][i] = Miss;
		grid[2][i] = Miss;
		grid[3][i] = Miss;
		grid[4][i] = Miss;
		grid[5][i] = Miss;
		grid[6][i] = Miss;
		grid[7][i] = Miss;
		grid[8][i] = Miss;
		grid[9][i] = Miss;
	}
	
	for (uint8_t i = 0; i < 10; i++)
	{
		grid[0][i] = Occupied;
		grid[1][i] = Occupied;
		grid[2][i] = Occupied;
		grid[3][i] = Occupied;
		grid[4][i] = Occupied;
		grid[5][i] = Occupied;
		grid[6][i] = Occupied;
		grid[7][i] = Occupied;
		grid[8][i] = Occupied;
		grid[9][i] = Occupied;
	}
	*/
	
	for (uint8_t i = 0; i < 10; i++)
	{
		grid[0][i] = Empty;
		grid[1][i] = Hit;
		grid[2][i] = Miss;
		grid[3][i] = Occupied;
		grid[4][i] = Empty;
		grid[5][i] = Hit;
		grid[6][i] = Miss;
		grid[7][i] = Occupied;
		grid[8][i] = Empty;
		grid[9][i] = Hit;
	}

	initializeSoftConnections();
	initializeHardConnections();
}

//Destructor empty.
LEDMatrix::~LEDMatrix()
{

}

void LEDMatrix::initializeSoftConnections()
{
	columnConnections[0][0] = 24; //C1R
	columnConnections[0][1] = 23; //C1G
	columnConnections[0][2] = 22; //C1B

	columnConnections[1][0] = 35; //C2R
	columnConnections[1][1] = 36; //C2G
	columnConnections[1][2] = 37; //C2B

	columnConnections[2][0] = 51; //C3R
	columnConnections[2][1] = 52; //C3G
	columnConnections[2][2] = 53; //C3B

	columnConnections[3][0] = 27; //C4R
	columnConnections[3][1] = 26; //C4G
	columnConnections[3][2] = 25; //C4B

	columnConnections[4][0] = 47; //C5R
	columnConnections[4][1] = 48; //C5G
	columnConnections[4][2] = 49; //C5B

	columnConnections[5][0] = 8; //C6R
	columnConnections[5][1] = 7; //C6G
	columnConnections[5][2] = 6; //C6B

	columnConnections[6][0] = 39; //C7R
	columnConnections[6][1] = 29; //C7G
	columnConnections[6][2] = 28; //C7B

	columnConnections[7][0] = 32; //C8R
	columnConnections[7][1] = 33; //C8G
	columnConnections[7][2] = 34; //C8B

	columnConnections[8][0] = 11; //C9R
	columnConnections[8][1] = 10; //C9G
	columnConnections[8][2] = 50; //C9B

	columnConnections[9][0] = 9; //C10R
	columnConnections[9][1] = 46; //C10G
	columnConnections[9][2] = 15; //C10B

	layerConnection = 2;
	layerReset = 3;
}

void LEDMatrix::initializeHardConnections()
{
	for (uint8_t column = 0; column < 10; column++)
	{
		for (uint8_t color = 0; color < 3; color++)
		{
			uint8_t pin = columnConnections[column][color];
			pinMode(pin, OUTPUT);
		}
	}

	pinMode(layerConnection, OUTPUT);
	pinMode(layerReset, OUTPUT);
}

void LEDMatrix::RefreshGrid()
{
	digitalWrite(layerReset, HIGH); //Reset the decade counter to zero.
	digitalWrite(layerReset, LOW);

	for (uint8_t row = 0; row < 10; row++) //For each row of the board.
	{
		for (uint8_t column = 0; column < 10; column++) //For each column on the board.
		{
			switch (grid[row][column]) //Configure columns.
			{
			case Hit:
				digitalWrite(columnConnections[column][0], HIGH); //Red On.
				digitalWrite(columnConnections[column][1], LOW); //Green Off.
				digitalWrite(columnConnections[column][2], LOW); //Blue Off.
				break;
			case HitAndSunk:
				digitalWrite(columnConnections[column][0], HIGH); //Red On.
				digitalWrite(columnConnections[column][1], LOW); //Green Off.
				digitalWrite(columnConnections[column][2], LOW); //Blue Off.
				break;
			case Miss:
				digitalWrite(columnConnections[column][0], LOW); //Red Off.
				digitalWrite(columnConnections[column][1], LOW); //Green Off.
				digitalWrite(columnConnections[column][2], HIGH); //Blue On.
				break;
			case Occupied:
				digitalWrite(columnConnections[column][0], LOW); //Red Off.
				digitalWrite(columnConnections[column][1], HIGH); //Green On.
				digitalWrite(columnConnections[column][2], LOW); //Blue Off.
				break;
			case Empty:
				digitalWrite(columnConnections[column][0], LOW); //Red Off.
				digitalWrite(columnConnections[column][1], LOW); //Green Off.
				digitalWrite(columnConnections[column][2], LOW); //Blue Off.
				break;
			}
		}
		delay(1);
		PORTA = B00000000;
		PORTB = B00000000;
		PORTC = B00000000;
		//PORTD untouched.
		//PORTE untouched.
		//PORTF untouched.
		PORTG = PORTG & B11111011;
		PORTH = PORTH & B10000111;
		//No PORTI.
		PORTJ = PORTJ & B11111110;
		//No PORTK.
		PORTL = PORTL & B11110000;

		digitalWrite(layerConnection, HIGH);
		digitalWrite(layerConnection, LOW);
	}
}