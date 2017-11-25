cplusplus {{
#include "Coord.h"
}}

//added
class noncobject Coord;
//added

//
// Defines all fields of an 802.11 MAC frame
//
struct vrtStruct
{

	int nodeMacAdd;//Next carrier Mac address
	string nodeID;//We will use the fullname of the host as the destination ID
    Coord nodePosition; //Next Carrier position
    double nodeSpeed; //NextCarrier Speed
//    double Distance_Sender_Rec;
    double nodeEDD_Value; //Next Carrier EDD_Value
    simtime_t lastUpdateTime; //Next Carrier Last Update in my RT
    int NumHopsToDst = 0;
    simtime_t rtTTL = 0.3;
};
//packet vrtpkt
//{
//
//	string RSUDestID;//for multiple RSUs, we have different EDDs, resulting into different Routing Tables.
//    double senderEDD_value; //RT Sender EDD
//
////    int priority;
////    end of send routing table packet   
//
//	vrtStruct RT[];
//}
cplusplus{{
#include "map"
#include "vector"
typedef std::map<std::string, double> senderEDDs;
typedef std::map<std::string, std::vector<vrtStruct>> multRSUsRt;

}};
class noncobject senderEDDs;
class noncobject multRSUsRt;

packet multipleRSUsRTpkt{
     int priority;
    //    packet to be sent 
    string pktSourceID;
    int seqNumber = 0;
    string pktDestinationID;//The id of RSU destinned the packet
    int pktDestinationMac;//The Mac of RSU destinned the packet
    string pktActualsrcID;//the id of next carrier of packet
    int pktActualsrcMac;//the Mac of the next carrier of the packet 
    int pktActualdestMac;//Current Carrier Mac Address
    simtime_t pktGenerationTime;//The time the packet is generated
    simtime_t pktlastReceiveTime;//The time the current carrier received the packet
    simtime_t DestArrivalTime;//The time the packet reached the destination
    simtime_t pktTTL;//time to live of the packet
    
// end of packet to be sent 

    int channelNumber; //  Channel Number on which this packet was sent (Used in mac handle upperMessage)
//    for routing table
    int rtsenderMacAdd; //RT sender ID
    //here include send routing table in packet
    string rtsenderID;
    Coord rtsenderPosition; //RT Sender Position
    double rtsenderSpeed; //RT Sender Speed
    simtime_t rtsendingTime; //RT Sending time stamp
    senderEDDs rtmyEDDs;
    multRSUsRt rtrouting_table;
//    end for routing table
	string myid;
}