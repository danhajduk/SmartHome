/**************************************************************************************
	Boiler.cpp - Library for setting up Boiler device
	Created by Dan Hajduk on April 1, 2017
	

	Last Modified April 29, 2017

/**************************************************************************************/


#include "Boiler.h"

extern uint8_t SmallFont[];			// Small font pointer
extern unsigned char TinyFont[];	// Tine font pointer

Boiler::Boiler(int pin ,float Rev , String Last )
{
	_pin = pin;
	RF24 radio1 (7,8);
	dev.setDevice(_pin);					// Set Device Output (on/off)
	turnOff();
}

/***************************************************************************************
	Class Boiler
	void init () 
	Initialize boiler
/***************************************************************************************/
void Boiler::init( char nodeID, bool onLevel)
{
	_nodeID = nodeID;

	// Connect to the mesh and set Node ID
	mesh.setNodeID(_nodeID);
	if (_DEBUG) Serial.println(F("Connecting to the mesh..."));
	mesh.begin();
	dev.setOnLevel(onLevel);

	// init LCD and print init data on LCD
	myGLCD.InitLCD(60);							// Init LCD 55 contrast
	myGLCD.setFont(SmallFont);					// Set small font
	myGLCD.clrScr();							// clr screen
	myGLCD.print("Boiler Device",0,0);			//Print init Data on screen
	myGLCD.print("Rev :" , 0 , 10);
	myGLCD.printNumF(_rev,1 ,35,10,'.',1,'0');
	myGLCD.print(_last,0,40);
	myGLCD.update();							// Update display


	turnOff();
}

/***************************************************************************************
	Class Boiler
	void DrawSCR () 
	Fills LCD screen with data
/***************************************************************************************/

void Boiler:: DrawSCR()
{
	myGLCD.clrScr();					// clear screen
	if (Temp < Tmin) Temp = Tmin;
	TempBar =( (Temp - Tmin)*38) / (Tmax-Tmin) ;
	
	// draw frame
	myGLCD.drawRect(0, 0, 83, 47);
	myGLCD.drawRect(0, 0, 16, 37);
	myGLCD.drawRect(0, 0, 16, 47);
	
	// draw temperature bar
	for (int i = 0; i < TempBar ; i++)
	{
		myGLCD.drawLine(0, 37 - i,16,37 - i);
	}
	
	// write current Temperature in boiler
	myGLCD.setFont(SmallFont);
	myGLCD.printNumI(Temp, 2, 39);
	
	// Show current time
	myGLCD.setFont(SmallFont);
	myGLCD.print(curentTime.showTime(),20,5);
	
	// Show boiler on time (if on)
	if (boilerTime.isSet)
	{
		myGLCD.setFont(TinyFont);
		myGLCD.print(boilerTime.showTime(),TMRx,TMRy);
	}

	// update display
	//backLight(true);
	if (boilerTime.isSet)
	{
		//myGLCD.setFont(SmallFont);
		//if (_animation) myGLCD.print("((((((",30,25); else myGLCD.print("))))))",30,25);
		//if (_animation) myGLCD.print("))))))",30,30); else myGLCD.print("((((((",30,30);
		//myGLCD.drawRect(30, 35, 65, 37);
		_animation = !_animation;
		int x1 = 38;
		int y1 = 15;
		myGLCD.drawRect(x1,y1,x1+20,y1+22);
		for (int i = 0; i < 22 ; i++)
		{
			myGLCD.drawLine(x1, y1+22- i,x1+20,y1+22 - i);
		}
		if (_animation) myGLCD.clrPixel(x1+5,y1+18) ;   else myGLCD.clrPixel(x1+10,y1+18) ;
		if (_animation) myGLCD.clrCircle(x1+5,y1+18,1); else myGLCD.clrCircle(x1+10,y1+18,1);
		if (_animation) myGLCD.clrPixel(x1+10,y1+14) ;   else myGLCD.clrPixel(x1+5,y1+14) ;
		if (_animation) myGLCD.clrCircle(x1+10,y1+14,1); else myGLCD.clrCircle(x1+5,y1+14,1);
		if (_animation) myGLCD.clrCircle(x1+10,y1+14,2); else myGLCD.clrCircle(x1+5,y1+14,2);
		if (_animation) myGLCD.clrPixel(x1+5,y1+9) ;   else myGLCD.clrPixel(x1+10,y1+9) ;
		if (_animation) myGLCD.clrCircle(x1+5,y1+9,1); else myGLCD.clrCircle(x1+10,y1+9,1);
		if (_animation) myGLCD.clrCircle(x1+5,y1+9,2); else myGLCD.clrCircle(x1+10,y1+9,2);
		if (_animation) myGLCD.clrCircle(x1+5,y1+9,3); else myGLCD.clrCircle(x1+10,y1+9,3);
	}
	else
	{
		myGLCD.setFont(TinyFont);
		myGLCD.print(msg,20,20);
		myGLCD.print(msg1,20,28);
	}
	//backLight(true);
	//myGLCD.drawBitmap(69,3, Wifi , 13,10);
	myGLCD.drawLine(70,13,80,3);
	myGLCD.drawLine(71,13,81,3);
	//myGLCD.drawCircle(75,7 ,6);
	myGLCD.update();
	changed = false;
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
/***************************************************************************************
	Class Boiler
	void updateBoiler () 
	Update Boiler status
/***************************************************************************************/

void Boiler::updateBoiler()
{
DrawSCR();
mesh.update();

}

/***************************************************************************************
	Class Boiler
	void backLight (bool On ) 
	Turns the back light on or off
/***************************************************************************************/

void Boiler::backLight (bool On )
{
	if (On)   analogWrite(_backLightPin,ON);
	else   analogWrite(_backLightPin,OFF);
	lightOn = On;
}

/***************************************************************************************
	Class Boiler
	bool writeMesh (const void* data, uint8_t msg_type, size_t size)
	Turns the back light on or off
/***************************************************************************************/

bool Boiler::writeMesh (const void* data, uint8_t msg_type, size_t size)
{
	if (!mesh.write( data,msg_type,size) )
	{
		// If a write fails, check connectivity to the mesh network
		if ( ! mesh.checkConnection() )
		{
			//refresh the network address
			if (_DEBUG)  Serial.println("Renewing Address");
			mesh.renewAddress();
		}
		else
		{
			if (_DEBUG) Serial.println("Send fail, Test OK");
			return false;
		}
	}
	else 
	{
		if (_DEBUG) Serial.print("Send OK: ");
		
	}
	mesh.checkConnection();
	return true;
}


