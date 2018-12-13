/*
*	Arduino BattleShip game.
*
*	Source file for communication with the other board using the bluetooth module.
*
*	By William Taylor https://github.com/WMTaylor3
*/

#ifndef _BLUETOOTHMODULE_h
#define _BLUETOOTHMODULE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "BattleShipCommonTypes.h"

class BluetoothModule
{
private:
	BluetoothModule();
	static BluetoothModule* instance;
public:
	~BluetoothModule();
	static BluetoothModule* getInstance();
	bool establishConnection(boardRole role);
};

#endif

