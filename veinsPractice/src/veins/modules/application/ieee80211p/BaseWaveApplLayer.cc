//
// Copyright (C) 2011 David Eckhoff <eckhoff@cs.fau.de>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//


#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
const simsignalwrap_t BaseWaveApplLayer::mobilityStateChangedSignal = simsignalwrap_t(MIXIM_SIGNAL_MOBILITY_CHANGE_NAME);
void BaseWaveApplLayer::initialize(int stage)
{
    //std::cout << "BaseWaveApplLayer::initialize" << endl;
	BaseApplLayer::initialize(stage);
	if (stage==0)
	{

//	    std::cout << "BaseWaveApplLayer::initialize, stage = 0" << endl; // for debug
		myMac = FindModule<WaveAppToMac1609_4Interface*>::findSubModule(getParentModule());
		assert(myMac); // if correct, go ahead.
		myId = getParentModule()->getIndex();
		headerLength = par("headerLength").longValue();
		double maxOffset = par("maxOffset").doubleValue();
		sendBeacons = par("sendBeacons").boolValue();
		beaconLengthBits = par("beaconLengthBits").longValue();
		beaconPriority = par("beaconPriority").longValue();
		sendData = par("sendData").boolValue();
		dataLengthBits = par("dataLengthBits").longValue();
		dataOnSch = par("dataOnSch").boolValue();
		dataPriority = par("dataPriority").longValue();
		sendBeaconEvt = new cMessage("beacon evt", SEND_BEACON_EVT);
		exampleMSG = new cMessage("Example MSG Scheduled");
		//simulate asynchronous channel access
		double offSet = dblrand() * (par("beaconInterval").doubleValue()/2);
		offSet = offSet + floor(offSet/0.050)*0.050;
		individualOffset = dblrand() * maxOffset;
		findHost()->subscribe(mobilityStateChangedSignal, this);
		scheduleAt(simTime() + 1, exampleMSG);
		if (sendBeacons)
		{
			scheduleAt(simTime() + offSet, sendBeaconEvt);
		}
	}
}
/*
WaveShortMessage*  BaseWaveApplLayer::prepareWSM(std::string name, int lengthBits, t_channel channel, int priority, int rcvId, int serial)
{
	WaveShortMessage* wsm =		new WaveShortMessage(name.c_str());
	wsm->addBitLength(headerLength);
	wsm->addBitLength(lengthBits);
	switch (channel)
	{
		case type_SCH: wsm->setChannelNumber(Channels::SCH1); break; //will be rewritten at Mac1609_4 to actual Service Channel. This is just so no controlInfo is needed
		case type_CCH: wsm->setChannelNumber(Channels::CCH); break;
	}
	wsm->setPsid(0);
	wsm->setPriority(priority);
	wsm->setWsmVersion(1);
	wsm->setTimestamp(simTime());
	wsm->setSenderAddress(myId);
	wsm->setRecipientAddress(rcvId);
	wsm->setSenderPos(curPosition);
	wsm->setSerial(serial);
	if (name == "beacon")
	{
		DBG << "Creating Beacon with Priority " << priority << " at Applayer at " << wsm->getTimestamp() << std::endl;
	}
	if (name == "data")
	{
		DBG << "Creating Data with Priority " << priority << " at Applayer at " << wsm->getTimestamp() << std::endl;
	}
	return wsm;
}
*/
kwon*  BaseWaveApplLayer::prepareKP(std::string name, int lengthBits, t_channel channel, int priority, int rcvId, int serial)
{
    //std::cout << "BaseWaveApplLayer::initialize" << endl;
    kwon* kpm = new kwon(name.c_str());
    kpm->addBitLength(headerLength);
    /*
     Changes packet length by the given value (bits). This is useful for modeling encapsulation/decapsulation. (See also encapsulate() and
     decapsulate().) The caller must take care that the result does not overflow (i.e. fits into an int64).
     The value may be negative (packet length may be decreased too).
     If the resulting length would be negative, the method throws a cRuntimeError.
     virtual void addBitLength(int64 delta);
     */
    kpm->addBitLength(lengthBits); // add header length, bit length.
    switch (channel)
    {
        // define in Consts_802_11p.h
        /*
        namespace Channels {
        enum ChannelNumber {
            CRIT_SOL = 172,
            SCH1 = 174,
            SCH2 = 176,
            CCH = 178,
            SCH3 = 180,
            SCH4 = 182,
            HPPS = 184
        };
        }
        enum t_channel {
            type_CCH=0,
            type_SCH,
        };
        */
        case type_SCH: kpm->setChannelNumber(Channels::SCH1); break; //will be rewritten at Mac1609_4 to actual Service Channel. This is just so no controlInfo is needed
        case type_CCH: kpm->setChannelNumber(Channels::CCH); break;
    }
    kpm->setPsid(0);
    kpm->setPriority(priority);
    kpm->setKwonVersion(1);
    kpm->setTimestamp(simTime());
    kpm->setSenderAddress(myId);
    kpm->setRecipientAddress(rcvId);
   // kpm->setSenderPos(curPosition);
    kpm->setSerial(serial);
    /*
    kwon::
        int kwonVersion_var;
        int channelNumber_var;
        int dataRate_var;
        int priority_var;
        int psid_var;
        opp_string psc_var;
        int kwonLength_var;
        opp_string kwonData_var;
        int senderAddress_var;
        int recipientAddress_var;
        int serial_var;
        simtime_t timestamp_var;

        virtual int getKwonVersion() const;
        virtual void setKwonVersion(int kwonVersion);
        virtual int getChannelNumber() const;
        virtual void setChannelNumber(int channelNumber);
        virtual int getDataRate() const;
        virtual void setDataRate(int dataRate);
        virtual int getPriority() const;
        virtual void setPriority(int priority);
        virtual int getPsid() const;
        virtual void setPsid(int psid);
        virtual const char * getPsc() const;
        virtual void setPsc(const char * psc);
        virtual int getKwonLength() const;
        virtual void setKwonLength(int kwonLength);
        virtual const char * getKwonData() const;
        virtual void setKwonData(const char * kwonData);
        virtual int getSenderAddress() const;
        virtual void setSenderAddress(int senderAddress);
        virtual int getRecipientAddress() const;
        virtual void setRecipientAddress(int recipientAddress);
        virtual int getSerial() const;
        virtual void setSerial(int serial);
        virtual simtime_t getTimestamp() const;
        virtual void setTimestamp(simtime_t timestamp);
    wsm::
        int wsmVersion_var;
        int securityType_var;
        int channelNumber_var;
        int dataRate_var;
        int priority_var;
        int psid_var;
        opp_string psc_var;
        int wsmLength_var;
        opp_string wsmData_var;
        int senderAddress_var;
        int recipientAddress_var;
        int serial_var;
        Coord senderPos_var;
        simtime_t timestamp_var;
    */
    if (name == "beacon")
    {
        //DBG << "Creating Beacon with Priority " << priority << " at Applayer at " << wsm->getTimestamp() << std::endl;
        DBG << "Creating Beacon with Priority " << priority << " at Applayer at " << kpm->getTimestamp() << std::endl;
        bubble("Creating Beacon");
    }
    if (name == "data")
    {
        //DBG << "Creating Data with Priority " << priority << " at Applayer at " << wsm->getTimestamp() << std::endl;
        DBG << "Creating Data with Priority " << priority << " at Applayer at " << kpm->getTimestamp() << std::endl;
        bubble("Creating Data");
    }
    //return wsm;
    return kpm;
}
kwon* BaseWaveApplLayer::examplepkt(){
    //std::cout << "BaseWaveApplLayer::examplepkt" << endl;
    kwon* kpm = new kwon("Kwon_Generated_Packet");
    kpm->setMyid(findHost()->getFullName());
    kpm->setChannelNumber(Channels::SCH1);
    kpm->setPriority(0);
    return kpm;
}
/*
void BaseWaveApplLayer::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj)
{
    Enter_Method_Silent();
    if (signalID == mobilityStateChangedSignal)
    {
        handlePositionUpdate(obj);
    }
}
*/
void BaseWaveApplLayer::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj)
{
    //std::cout << "BaseWaveApplLayer::receiveSignal" << endl;
	Enter_Method_Silent();
	if (signalID == mobilityStateChangedSignal)
	{
	    DBG << "BaseWaveApplLayer::receiveSignal::handlePositionUpdate is activated " << std::endl;
	    bubble("BaseWaveApplLayer::receiveSignal::handlePositionUpdate is activated");
		//handlePositionUpdate(obj);
	}
}
/*
void BaseWaveApplLayer::handlePositionUpdate(cObject* obj)
{
	ChannelMobilityPtrType const mobility = check_and_cast<ChannelMobilityPtrType>(obj);
	curPosition = mobility->getCurrentPosition();
}
*/
void BaseWaveApplLayer::handlePositionUpdate(cObject* obj)
{
    //std::cout << "BaseWaveApplLayer::handlePositionUpdate" << endl;
  //  ChannelMobilityPtrType const mobility = check_and_cast<ChannelMobilityPtrType>(obj);
   // curPosition = mobility->getCurrentPosition(); there is no curPosition in my packet.
}
/*
 void BaseWaveApplLayer::handleLowerMsg(cMessage* msg)
{
    WaveShortMessage* wsm = dynamic_cast<WaveShortMessage*>(msg);
    ASSERT(wsm);
    if (std::string(wsm->getName()) == "beacon")
    {
        onBeacon(wsm);
    }
    else if (std::string(wsm->getName()) == "data")
    {
        onData(wsm);
    }
    else
    {
        DBG << "unknown message (" << wsm->getName() << ")  received\n";
    }
    delete(msg);
}
 */
