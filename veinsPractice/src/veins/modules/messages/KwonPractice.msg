//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

//cplusplus 
//{{
// #include "veins/base/utils/Coord.h"
//}}
//class noncobject Coord;
packet kwon 
{
	//Version of the kwon message
	int kwonVersion = 0;
	//Determine which security mechanism was used
	//int securityType = 0;
	//Channel Number on which this packet was sent
	int channelNumber;
	//Data rate with which this packet was sent
	int dataRate = 1;
	//Power Level with which this packet was sent
	int priority = 3;
	//Unique number to identify the service
	int psid = 0;
	//Provider Service Context
	string psc = "Service with some Data";
	//Length of kwon Message
	int kwonLength;
	//Data of Wave Short Message
	string kwonData = "KWON_DATA";
	string myid;
	int senderAddress = 0;
	int recipientAddress = -1;
	int serial = 0;
	simtime_t pktTTL;
	//Coord senderPos;
	simtime_t timestamp = 0;
}