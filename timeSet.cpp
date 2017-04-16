/**************************************************************************************
	Boiler.cpp - Library for setting up Boiler device
	Created by Dan Hajduk on April 1, 2017
	All rights reserved (C)

	Last Modified April 1, 2017

/**************************************************************************************/
#include "Arduino.h"
#include "timeSet.h"

tSet::tSet()
{
	//_SS = 0;
	//_MM = 0;
	//_HH = 0;
}
/***************************************************************************************
	Class tSet
	void tick () 
	Advance one second
/***************************************************************************************/

void tSet::tick ()
{
	Serial.print("Tick : ");
	_MS ++;
	if (_MS == 10)
	{
		_SS ++;
		_MS = 0;
	}
	//Serial.print(_SS);
	if (_SS == 60 ) 
	{
		_SS = 00;
		_MM ++;
		if (_MM == 60)
		{
			_MM = 00;
			_HH ++;
			if (_HH ==24 ) _HH =00;
		}
	}
	//Serial.print(_SS);
}
/***************************************************************************************
	Class tSet
	String showTime () 
	Return string with time 
/***************************************************************************************/

String tSet::showTime()
{
	String tmp;
	if (_HH <10) tmp += "0";
	tmp += String(_HH);
	tmp +=":";
	if (_MM <10) tmp += "0";
	tmp += String(_MM);
	tmp +=":";
	if (_SS <10) tmp += "0";
	tmp += String(_SS);
	return (tmp);
}

/***************************************************************************************
	Class tSet
	void clearTime () 
	Set time to 00:00:00
/***************************************************************************************/
void tSet::clearTime()
{
	_SS = _MM = _HH = 0;
}

/***************************************************************************************
	Class tSet
	void timeCheck () 
	Compare time
/***************************************************************************************/
bool tSet::timeCheck(int HH,int MM)
{
	if (_HH == HH && _MM == MM) return true;
	return false;
}

/***************************************************************************************
	Class tSet
	void timeCheck () 
	Compare time
/***************************************************************************************/

void tSet::timeSet(int HH, int MM)
{
	if (HH >=0 && HH < 24) _HH = HH;
	if (MM >=0 && MM <60 ) _MM = MM;
}