void BaseWaveApplLayer::handleLowerMsg(cMessage* msg)
{
    //std::cout << "BaseWaveApplLayer::handleLowerMsg" << endl;
	kwon* kpm = dynamic_cast<kwon*>(msg);
	ASSERT(kpm);
//	std::cout <<" Packet received : Appl, handlelowerMSG"<<endl;
//	std::cout<<kpm->getName() <<"  FN: "<<kpm->getFullName()<<endl;
	/*if (std::string(kpm->getName()) == "beacon")
	{
		onBeacon(kpm);
	}
	else if (std::string(kpm->getName()) == "data")
	{
		onData(kpm);
	}*/
	if (strcmp(kpm->getName(),"Kwon_Generated_Packet") == 0){
	   // std::cout <<" My Generated packet is properly received"<< endl;
	   // std::cout<<" Sender ID: "<<kpm->getMyid() << " RCR ID : "<<findHost()->getFullName()<<endl;
	}
	else
	{
		DBG << "unknown message (" << kpm->getName() << ")  received\n";
	}
	delete(kpm);
}
/*
void BaseWaveApplLayer::handleSelfMsg(cMessage* msg)
{
	switch (msg->getKind())
	{
		case SEND_BEACON_EVT:
		{
			sendWSM(prepareWSM("beacon", beaconLengthBits, type_CCH, beaconPriority, 0, -1));
			scheduleAt(simTime() + par("beaconInterval").doubleValue(), sendBeaconEvt);
			break;
		}
		default:
		{
			if (msg)
				DBG << "APP: Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
			break;
		}
	}
}
*/
void BaseWaveApplLayer::handleSelfMsg(cMessage* msg)
{
    //std::cout << "BaseWaveApplLayer::handleSelfMsg" << endl;
    /*bubble("BaseWaveApplLayer::handleSelfMsg is activated");
    switch (msg->getKind())
    {
        case SEND_BEACON_EVT:
        {
            sendKPM(prepareKP("beacon", beaconLengthBits, type_CCH, beaconPriority, 0, -1));
            scheduleAt(simTime() + par("beaconInterval").doubleValue(), sendBeaconEvt);
            break;
        }
        default:
        {
            if (msg)
                DBG << "APP: Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
            break;
        }
    }
*/
    if (msg == exampleMSG){
//        std::cout << "    Appl Handleselfmsg packet sent!"<<endl;
        sendDown(examplepkt());
        scheduleAt(simTime() + 10, exampleMSG);
    }
}
/*
void BaseWaveApplLayer::sendWSM(WaveShortMessage* wsm)
{
	sendDelayedDown(wsm,individualOffset);
}
*/
void BaseWaveApplLayer::sendKPM(kwon* kpm)
{
    //std::cout << "BaseWaveApplLayer::sendKPM" << endl;
    sendDelayedDown(kpm,individualOffset);
}
/*
void BaseWaveApplLayer::finish()
{
	if (sendBeaconEvt->isScheduled())
	{
		cancelAndDelete(sendBeaconEvt);
	}
	else
	{
		delete sendBeaconEvt;
	}
	findHost()->unsubscribe(mobilityStateChangedSignal, this);
}
*/
void BaseWaveApplLayer::finish()
{
    if (sendBeaconEvt->isScheduled())
    {
        cancelAndDelete(sendBeaconEvt);
    }
    else
    {
        delete sendBeaconEvt;
    }
    findHost()->unsubscribe(mobilityStateChangedSignal, this);
}
BaseWaveApplLayer::~BaseWaveApplLayer()
{

}
