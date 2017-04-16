/**************************************************************************************
	Boiler.h - Library for setting up Boiler device
	Created by Dan Hajduk on April 1, 2017
	All rights reserved (C)

	Last Modified April 1, 2017

/**************************************************************************************/



#ifndef BOILER_H_
#define BOILER_H_

#include "Device.h"
#include "TimerOne.h"
#include "timeSet.h"



class Boiler 
{
	private:
		

		int _pin ;
		
		
		// Setup LCD with assigned pins


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