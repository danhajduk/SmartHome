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
		const float _rev = 0.1;
		const String _last = "09/04/2017";

		const int Tmax = 60, Tmin = 20;		// Temperature limits
		int TempBar, Time1 ;				//
		const int TMRx = 33, TMRy = 41;		//X,Y coordinates of the Timer on
		const int _backLightPin = 3;		// Back light on pin 3
		const int _lightON = 180;			// Light on level
		const int _lightOff = 255;			// light off level
		int Temp = 00;						// boiler temperature
		const int ON = 180, OFF= 255, Low = 220;

		bool _animation = false;  
		

		bool _DEBUG;
		int _pin ;
		char _nodeID ;

		void timerIsr();
		
	public:
		Device dev;
		bool changed ;
		tSet curentTime ;
		tSet boilerTime ;
		int temperature = 40;
		bool oneSecPassed = false;
		String msg,msg1;
		bool lightOn;

		Boiler (int pin ,float Rev , String Last );
		void init (char nodeID);
		void turnOn();
		void turnOff();
		void DrawSCR();
		void updateBoiler();
		void backLight (bool On );
};



#endif /* BOILER_H_ */