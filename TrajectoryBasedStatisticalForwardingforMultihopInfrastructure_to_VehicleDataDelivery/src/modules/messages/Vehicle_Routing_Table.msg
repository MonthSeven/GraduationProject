
//**************************************************************************
// * file:        Mac80211Pkt.msg
// *
// * author:      Marc L�bbers
// * copyright:   (c) by 'the Glimmer Twins'
// *              Telecommunication Networks Group
// *              TU-Berlin
// * email:       loebbers@tkn.tu-berlin.de
// **************************************************************************
// * part of:     framework implementation developed by tkn
// *************************************************************************/
cplusplus {{
#include "Coord.h"
//#include "string.h"
}}

//added
class noncobject Coord;
//added

//
// Defines all fields of an 802.11 MAC frame
//
struct Veh_Routing_Table
{
//	int nodeID;//Destination ID 
	int nodeMacAdd;//Next carrier Mac address
	string nodestrid;//We will use the fullname of the host
    Coord vehPosition; //Next Carrier position
    double vehSpeed; //NextCarrier Speed
//    double Distance_Sender_Rec;
    double EDD_Value; //Next Carrier EDD_Value
    simtime_t lastUpdateTime; //Next Carrier Last Update in my RT
    simtime_t rtTTL = 10;
};
packet VRT
{
//here include send routing table in packet
//	int senderID; //RT sender ID
//	char SenderHostID[]; //Full name of the sending host
	string extID;
	int senderMacAdd; //RT sender ID
	string sendernodeStrId;
    Coord senderPosition; //RT Sender Position
    double senderSpeed; //RT Sender Speed
    double senderEDD_value; //RT Sender EDD
    simtime_t sendingTime; //RT Sending time stamp
    int priority = 3;
    //end of send routing table packet
    
	Veh_Routing_Table RT[];
}