/**************************************************************************************
	Boiler.cpp - Library for setting up Boiler device
	Created by Dan Hajduk on April 1, 2017
	All rights reserved (C)

	Last Modified April 1, 2017

/**************************************************************************************/

#include "Boiler.h"

Boiler::Boiler(int pin)
{
	_pin = pin;
	dev.setDevice(_pin);					// Set Device Output (on/off)
	turnOff();
}

/***************************************************************************************
	Class Boiler
	void turnOn () 
	Turn On Boiler
/***************************************************************************************/

void Boiler::turnOn()
{
	dev.turnOn();
	boilerTime.isSet = true;
	boilerTime.clearTime();
}

/***************************************************************************************
	Class Boiler
	void turnOff () 
	Turn Off Boiler
/***************************************************************************************/

void Boiler::turnOff()
{
	dev.turnOff();
	boilerTime.isSet = false;
	boilerTime.clearTime();
}





