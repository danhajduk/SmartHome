/************************************************************************/
/*	Master_Unit.h - Main hub unit Header file							*/
/*	Created by Dan Hajduk on August 25, 2017     						*/
/*	Last Update on August 25 ,2017										*/
/*	All rights reserved (C)                                             */
/************************************************************************/

#ifndef MASTER_H_
#define MASTER_H_

#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <SPI.h>
#include "wifi.h"

#include <Ethernet.h>


// SmartHome Lib Includes
#include <config.h>

class MasterUnit
{
	private:
		int _masterID = 0 ; 
		const float _rev = 0.1;
		const String _last = "25/08/2017";
		//byte [4] _CMD;

		//const's

		// NRF24 init code
		RF24 radio{10,9};
		RF24Network network{radio};							// Init RF24 Network
		RF24Mesh mesh {radio, network};						// Init RF24 Mesh
		
		byte mac[6] = {
			0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
		};
		IPAddress ip{192, 168, 1, 177};
		EthernetServer srv {23};

		void _printData();
	
	public:
		MasterUnit();
		void init();
		bool writeMesh (const void* data, uint8_t msg_type, size_t size, char node);
		void update();
		void DHCP();
		bool readUnits();
		bool sendCMD(char nodeID, char cmd);
		bool checkDev(char nodeID);


		char setNew ();
		void setName();
		bool getIpCommand();
		void sendStat();

		

		// Variables
		bool _DEBUG;
		char _data[40];
		int data_type ;
		uint16_t _from;
		// Constants
		//headr_stat hdrType;
};
#endif