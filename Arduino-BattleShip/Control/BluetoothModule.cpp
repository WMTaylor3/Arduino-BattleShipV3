/*
*	Arduino BattleShip game.
*
*	Source file for communication with the other board using the bluetooth module.
*
*	By William Taylor https://github.com/WMTaylor3
*/

#include "BluetoothModule.h"
#include "BattleShipCommonTypes.h"

BluetoothModule* BluetoothModule::instance = 0;

//Constructor
BluetoothModule::BluetoothModule()
{

}

//Destructor
BluetoothModule::~BluetoothModule()
{

}

//In accordance to singleton pattern this method is used instead of a public constructor to ensure only one instance exists.
BluetoothModule* BluetoothModule::getInstance()
{
	if (instance == 0)
	{
		instance = new BluetoothModule();
	}

	return instance;
}

//Method for determining whether a connection has been made to the other board.
bool BluetoothModule::establishConnection(boardRole role)
{
	uint8_t connectionAttempt = 0;
	unsigned long timeOfLastCheck = millis();

	switch (role)
	{
		case(Master):
			//Procedure for Master board.
			while (connectionAttempt <= 10)
			{
				if (millis() >= timeOfLastCheck + 3000)	//Every three seconds, send a BlueTooth Query.
				{
					connectionAttempt++;
					timeOfLastCheck = millis();

					//Send a new query.
					Serial3.write('Q');

					//Attempt to retrieve and validate confirmation message.
					for (uint8_t readAttempt = 0; readAttempt < 10; readAttempt++)
					{
						if (Serial3.read() == 'C')	//If the other board has responded with BlueTooth Confirmed.
						{
							//Clear the buffer.
							while (Serial1.available() > 0)
							{
								char junk = Serial1.read();
							}

							return true;
						}
						else
						{
							delay(200);
						}
					}
				}
			}
			break;

		case(Slave):
			//Procedure for Slave board.
			while (connectionAttempt <= 30)
			{
				if (millis() >= timeOfLastCheck + 1000)	//Every second, check for a BlueTooth Query.
				{
					connectionAttempt++;
					timeOfLastCheck = millis();

					//If there is a message waiting.
					if (Serial3.available() != 0)
					{
						//Ensure the data is a bluetooth query.
						if (Serial3.read() == 'Q')
						{
							//Clear the buffer.
							while (Serial1.available() > 0)
							{
								char junk = Serial1.read();
							}

							//Send confirmation to Master Arduino.
							Serial3.write('C');

							return true;
						}
					}
				}
			}
			break;
	}

	return false;
}

//Method for transmitting a strike position to the other board.
void BluetoothModule::transmitStrike(singleLocation strikePosition)
{

}

//Method for reading an incoming strike from the other board.
strikePosition BluetoothModule::receiveStrike()
{

}

//Method for transmitting a response to the strike.
void BluetoothModule::transmitResponse(gridReferenceState response)
{

}

//Method for reading an incomming strike response.
gridReferenceState BluetoothModule::receiveResponse()
{

}