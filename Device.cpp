/**************************************************************************************
	Device.cpp - Library for setting up smart home device
	Created by Dan Hajduk on April 1, 2017

	Last Modified April 29, 2017

/**************************************************************************************/

#include "Arduino.h"
#include "Device.h"


		

Device::Device()
{
	
}

void Device::setDevice(int pin )
{
	pinMode(pin, OUTPUT);
	_pin = pin;
	
}
void Device::turnOn()
{
	digitalWrite(_pin, _onLevel);
}

void Device::turnOff()
{
	digitalWrite(_pin, !_onLevel);
}

bool Device::getStat()
{
	return ( digitalRead(_pin) );
}

void Device::setOnLevel(bool onLevel)
{
	_onLevel = onLevel;
}
