/**************************************************************************************
	Device.h - Library for setting up smart home device
	Created by Dan Hajduk on April 1, 2017
	
/**************************************************************************************/
#ifndef Device_h
#define Device_h

#include "Arduino.h"


class Device 
{
	public:
		Device ();
		void setDevice(int pin );
		void turnOn ();
		void turnOff ();
		bool getStat ();
		
	private:
		int _pin;
};

#endif

		
