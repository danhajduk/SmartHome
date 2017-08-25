/************************************************************************/
/*	MasterUnit.cpp - Library for setting up Main hub unit 				*/
/*	Created by Dan Hajduk on August 25, 2017     						*/
/*	Last Update on August 25 ,2017										*/
/*	All rights reserved (C)                                             */
/************************************************************************/

#include "MasterUnit.h"


MasterUnit::MasterUnit()
/***************************************************************************************
	Class MasterUnit
	void MasterUnit ()
	Main unit constructor
/***************************************************************************************/
{
	

}

void MasterUnit::init()
/***************************************************************************************
	Class MasterUnit
	void init ()
	Initialize the master unit
/***************************************************************************************/
{
	if (_DEBUG) Serial.print(F("Main Unit Device Ver. "));
	if (_DEBUG) Serial.println(_rev);

	mesh.setNodeID(_masterID); // Set the nodeID to master node
	if (_DEBUG) Serial.println(F("Connecting to the mesh..."));
	mesh.begin();
	if (_DEBUG) Serial.print(F("Connected to the mesh as node: "));
	if (_DEBUG) Serial.println(mesh.getNodeID());
	if (_DEBUG) Serial.print(F("at Address : "));
	if (_DEBUG) Serial.println(mesh.getAddress(mesh.getNodeID()));
	

	_printData();

	/***********************
	TBD : init Ethernet
	************************/

	if (_DEBUG) Serial.println(F("******** Init  finished *********"));
}

void MasterUnit::_printData()
/***************************************************************************************
	Class MasterUnit
	void _printData ()
	Print Assigned Addresses
/***************************************************************************************/
{
	if (_DEBUG)
		{
				Serial.println(F("********Assigned Addresses********"));
				if (!mesh.addrListTop) Serial.println("No Addresses");
				for(int i=0; i<mesh.addrListTop; i++){
					Serial.print("NodeID: ");
					Serial.print(mesh.addrList[i].nodeID);
					Serial.print(" RF24Network Address: 0");
					Serial.println(mesh.addrList[i].address,OCT);
				}
				Serial.println(F("**********************************"));
		}
}

void MasterUnit::update()
/***************************************************************************************
	Class MasterUnit
	void update ()
	Update mesh
/***************************************************************************************/
{
	mesh.update();
	
}

void MasterUnit::DHCP()
/***************************************************************************************
	Class MasterUnit
	void DHCP ()
	Update DHCP 
/***************************************************************************************/
{
	mesh.DHCP();
}

bool MasterUnit::readUnits()
/***************************************************************************************
	Class MasterUnit
	bool  readUnits()
	Read data available from child units and return true is data availble
/***************************************************************************************/
{
	if (network.available())
	{
		RF24NetworkHeader header;
		network.peek(header);
		network.read(header,&_data,sizeof(_data));

		headr_stat hdrType;
		hdrType = header.type;
		switch (hdrType)
		{
			case ping :
				if (_DEBUG) Serial.print(F("Got Ping form : "));
				if (_DEBUG) Serial.println(header.from_node);
				if (_DEBUG) Serial.print(F("Checking the node ... "));
				bool reg1;
				for (int i=0; i < mesh.addrListTop; i++)
				{
					if(mesh.addrList[i].address == header.from_node) reg1 = true ;
				}
				if (reg1)
				{
					if (_DEBUG) Serial.println(F("The Node is registered."));
				} 
				else
				{
					if (_DEBUG) Serial.println(F("The Node is NOT registered"));
					RF24NetworkHeader hdr(header.from_node,OCT);
					hdr.type = reconect;
					network.write(hdr,0xAA,1);
				}
				_from = header.from_node;
				data_type = ping;
			break;
			default:
				network.read(header,0,0);
				if (_DEBUG) Serial.println(header.toString());
			break;
			case reconect:
			break;
			case command:
			break;
			case stat:
			break;
			case batt:
			break;
		}

	_printData();

	}
}

bool MasterUnit::writeMesh (const void* data, uint8_t msg_type, size_t size, char node)
/***************************************************************************************
	Class MasterUnit
	bool writeMesh (const void* data, uint8_t msg_type, size_t size)
	Write to mesh
/***************************************************************************************/
{
	if (!mesh.write(node,data,msg_type,size) )
	{
		mesh.checkConnection();
		
	}
	else
	{
		if (_DEBUG) Serial.print("Send OK: ");
		
	}
	mesh.checkConnection();
	return true;
}

bool MasterUnit::sendCMD(char nodeID , char cmd)
/***************************************************************************************
	Class MasterUnit
	void sendCMD (char nodeID , char cmd)
	Send command to node
/***************************************************************************************/
{
	writeMesh(cmd,command,sizeof(char),nodeID);
}

bool MasterUnit::checkDev(char nodeID)
/***************************************************************************************
	Class MasterUnit
	bool checkDev (char nodeID)
	Check if the device is connected
/***************************************************************************************/
{
	writeMesh(00,ping,1,nodeID);
}