cplusplus {{
#include "Coord.h"
}}

class noncobject Coord;

packet pkt_Send
{
//    int sourceMac;//Mac address of the source Module (Node or RSU)
	string sourceID;
	int seqNumber = 0;
	string destinationID;//The id of RSU destinned the packet
	int destinationMac;//The Mac of RSU destinned the packet
	string actualsrcID;//the id of next carrier of packet
	int actualsrcMac;//the Mac of the next carrier of the packet	
    int actualdestMac;//Current Carrier Mac Address
    simtime_t pktGenerationTime;//The time the packet is generated
    simtime_t lastReceiveTime;//The time the current carrier received the packet
    simtime_t DestArrivalTime;//The time the packet reached the destination
    simtime_t ttl;//time to live of the packet
    int priority = 1;
}
