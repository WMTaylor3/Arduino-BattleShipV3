/*
*	Arduino BattleShip game.
*
*	Source file for interfacing with the LED Grid.
*	This one is tailored to the upper grid and thus ommits ship placement logic.
*
*	By William Taylor https://github.com/WMTaylor3
*/


#include <BattleShipCommonTypes.h>

gridReferenceState grid[10][10];	//Representation of the board to be drawn on the grid.
uint8_t columnConnections[10][2];	//The addresses of the pins of each of the columns (10) and their colors (3).
uint8_t layerConnection;			//The address of the pin which triggers the decade counter.
uint8_t layerReset;					//The address of the pin which resets the decade counter to 0.

void setup()
{
	emptyGrid();
	initializeSoftConnections();
	initializeHardConnections();
	Serial1.begin(115200);
}

void loop()
{
	//checkforNewData();
	//refreshGrid();
	testGridRB();
}

void emptyGrid()
{
	for (uint8_t i = 0; i < 10; i++)
	{
		for (uint8_t j = 0; j < 10; j++)
		{
			grid[i][j] = Empty;
		}
	}
}

//Assigns the correct number to each of the columnConnections array members and layerConnection.
void initializeSoftConnections()
{
	columnConnections[0][0] = 24; //C1R
	columnConnections[0][1] = 22; //C1B

	columnConnections[1][0] = 35; //C2R
	columnConnections[1][1] = 37; //C2B

	columnConnections[2][0] = 51; //C3R
	columnConnections[2][1] = 53; //C3B

	columnConnections[3][0] = 27; //C4R
	columnConnections[3][1] = 25; //C4B

	columnConnections[4][0] = 47; //C5R
	columnConnections[4][1] = 49; //C5B

	columnConnections[5][0] = 8; //C6R
	columnConnections[5][1] = 6; //C6B

	columnConnections[6][0] = 39; //C7R
	columnConnections[6][1] = 28; //C7B

	columnConnections[7][0] = 32; //C8R
	columnConnections[7][1] = 34; //C8B

	columnConnections[8][0] = 11; //C9R
	columnConnections[8][1] = 50; //C9B

	columnConnections[9][0] = 9; //C10R
	columnConnections[9][1] = 15; //C10B

	layerConnection = 2;
	layerReset = 3;
}

//Configures the Arduino I/O according to columnConnections and layerConnection.
void initializeHardConnections()
{
	for (uint8_t column = 0; column < 10; column++)
	{
		for (uint8_t color = 0; color < 2; color++)
		{
			uint8_t pin = columnConnections[column][color];
			pinMode(pin, OUTPUT);
		}
	}

	pinMode(layerConnection, OUTPUT);
	pinMode(layerReset, OUTPUT);
}

void refreshGrid()
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
				digitalWrite(columnConnections[column][1], LOW); //Blue Off.
				break;
			case HitAndSunk:
				digitalWrite(columnConnections[column][0], HIGH); //Red On.
				digitalWrite(columnConnections[column][1], LOW); //Blue Off.
				break;
			case Miss:
				digitalWrite(columnConnections[column][0], LOW); //Red Off.
				digitalWrite(columnConnections[column][1], HIGH); //Blue On.
				break;
			case Empty:
				digitalWrite(columnConnections[column][0], LOW); //Red Off.
				digitalWrite(columnConnections[column][1], LOW); //Blue Off.
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

void checkforNewData()
{
	uint8_t message[3];

	//If the whole message has been recieved.
	if (Serial1.available() >= 3)
	{
		//Read in the data to seperate chars.
		for (uint8_t i = 0; i < 3; i++)
		{
			message[i] = Serial1.read();
		}

		updateGrid(message);

		//Clear the buffer.
		while (Serial1.available() > 0)
		{
			char junk = Serial1.read();
		}

		//Send confirmation to main Arduino.
		Serial1.write('-');
	}
}

void updateGrid(uint8_t message[])
{
	switch (message[2])
	{
	case(Hit):
		grid[message[0]][message[1]] = Hit;
		break;
	case(HitAndSunk):
		grid[message[0]][message[1]] = HitAndSunk;
		break;
	case(Miss):
		grid[message[0]][message[1]] = Miss;
		break;
	case(Empty):
		grid[message[0]][message[1]] = Empty;
		break;
	}
}

void testGridRB()
{
	unsigned long time;
	time = millis();
	testGridR();
	while (millis() <= (time + 1000))
	{
		refreshGrid();
	}

	time = millis();
	testGridB();
	while (millis() <= (time + 1000))
	{
		refreshGrid();
	}
}

void testGridR()
{
	for (uint8_t i = 0; i < 10; i++)
	{
		for (uint8_t j = 0; j < 10; j++)
		{
			grid[i][j] = Hit;
		}
	}
}

void testGridB()
{
	for (uint8_t i = 0; i < 10; i++)
	{
		for (uint8_t j = 0; j < 10; j++)
		{
			grid[i][j] = Miss;
		}
	}
}