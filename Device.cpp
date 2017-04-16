/**************************************************************************************
	Device.cpp - Library for setting up smart home device
	Created by Dan Hajduk on April 1, 2017
	All rights reserved (C)
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
	digitalWrite(_pin, LOW);
}

void Device::turnOff()
{
	digitalWrite(_pin, HIGH);
}

bool Device::getStat()
{
	return ( digitalRead(_pin) );
}

