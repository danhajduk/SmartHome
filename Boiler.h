/**************************************************************************************
	Boiler.h - Library for setting up Boiler device
	Created by Dan Hajduk on April 1, 2017
	

	Last Modified April 29, 2017

/**************************************************************************************/



#ifndef BOILER_H_
#define BOILER_H_

#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
#include <LCD5110_Graph.h>
#include "wifi.h"

// SmartHome Lib Includes
#include "Device.h"
#include "TimerOne.h"
#include "timeSet.h"
#include "Arduino.h"
#include "config.h"

class Boiler 
{
	
	private:

		const float _rev = 0.1;
		const String _last = "09/04/2017";
		// NRF24 init code
		RF24 radio{7,8};
		RF24Network network{radio};							// Init RF24 Network
		RF24Mesh mesh {radio, network};						// Init RF24 Mesh
		// LCD init code
		const int _SCK = 7;
		const int _MOSI = 6;
		const int _DC = 5;
		const int _RST = 2;
		const int _CS = 4;
		LCD5110 myGLCD {_SCK, _MOSI , _DC, _RST, _CS};		// Init LCD
		

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
		void init (char nodeID , bool onLevel);
		void turnOn();
		void turnOff();
		void DrawSCR();
		void updateBoiler();
		void backLight (bool On );
		bool writeMesh (const void* data, uint8_t msg_type, size_t size);
		void doPing();
};



#endif /* BOILER_H_ */