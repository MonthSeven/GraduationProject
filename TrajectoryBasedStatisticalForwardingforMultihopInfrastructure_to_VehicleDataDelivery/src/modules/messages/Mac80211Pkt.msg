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
#include "MacPkt_m.h"
#include "Coord.h"
}}


class MacPkt;
class noncobject Coord;

//
// Defines all fields of an 802.11 MAC frame
//
packet Mac80211Pkt extends MacPkt
{
    int sendeMac;
    int receiverMac;
    int sequenceNumber;
  	int sendingTime;
  	
    int sequenceControl;
    bool retry;
    simtime_t duration; 	//the expected remaining duration the current transaction
}
