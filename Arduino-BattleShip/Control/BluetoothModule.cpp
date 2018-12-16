/*
*	Arduino BattleShip game.
*
*	Source file for communication with the other board using the bluetooth module.
*
*	By William Taylor https://github.com/WMTaylor3
*/

#include "BluetoothModule.h"

BluetoothModule* BluetoothModule::instance = 0;

//Constructor
BluetoothModule::BluetoothModule()
{
	display = InchDisplay::getInstance();
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
bool BluetoothModule::transmitStrike(singleLocation strikePosition)
{
	uint8_t message[2];
	uint8_t transmitAttempt = 0;
	unsigned long timeOfLastAttempt = millis();

	display->drawSending();

	//Make ten attempts to transmit.
	while (transmitAttempt <= 10)
	{
		if (millis() >= timeOfLastAttempt + 2000)	//Every two seconds, perform a transmit attempt.
		{
			transmitAttempt++;
			timeOfLastAttempt = millis();

			//Construct message.
			message[0] = strikePosition.x;
			message[1] = strikePosition.y;

			//Transmit to the other board.
			Serial3.write(message[0]);
			Serial3.write(message[1]);

			//Attempt to retrieve and validate confirmation message.
			for (uint8_t readAttempt = 0; readAttempt < 10; readAttempt++)
			{
				if (Serial3.read() == '-')	//If the other board has responded with BlueTooth Confirmed.
				{
					//Clear the buffer.
					while (Serial3.available() > 0)
					{
						char junk = Serial3.read();
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
}

//Method for reading an incoming strike from the other board.
singleLocation BluetoothModule::receiveStrike()
{
	uint8_t message[2];
	unsigned long timeOfLastCheck = millis();

	while (true)
	{
		if (millis() >= timeOfLastCheck + 1000)	//Every second, check for an incoming strike.
		{
			timeOfLastCheck = millis();

			//If the whole message has been recieved.
			if (Serial3.available() >= 2)
			{
				display->drawReceiving();
				//Read in the data to seperate chars.
				for (uint8_t i = 0; i < 2; i++)
				{
					message[i] = Serial3.read();
				}

				//Clear the buffer.
				while (Serial3.available() > 0)
				{
					char junk = Serial3.read();
				}

				//Send confirmation to Master Arduino.
				Serial3.write('-');

				//Construct strikePosition out of message and return it to the caller.
				singleLocation strikePosition;
				strikePosition.x = message[0];
				strikePosition.y = message[1];
				return strikePosition;
			}
		}
	}
}

//Method for transmitting a response to the strike.
bool BluetoothModule::transmitResponse(gridReferenceState response)
{
	uint8_t transmitAttempt = 0;
	unsigned long timeOfLastAttempt = millis();

	//Make ten attempts to transmit.
	while (transmitAttempt <= 10)
	{
		if (millis() >= timeOfLastAttempt + 2000)	//Every two seconds, perform a transmit attempt.
		{
			transmitAttempt++;
			timeOfLastAttempt = millis();

			//Transmit to the other board.
			Serial3.write(response);

			//Attempt to retrieve and validate confirmation message.
			for (uint8_t readAttempt = 0; readAttempt < 10; readAttempt++)
			{
				if (Serial3.read() == '-')	//If the other board has responded with BlueTooth Confirmed.
				{
					//Clear the buffer.
					while (Serial3.available() > 0)
					{
						char junk = Serial3.read();
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
}

//Method for reading an incomming strike response.
gridReferenceState BluetoothModule::receiveResponse()
{
	uint8_t message;
	uint8_t receiveAttempt = 0;
	unsigned long timeOfLastCheck = millis();

	while (receiveAttempt <= 30)
	{
		if (millis() >= timeOfLastCheck + 1000)	//Every second, check for an incoming strike response.
		{
			receiveAttempt++;
			timeOfLastCheck = millis();

			//If the whole message has been recieved.
			if (Serial3.available() != 0)
			{
				message = Serial3.read();

				//Clear the buffer.
				while (Serial3.available() > 0)
				{
					char junk = Serial3.read();
				}

				//Send confirmation to Master Arduino.
				Serial3.write('-');

				//Construct response out of message and return it to the caller.
				switch (message)
				{
				case(Hit):
					return Hit;
					break;
				case(HitAndSunk):
					return HitAndSunk;
					break;
				case(Miss):
					return Miss;
					break;
				case(Occupied):
					return Occupied;
					break;
				case(Empty):
					return Empty;
					break;
				}
			}
		}
	}
}