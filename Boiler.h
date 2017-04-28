/**************************************************************************************
	Boiler.h - Library for setting up Boiler device
	Created by Dan Hajduk on April 1, 2017
	

	Last Modified April 1, 2017

/**************************************************************************************/



#ifndef BOILER_H_
#define BOILER_H_

// include RF24 libs
#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>

// SmartHome Lib Includes
#include "Device.h"
#include "TimerOne.h"
#include "timeSet.h"



class Boiler 
{
	
	private:

		RF24 radio(7, 8);
		RF24Network network(radio);
		RF24Mesh mesh(radio, network);

		int _pin ;
		
		void timerIsr();
		void DrawSCR();
	public:
		Device dev;
		bool changed ;
		tSet curentTime ;
		tSet boilerTime ;
		int temperature = 40;

		Boiler (int pin );
		void turnOn();
		void turnOff();
};



#endif /* BOILER_H_ */