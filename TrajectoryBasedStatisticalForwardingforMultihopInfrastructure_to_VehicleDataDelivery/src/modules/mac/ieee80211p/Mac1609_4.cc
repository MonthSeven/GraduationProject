//
// Copyright (C) 2012 David Eckhoff <eckhoff@cs.fau.de>
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

#include "Mac1609_4.h"
#include <iterator>
#define DBG_MAC EV
Define_Module(Mac1609_4);
fstream macpktfile, edcaQueuecontentfile;
static int PktDropedDueToRetransmission_case1 = 0;
static int PktDropedDueToRetransmission_case2 = 0;
//static bool isRT = true;
void Mac1609_4::initialize(int stage)
{
    //std::cout << "Mac1609_4::initialize" << endl;
    BaseMacLayer::initialize(stage);
    if (stage == 0)
    {
        //  traffic statistics
        phy11p = FindModule<Mac80211pToPhy11pInterface*>::findSubModule( getParentModule());
        assert(phy11p);

        //this is required to circumvent double precision issues with constants from CONST80211p.h
        assert(simTime().getScaleExp() == -12);
        // original
        //---------------------------------------------------------------------
        //sigChannelBusy = registerSignal("sigChannelBusy"); // Mac1609_4::simsignal_t sigChannelBusy
        //sigCollision = registerSignal("sigCollision"); // Mac1609_4::simsignal_t sigCollision
        //---------------------------------------------------------------------
        txPower = par("txPower").doubleValue();
        bitrate = par("bitrate");
        n_dbps = 0;
        setParametersForBitrate(bitrate);

        //mac-adresses
        myMacAddress = intuniform(0, 0xFFFFFFFE);
        myId = getParentModule()->getParentModule()->getFullPath();
        //create frequency mappings
        frequency.insert(std::pair<int, double>(Channels::CRIT_SOL, 5.86e9));
        frequency.insert(std::pair<int, double>(Channels::SCH1, 5.87e9));
        frequency.insert(std::pair<int, double>(Channels::SCH2, 5.88e9));
        frequency.insert(std::pair<int, double>(Channels::CCH, 5.89e9));
        frequency.insert(std::pair<int, double>(Channels::SCH3, 5.90e9));
        frequency.insert(std::pair<int, double>(Channels::SCH4, 5.91e9));
        frequency.insert(std::pair<int, double>(Channels::HPPS, 5.92e9));

        //create two edca systems

        myEDCA[type_CCH] = new EDCA(type_CCH, par("queueSize").longValue());
        myEDCA[type_CCH]->myId = myId;
        myEDCA[type_CCH]->myId.append(" CCH");

        myEDCA[type_CCH]->createQueue(2, (((CWMIN_11P + 1) / 4) - 1), (((CWMIN_11P + 1) / 2) - 1), AC_VO);
        myEDCA[type_CCH]->createQueue(3, (((CWMIN_11P + 1) / 2) - 1), CWMIN_11P, AC_VI);
        myEDCA[type_CCH]->createQueue(6, CWMIN_11P, CWMAX_11P, AC_BE);
        myEDCA[type_CCH]->createQueue(9, CWMIN_11P, CWMAX_11P, AC_BK);

        myEDCA[type_SCH] = new EDCA(type_SCH, par("queueSize").longValue());
        myEDCA[type_SCH]->myId = myId;
        myEDCA[type_SCH]->myId.append(" SCH");
        myEDCA[type_SCH]->createQueue(2, (((CWMIN_11P + 1) / 4) - 1), (((CWMIN_11P + 1) / 2) - 1), AC_VO);
        myEDCA[type_SCH]->createQueue(3, (((CWMIN_11P + 1) / 2) - 1), CWMIN_11P, AC_VI);
        myEDCA[type_SCH]->createQueue(6, CWMIN_11P, CWMAX_11P, AC_BE);
        myEDCA[type_SCH]->createQueue(9, CWMIN_11P, CWMAX_11P, AC_BK);

        useSCH = par("useServiceChannel").boolValue();
        if (useSCH)
        {
            //set the initial service channel
            switch (par("serviceChannel").longValue())
            {
            case 1: mySCH = Channels::SCH1; break;
            case 2: mySCH = Channels::SCH2; break;
            case 3: mySCH = Channels::SCH3; break;
            case 4: mySCH = Channels::SCH4; break;
            default: opp_error("Service Channel must be between 1 and 4"); break;
            }
        }
        //Retransmission
        ackEvent = new cMessage ("acknowledgement");
        isACKSent = false;
        AckSendingDuration = 0;
        Mac80211Pkt* mac = new Mac80211Pkt("Mac Ack");
        AckSendingDuration = RADIODELAY_11P + getFrameDuration(mac->getBitLength()) + SIFS_11P;
        retransmissionnumbers = 0;
        Lstate = none;
        isACKSent = false;
        //Retransmission

        headerLength = par("headerLength");
        nextMacEvent = new cMessage("next Mac Event");
        if (useSCH)
        {
            // introduce a little asynchronization between radios, but no more than .3 milliseconds
            uint64_t currenTime = simTime().raw();
            uint64_t switchingTime = SWITCHING_INTERVAL_11P.raw();
            double timeToNextSwitch = (double) (switchingTime - (currenTime % switchingTime)) / simTime().getScale();
            if ((currenTime / switchingTime) % 2 == 0)
            {
                setActiveChannel(type_CCH);
            }
            else
            {
                setActiveChannel(type_SCH);
            }

            // channel switching active
            nextChannelSwitch = new cMessage("Channel Switch");
            simtime_t offset = dblrand() * par("syncOffset").doubleValue();
            scheduleAt(simTime() + offset + timeToNextSwitch, nextChannelSwitch);
        }
        else
        {
            // no channel switching
            nextChannelSwitch = 0;
            setActiveChannel(type_CCH);
        }

        nextCheckEvent = new cMessage("next Check Event");

        //stats
        statsReceivedPackets = 0;
        statsReceivedBroadcasts = 0;
        statsSentPackets = 0;
        statsTXRXLostPackets = 0;
        statsSNIRLostPackets = 0;
        statsDroppedPackets = 0;
        statsNumTooLittleTime = 0;
        statsNumInternalContention = 0;
        statsNumBackoff = 0;
        statsSlotsBackoff = 0;
        statsTotalBusyTime = 0;

        idleChannel = true;
        lastBusy = simTime();
        remove("/home/aime/Downloads/TBDVADD/examples/veins/VADDResults/pktinMac.txt");
        remove ("/home/aime/Downloads/TBDVADD/examples/veins/VADDResults/edcaqueueContents.txt");
    }
}

void Mac1609_4::handleSelfMsg(cMessage* msg)
{
    //std::cout << "Mac1609_4::handleSelfMsg" << endl;
    if (msg == nextChannelSwitch)
    {
        ASSERT(useSCH);
        scheduleAt(simTime() + SWITCHING_INTERVAL_11P, nextChannelSwitch);

        switch (activeChannel)
        {
        case type_CCH:
            DBG_MAC << "CCH --> SCH" << std::endl;
            channelBusySelf(false);
            setActiveChannel(type_SCH);
            channelIdle(true);
            phy11p->changeListeningFrequency(frequency[mySCH]);
            break;
        case type_SCH:
            DBG_MAC << "SCH --> CCH" << std::endl;
            channelBusySelf(false);
            setActiveChannel(type_CCH);
            channelIdle(true);
            phy11p->changeListeningFrequency(frequency[Channels::CCH]);
            break;
        }
            //schedule next channel switch in 50ms

    }
    else if (msg == nextMacEvent)
    {

        if(isACKSent)
            return;

        if (activeChannel == type_SCH)
        {//We use service channel to transit a data packet
            //transmitting packet process and Retransmission process (discard a packet retransmitted more than 3 times)
            if(Lstate == waitack && retransmissionnumbers > 3)
            {
                myEDCA[activeChannel]->postTransmit(lastAC);
                Lstate = none;
                retransmissionnumbers = 0;
                if (ackEvent->isScheduled())
                {
                    cancelEvent(ackEvent);
                }
                PktDropedDueToRetransmission_case1++;
                return;
            }
            else if (Lstate != waitack && retransmissionnumbers > 3)
            {
                myEDCA[activeChannel]->postTransmit(lastAC);
                Lstate = none;
                retransmissionnumbers = 0;

                if (ackEvent->isScheduled())
                {
                    cancelEvent(ackEvent);
                }
                PktDropedDueToRetransmission_case2++;
                return;
            }
            if (Lstate == none || (Lstate == waitack && LastSentTime + RetransTimer < simTime())){
                channelBusySelf(true);
                multipleRSUsRTpkt* pktToSend = myEDCA[activeChannel]->initiateTransmit(lastIdle);
                if (pktToSend == nullptr){//in case no packet was ready
                    return;
                }
                lastAC = mapPriority(pktToSend->getPriority());

                DBG_MAC << "MacEvent received. Trying to send packet with priority" << lastAC << std::endl;
                Mac80211Pkt* mac = new Mac80211Pkt(pktToSend->getName(), pktToSend->getKind());
                dynamic_cast<multipleRSUsRTpkt*>(pktToSend)->setPktActualsrcMac(myMacAddress);
                mac->setSrcAddr(myMacAddress);
                std::string p = "MAC: HANDLE SELF MESSAGE";
                macPktTracing(p, pktToSend);
                mac->setDestAddr(dynamic_cast<multipleRSUsRTpkt*>(pktToSend)->getPktActualdestMac());
                mac->encapsulate(pktToSend->dup());
                simtime_t sendingDuration = RADIODELAY_11P + getFrameDuration(mac->getBitLength());

                DBG_MAC << "Sending duration will be" << sendingDuration << std::endl;

                if ((!useSCH) || (timeLeftInSlot() > sendingDuration + AckSendingDuration)) {

                   if (useSCH) DBG_MAC << " Time in this slot left: " << timeLeftInSlot() << std::endl;
                   // give time for the radio to be in Tx state before transmitting
                   phy->setRadioState(Radio::TX);

                   double freq = (activeChannel == type_CCH) ? frequency[Channels::CCH] : frequency[mySCH];

                   attachSignal(mac, simTime() + RADIODELAY_11P, freq);
                   MacToPhyControlInfo* phyInfo = dynamic_cast<MacToPhyControlInfo*>(mac->getControlInfo());
                   assert(phyInfo);

                   DBG_MAC << "Sending a Packet. Frequency " << freq << " Priority" << lastAC << std::endl;
        //           PktWaitingAckQueue.insert(mac->dup());
                   Lstate = packetsent;
                   sendDelayed(mac, RADIODELAY_11P, lowerLayerOut);
                   statsSentPackets++;
                //            std::cout<<" our packet is already sent  "<<endl;
                }
                else {   //not enough time left now
                   DBG_MAC << "Too little Time left. This packet cannot be send in this slot." << std::endl;
                   statsNumTooLittleTime++;
                   //revoke TXOP
//                   std::cout<<" Unable to send our packet from mac "<< mac->getName() <<endl;
                   myEDCA[activeChannel]->revokeTxOPs();
                   delete mac;
                   channelIdle();           //do nothing. contention will automatically start after channel switch
                }

            }

        }
        else{//We use Control Channel (CCH) to broadcast routing table beacon packet
            channelBusySelf(true);
            multipleRSUsRTpkt* pktToSend = myEDCA[activeChannel]->initiateTransmit(lastIdle);

            lastAC = mapPriority(pktToSend->getPriority());

            DBG_MAC << "MacEvent received. Trying to send packet with priority" << lastAC << std::endl;

            //send the packet
    //        Mac80211Pkt* mac = new Mac80211Pkt(pktToSend->getName(), pktToSend->getKind());
            Mac80211Pkt* mac = new Mac80211Pkt(pktToSend->getName(), pktToSend->getKind());
            mac->setSrcAddr(myMacAddress);
            mac->setDestAddr(LAddress::L2BROADCAST);
            pktToSend->setRtsenderMacAdd(myMacAddress);
            mac->encapsulate(pktToSend->dup());

            simtime_t sendingDuration = RADIODELAY_11P + getFrameDuration(mac->getBitLength());
            DBG_MAC << "Sending duration will be" << sendingDuration << std::endl;
            if ((!useSCH) || (timeLeftInSlot() > sendingDuration)) {

               if (useSCH) DBG_MAC << " Time in this slot left: " << timeLeftInSlot() << std::endl;
               // give time for the radio to be in Tx state before transmitting
               phy->setRadioState(Radio::TX);

               double freq = (activeChannel == type_CCH) ? frequency[Channels::CCH] : frequency[mySCH];

               attachSignal(mac, simTime() + RADIODELAY_11P, freq);
               MacToPhyControlInfo* phyInfo = dynamic_cast<MacToPhyControlInfo*>(mac->getControlInfo());
               assert(phyInfo);
               DBG_MAC << "Sending a Packet. Frequency " << freq << " Priority" << lastAC << std::endl;
               myEDCA[activeChannel]->Lstate = myEDCA[activeChannel]->acksent;
               sendDelayed(mac, RADIODELAY_11P, lowerLayerOut);
               statsSentPackets++;
            }
            else {   //not enough time left now
               DBG_MAC << "Too little Time left. This packet cannot be send in this slot." << std::endl;
               statsNumTooLittleTime++;
               //revoke TXOP
               myEDCA[activeChannel]->revokeTxOPs();
               delete mac;
               channelIdle();           //do nothing. contention will automatically start after channel switch
            }

        }

    }
    else if (msg == nextCheckEvent)
    {
        simtime_t offset = dblrand() * par("syncOffset").doubleValue();
//        scheduleAt(simTime() + offset, nextRTEvent);
        scheduleAt(simTime() + 0.1, nextCheckEvent);
    }
    else if (msg == ackEvent){ //Event to acknowledge a successfully received packet
        channelBusySelf(false);
        lastAC = mapPriority(AC_BK);

        DBG_MAC << "MacEvent received. Trying to send packet with priority" << lastAC << std::endl;
        Mac80211Pkt* mac = new Mac80211Pkt("acknowledgement");
        mac->setSrcAddr(myMacAddress);
        mac->setDestAddr(AckDestAddr);

        simtime_t sendingDuration = RADIODELAY_11P + getFrameDuration(mac->getBitLength()) + SIFS_11P;
        DBG_MAC << "Sending duration will be" << sendingDuration << std::endl;
        if(timeLeftInSlot() > sendingDuration && activeChannel == type_SCH){

           // give time for the radio to be in Tx state before transmitting
           phy->setRadioState(Radio::TX);

           double freq = (activeChannel == type_CCH) ? frequency[Channels::CCH] : frequency[mySCH];

           attachSignal(mac, simTime() + RADIODELAY_11P + SIFS_11P, freq);
           MacToPhyControlInfo* phyInfo = dynamic_cast<MacToPhyControlInfo*>(mac->getControlInfo());
           assert(phyInfo);
           isACKSent = true;
           DBG_MAC << "Sending a Packet. Frequency " << freq << " Priority" << lastAC << std::endl;
           sendDelayed(mac, RADIODELAY_11P, lowerLayerOut);
           statsSentPackets++;
        //            std::cout<<" our packet is already sent  "<<endl;
        }
        else {   //not enough time left now
            cout <<  simTime()<<" "<<findHost()->getFullName()<<"ACK dropped due to too little time slot "<<endl;
            delete mac;
        }
    }

}
void Mac1609_4::handleUpperControl(cMessage* msg) {
    assert(false);
}
void Mac1609_4::handleUpperMsg(cMessage* msg) {

    multipleRSUsRTpkt* thisMsg;
    if ((thisMsg = dynamic_cast<multipleRSUsRTpkt*>(msg)) == NULL) {
        error("vrtpktMac only accepts vrtpkt");
    }

    t_access_category ac = mapPriority(thisMsg->getPriority());

    DBG_MAC << "Received a message from upper layer for channel "
            << thisMsg->getChannelNumber() << " Access Category (Priority):  "
            << ac << std::endl;

    t_channel chan;

    //rewrite SCH channel to actual SCH the Mac1609_4 is set to
    if (thisMsg->getChannelNumber() == Channels::SCH1) {
        ASSERT(useSCH);
        thisMsg->setChannelNumber(mySCH);
        chan = type_SCH;
    }


    //put this packet in its queue
    if (thisMsg->getChannelNumber() == Channels::CCH) {
        chan = type_CCH;
    }

    if (std::string(msg->getName()) == "GeneratedPkt"){ //Trace Packet
        DBG_MAC<<" Packet from Application received in Mac"<<endl;
        std::string P = "MAC: Handle Upper Msg";
        macPktTracing(P,thisMsg);
    }

    int num = myEDCA[chan]->queuePacket(ac,thisMsg);

    //packet was dropped in Mac
    if (num == -1) {
        statsDroppedPackets++;
        return;
    }

    //if this packet is not at the front of a new queue we dont have to reevaluate times
    DBG_MAC << "sorted packet into queue of EDCA " << chan << " this packet is now at position: " << num << std::endl;

    if (chan == activeChannel) {
        DBG_MAC << "this packet is for the currently active channel" << std::endl;
    }
    else {
        DBG_MAC << "this packet is NOT for the currently active channel" << std::endl;
    }

    if (num == 1 && idleChannel == true && chan == activeChannel) {

        simtime_t nextEvent = myEDCA[chan]->startContent(lastIdle,guardActive());

        if (nextEvent != -1) {
            if ((!useSCH) || (nextEvent <= nextChannelSwitch->getArrivalTime())) {
                if (nextMacEvent->isScheduled()) {
                    cancelEvent(nextMacEvent);
                }
                scheduleAt(nextEvent,nextMacEvent);
                DBG_MAC << "Updated nextMacEvent:" << nextMacEvent->getArrivalTime().raw() << std::endl;
            }
            else {
                DBG_MAC << "Too little time in this interval. Will not schedule nextMacEvent" << std::endl;
                //it is possible that this queue has an txop. we have to revoke it
                myEDCA[activeChannel]->revokeTxOPs();
                statsNumTooLittleTime++;
            }
        }
        else {
            cancelEvent(nextMacEvent);
        }
    }
    if (num == 1 && idleChannel == false && myEDCA[chan]->myQueues[ac].currentBackoff == 0 && chan == activeChannel) {
        myEDCA[chan]->backoff(ac);
    }

}

void Mac1609_4::handleLowerControl(cMessage* msg) {
    if (msg->getKind() == MacToPhyInterface::TX_OVER) {

        DBG_MAC << "Successfully transmitted a packet on " << lastAC << std::endl;

        phy->setRadioState(Radio::RX);

        if(activeChannel == type_SCH){
            if (!isACKSent){
                if (Lstate == packetsent){
                    Lstate = waitack;
                    retransmissionnumbers++;
                    LastSentTime = simTime();
                    RetransTimer = uniform(0,CWMIN_11P * SLOTLENGTH_11P + pow(2,retransmissionnumbers)*SLOTLENGTH_11P) + SendingDuration + AckSendingDuration;
                }
            }
            else{
                isACKSent = false;
            }
        }
        else{
            myEDCA[activeChannel]->postTransmit(lastAC);
            Lstate = none;
            retransmissionnumbers = 0;
            if (nextMacEvent->isScheduled() == true){
                cancelEvent(nextMacEvent);
            }
            if (ackEvent->isScheduled() == true){
                cancelEvent(ackEvent);
            }

        }

       /* if (guardActive()) {
            opp_error("We shouldn't have sent a packet in guard!");
        }*/
    }
    else if (msg->getKind() == Mac80211pToPhy11pInterface::CHANNEL_BUSY) {
        channelBusy();
    }
    else if (msg->getKind() == Mac80211pToPhy11pInterface::CHANNEL_IDLE) {
        channelIdle();
    }
    else if (msg->getKind() == Decider80211p::BITERROR) {
        statsSNIRLostPackets++;
        DBG_MAC << "A packet was not received due to biterrors" << ", Mac: "<<myMacAddress<< std::endl;
    }
    else if (msg->getKind() == Decider80211p::RECWHILESEND) {
        statsTXRXLostPackets++;
        DBG_MAC << "A packet was not received because we were sending while receiving" << ", Mac: "<<myMacAddress<<std::endl;

    }
    else if (msg->getKind() == MacToPhyInterface::RADIO_SWITCHING_OVER) {
        DBG_MAC << "Phylayer said radio switching is done" << ", Mac: "<<myMacAddress<< std::endl;
    }
    else if (msg->getKind() == BaseDecider::PACKET_DROPPED) {
        phy->setRadioState(Radio::RX);
        DBG_MAC << "Phylayer said packet was dropped" << std::endl;
    }
    else {
        DBG_MAC << "Invalid control message type (type=NOTHING) : name="
                       << msg->getName() << " module src="
                       << msg->getSenderModule()->getFullPath() << "."
                       << std::endl;
        assert(false);
    }
    delete msg;
}

void Mac1609_4::setActiveChannel(t_channel state) {
    activeChannel = state;
    assert(state == type_CCH || (useSCH && state == type_SCH));
}

void Mac1609_4::finish() {
    //clean up queues.
    cout <<" Packets dropped in Mac : "<< statsDroppedPackets<<endl;
    cout<<"PktDropped while retransmitted more then three times :  "<<PktDropedDueToRetransmission_case1<<endl;
    cout<<"PktDropped while retransmitted more then three times :  "<<PktDropedDueToRetransmission_case2<<endl;
    for (std::map<t_channel, EDCA*>::iterator iter = myEDCA.begin();
            iter != myEDCA.end(); iter++) {
        statsNumInternalContention += iter->second->statsNumInternalContention;
        statsNumBackoff += iter->second->statsNumBackoff;
        statsSlotsBackoff += iter->second->statsSlotsBackoff;
        iter->second->cleanUp();
        delete iter->second;
    }

    myEDCA.clear();
    if (nextMacEvent->isScheduled()) {
        cancelAndDelete(nextMacEvent);
    }
    else {
        delete nextMacEvent;
    }
//    Added to finish EDD events
    if (nextCheckEvent->isScheduled()){
        cancelAndDelete(nextCheckEvent);
    }
    else{
        delete nextCheckEvent;
    }
//    end of EDD added to finish EDD Events
    if (nextChannelSwitch && nextChannelSwitch->isScheduled())
        cancelAndDelete(nextChannelSwitch);

    //stats
    recordScalar("ReceivedUnicastPackets", statsReceivedPackets);
    recordScalar("ReceivedBroadcasts", statsReceivedBroadcasts);
    recordScalar("SentPackets", statsSentPackets);
    recordScalar("SNIRLostPackets", statsSNIRLostPackets);
    recordScalar("RXTXLostPackets", statsTXRXLostPackets);
    recordScalar("TotalLostPackets",
            statsSNIRLostPackets + statsTXRXLostPackets);
    recordScalar("DroppedPacketsInMac", statsDroppedPackets);
    recordScalar("TooLittleTime", statsNumTooLittleTime);
    recordScalar("TimesIntoBackoff", statsNumBackoff);
    recordScalar("SlotsBackoff", statsSlotsBackoff);
    recordScalar("NumInternalContention", statsNumInternalContention);
    recordScalar("totalBusyTime", statsTotalBusyTime.dbl());

}

void Mac1609_4::attachSignal(Mac80211Pkt* mac, simtime_t startTime, double frequency) {

    simtime_t duration = getFrameDuration(mac->getBitLength());

    Signal* s = createSignal(startTime, duration, txPower, bitrate, frequency);
    MacToPhyControlInfo* cinfo = new MacToPhyControlInfo(s);

    mac->setControlInfo(cinfo);
}
Signal* Mac1609_4::createSignal(simtime_t start, simtime_t length, double power, double bitrate, double frequency) {
    simtime_t end = start + length;
//    create signal with start at current simtime and passed length
    Signal* s = new Signal(start, length);

    //create and set tx power mapping
    ConstMapping* txPowerMapping = createSingleFrequencyMapping(start, end,frequency, 5.0e6, power);
    s->setTransmissionPower(txPowerMapping);

    Mapping* bitrateMapping = MappingUtils::createMapping(DimensionSet::timeDomain, Mapping::STEPS);

    Argument pos(start);
    bitrateMapping->setValue(pos, bitrate);
    pos.setTime(phyHeaderLength / bitrate);
    bitrateMapping->setValue(pos, bitrate);
    s->setBitrate(bitrateMapping);

    return s;
}

/* checks if guard is active */
bool Mac1609_4::guardActive() const {
    if (!useSCH) return false;
    if (simTime().dbl() - nextChannelSwitch->getSendingTime() <= GUARD_INTERVAL_11P)
        return true;
    return false;
}

/* returns the time until the guard is over */
simtime_t Mac1609_4::timeLeftTillGuardOver() const {
    ASSERT(useSCH);
    simtime_t sTime = simTime();
    if (sTime - nextChannelSwitch->getSendingTime() <= GUARD_INTERVAL_11P) {
        return GUARD_INTERVAL_11P - (sTime - nextChannelSwitch->getSendingTime());
    }
    else
        return 0;
}

/* returns the time left in this channel window */
simtime_t Mac1609_4::timeLeftInSlot() const {
    ASSERT(useSCH);
    return nextChannelSwitch->getArrivalTime() - simTime();
}

/* Will change the Service Channel on which the mac layer is listening and sending */
void Mac1609_4::changeServiceChannel(int cN) {
    ASSERT(useSCH);
    if (cN != Channels::SCH1 && cN != Channels::SCH2 && cN != Channels::SCH3 && cN != Channels::SCH4) {
        opp_error("This Service Channel doesnt exit: %d", cN);
    }

    mySCH = cN;

    if (activeChannel == type_SCH) {
        //change to new chan immediately if we are in a SCH slot,
        //otherwise it will switch to the new SCH upon next channel switch
        phy11p->changeListeningFrequency(frequency[mySCH]);
    }
}

void Mac1609_4::handleLowerMsg(cMessage* msg) {
    DBG_MAC <<" HANDLE LAWER MESSAGES" <<endl;
    Mac80211Pkt* macPkt = static_cast<Mac80211Pkt*>(msg);
    ASSERT(macPkt);

    multipleRSUsRTpkt* pkts = dynamic_cast<multipleRSUsRTpkt*>(macPkt->decapsulate());

    long dest = macPkt->getDestAddr();
    DBG_MAC << "Received frame name= " << macPkt->getName() << ", myState=" << " src=" << macPkt->getSrcAddr() << " dst=" << macPkt->getDestAddr() << " myAddr=" << myMacAddress << std::endl;

    if (std::string (macPkt->getName()) == "VRT"){

        sendUp(pkts);
    }
    else if (std::string (macPkt->getName()) == "GeneratedPkt"){
        DBG_MAC <<" Packet : "<< macPkt->getName() <<" Dest MAC:  "<<macPkt->getDestAddr()<< " My MAC : "<<myMacAddress <<endl;
        if ( macPkt->getDestAddr() == myMacAddress){
            std::string p = "MAC: HANDLE LOWER MSG";
            macPktTracing(p, pkts);
            DBG_MAC <<" Actual Packet for me in Mac sending to Upper Layer "<<endl;
//            cout <<"!!!!!!!! condition ! From: " << macPkt->getSrcAddr()<<"  :: Destined to : "<<macPkt->getDestAddr() <<endl;
            pkts->setPktActualsrcMac(macPkt->getSrcAddr());
            AckDestAddr = macPkt->getSrcAddr();
            scheduleAt(simTime(), ackEvent);
            sendUp(pkts);
        }
        else{
            delete pkts;
        }
    }
    else if (std::string (macPkt->getName()) == "acknowledgement"){

        if (macPkt->getDestAddr() == myMacAddress){
            if (Lstate == waitack){
                if (nextMacEvent->isScheduled() == true){//in case retransmission is scheduled, we cancel it after receiving the acknowledgement.
                    cancelEvent(nextMacEvent);
                }
                myEDCA[type_SCH]->postTransmit(lastAC);
                Lstate = none;
                retransmissionnumbers = 0;
                delete pkts;
                return;
            }
            else{
                delete pkts;
            }
        }

    }
    //-----------------------------------------------------------------------------
//    else{
//        cout<<" ??????????? Unkown packet received: "<<macPkt->getName()<<"  ???????????"<<endl;
//    }
    else if(std::string (macPkt->getName()) == "RSUGeneratedPkt")
    {
        cout << "RSU generated Packet received! " << endl;
    }
    //-----------------------------------------------------------------------------
    delete macPkt;
}

int Mac1609_4::EDCA::queuePacket(t_access_category ac,multipleRSUsRTpkt* msg) {

    if (maxQueueSize && myQueues[ac].queue.size() >= maxQueueSize) {
        cout << "!!!!!!!!! THE EDCA QUEUE IS FULl !!!!!!!!!"<<  " & Maximum Queue size :  "<<maxQueueSize<<endl;
        delete msg;
        return -1;
    }

    myQueues[ac].queue.push(msg);

    return myQueues[ac].queue.size();
}

int Mac1609_4::EDCA::createQueue(int aifsn, int cwMin, int cwMax,t_access_category ac) {
    if (myQueues.find(ac) != myQueues.end()) {
        throw cRuntimeError("You can only add one queue per Access Category per EDCA subsystem");
    }

    EDCAQueue newQueue(aifsn,cwMin,cwMax,ac);
    myQueues[ac] = newQueue;

    return ++numQueues;
}

Mac1609_4::t_access_category Mac1609_4::mapPriority(int prio) {
    //dummy mapping function
    switch (prio) {
        case 0: return AC_BK;
        case 1: return AC_BE;
        case 2: return AC_VI;
        case 3: return AC_VO;
        default: throw cRuntimeError("MacLayer received a packet with unknown priority"); break;
    }
    return AC_VO;
}

multipleRSUsRTpkt* Mac1609_4::EDCA::initiateTransmit(simtime_t lastIdle) {
    //iterate through the queues to return the packet we want to send
    multipleRSUsRTpkt* pktToSend = NULL;

    simtime_t idleTime = simTime() - lastIdle;

    DBG_MAC << "Initiating transmit at " << simTime() << ". I've been idle since " << idleTime << std::endl;

    for (std::map<t_access_category, EDCAQueue>::iterator iter = myQueues.begin(); iter != myQueues.end(); iter++) {
        if (iter->second.queue.size() != 0) {
            if (idleTime >= iter->second.aifsn* SLOTLENGTH_11P + SIFS_11P && iter->second.txOP == true) {

                DBG_MAC << "Queue " << iter->first << " is ready to send!" << std::endl;

                iter->second.txOP = false;
                //this queue is ready to send
                if (pktToSend == NULL) {
                    pktToSend = iter->second.queue.front();
                }
                else {
                    //there was already another packet ready. we have to go increase cw and go into backoff. It's called internal contention and its wonderful

                    statsNumInternalContention++;
                    iter->second.cwCur = std::min(iter->second.cwMax,iter->second.cwCur*2);
                    iter->second.currentBackoff = intuniform(0,iter->second.cwCur);
                    DBG_MAC << "Internal contention for queue " << iter->first  << " : "<< iter->second.currentBackoff << ". Increase cwCur to " << iter->second.cwCur << std::endl;
                }
            }
        }
    }

  /*  if (pktToSend == NULL) {
        throw cRuntimeError("No packet was ready");
    }*/
    return pktToSend;
}

simtime_t Mac1609_4::EDCA::startContent(simtime_t idleSince,bool guardActive) {
    DBG_MAC << "Restarting contention." << std::endl;

    simtime_t nextEvent = -1;

    simtime_t idleTime = SimTime().setRaw(std::max((int64_t)0,(simTime() - idleSince).raw()));;

    lastStart = idleSince;

    DBG_MAC << "Channel is already idle for:" << idleTime << " since " << idleSince << std::endl;

    //this returns the nearest possible event in this EDCA subsystem after a busy channel

    for (std::map<t_access_category, EDCAQueue>::iterator iter = myQueues.begin(); iter != myQueues.end(); iter++) {
        if (iter->second.queue.size() != 0) {

            /* 1609_4 says that when attempting to send (backoff == 0) when guard is active, a random backoff is invoked */

            if (guardActive == true && iter->second.currentBackoff == 0) {
                //cw is not increased
                iter->second.currentBackoff = intuniform(0,iter->second.cwCur);
//                std::cout <<" StartContent : Int Uniform ["<<0<<","<<iter->second.cwCur<<"] = "<<iter->second.currentBackoff<<endl;
                statsNumBackoff++;
            }

            simtime_t DIFS = iter->second.aifsn * SLOTLENGTH_11P + SIFS_11P;

//            the next possible time to send can be in the past if the channel was idle for a long time, meaning we COULD have sent earlier if we had a packet
            simtime_t possibleNextEvent = DIFS + iter->second.currentBackoff * SLOTLENGTH_11P;


            DBG_MAC << "Waiting Time for Queue " << iter->first <<  ":" << possibleNextEvent << "=" << iter->second.aifsn << " * "  << SLOTLENGTH_11P << " + " << SIFS_11P << "+" << iter->second.currentBackoff << "*" << SLOTLENGTH_11P << "; Idle time: " << idleTime << std::endl;

            if (idleTime > possibleNextEvent) {
                DBG_MAC << "Could have already send if we had it earlier" << std::endl;
                //we could have already sent. round up to next boundary
                simtime_t base = idleSince + DIFS;
                possibleNextEvent =  simTime() - simtime_t().setRaw((simTime() - base).raw() % SLOTLENGTH_11P.raw()) + SLOTLENGTH_11P;
            }
            else {
                //we are gonna send in the future
                DBG_MAC << "Sending in the future" << std::endl;
                possibleNextEvent =  idleSince + possibleNextEvent;
            }
            nextEvent == -1? nextEvent =  possibleNextEvent : nextEvent = std::min(nextEvent,possibleNextEvent);
        }
    }
    return nextEvent;
}

void Mac1609_4::EDCA::stopContent(bool allowBackoff, bool generateTxOp) {
    //update all Queues

    DBG_MAC << "Stopping Contention at " << simTime().raw() << std::endl;

    simtime_t passedTime = simTime() - lastStart;

    DBG_MAC << "Channel was idle for " << passedTime << std::endl;

    lastStart = -1; //indicate that there was no last start

    for (std::map<t_access_category, EDCAQueue>::iterator iter = myQueues.begin(); iter != myQueues.end(); iter++) {
        if (iter->second.currentBackoff != 0 || iter->second.queue.size() != 0) {
            //check how many slots we already waited until the chan became busy

            int oldBackoff = iter->second.currentBackoff;

            std::string info;
            if (passedTime < iter->second.aifsn * SLOTLENGTH_11P + SIFS_11P) {
                //we didnt even make it one DIFS :(
                info.append(" No DIFS");
            }
            else {
                //decrease the backoff by one because we made it longer than one DIFS
                iter->second.currentBackoff--;

                //check how many slots we waited after the first DIFS
                int passedSlots = (int)((passedTime - SimTime(iter->second.aifsn * SLOTLENGTH_11P + SIFS_11P)) / SLOTLENGTH_11P);

                DBG_MAC << "Passed slots after DIFS: " << passedSlots << std::endl;


                if (iter->second.queue.size() == 0) {
                    //this can be below 0 because of post transmit backoff -> backoff on empty queues will not generate macevents,
                    //we dont want to generate a txOP for empty queues
                    iter->second.currentBackoff -= std::min(iter->second.currentBackoff,passedSlots);
                    info.append(" PostCommit Over");
                }
                else {
                    iter->second.currentBackoff -= passedSlots;
                    if (iter->second.currentBackoff <= -1) {
                        if (generateTxOp) {
                            iter->second.txOP = true; info.append(" TXOP");
                        }
                        //else: this packet couldnt be sent because there was too little time. we could have generated a txop, but the channel switched
                        iter->second.currentBackoff = 0;
                    }
                }
            }
            DBG_MAC << "Updating backoff for Queue " << iter->first << ": " << oldBackoff << " -> " << iter->second.currentBackoff << info <<std::endl;
        }
    }
}
void Mac1609_4::EDCA::backoff(t_access_category ac) {
    myQueues[ac].currentBackoff = intuniform(0,myQueues[ac].cwCur);
    statsSlotsBackoff += myQueues[ac].currentBackoff;
    statsNumBackoff++;
    DBG_MAC << "Going into Backoff because channel was busy when new packet arrived from upperLayer" << std::endl;
}

void Mac1609_4::EDCA::postTransmit(t_access_category ac) {

    delete myQueues[ac].queue.front();
    myQueues[ac].queue.pop();
    myQueues[ac].cwCur = myQueues[ac].cwMin;

    //post transmit backoff
    myQueues[ac].currentBackoff = intuniform(0,myQueues[ac].cwCur);
    statsSlotsBackoff += myQueues[ac].currentBackoff;
    statsNumBackoff++;
    DBG_MAC << "Queue " << ac << " will go into post-transmit backoff for " << myQueues[ac].currentBackoff << " slots" << std::endl;
}

void Mac1609_4::EDCA::cleanUp() {
    for (std::map<t_access_category, EDCAQueue>::iterator iter = myQueues.begin(); iter != myQueues.end(); iter++) {
        while (iter->second.queue.size() != 0) {
            delete iter->second.queue.front();
            iter->second.queue.pop();
        }
    }
    myQueues.clear();
}

void Mac1609_4::EDCA::revokeTxOPs() {
    for (std::map<t_access_category, EDCAQueue>::iterator iter = myQueues.begin(); iter != myQueues.end(); iter++) {
        if (iter->second.txOP == true) {
            iter->second.txOP = false;
            iter->second.currentBackoff = 0;
        }
    }
}

void Mac1609_4::channelBusySelf(bool generateTxOp) {
    //the channel turned busy because we're sending. we don't want our queues to go into backoff
    //internal contention is already handled in initiateTransmission

    if (!idleChannel)
        return;
    idleChannel = false;
    DBG_MAC << "Channel turned busy: Switch or Self-Send" << std::endl;

    lastBusy = simTime();

    //channel turned busy
    if (nextMacEvent->isScheduled() == true) {
        cancelEvent(nextMacEvent);
    }
    else {
        //the edca subsystem was not doing anything anyway.
    }
    myEDCA[activeChannel]->stopContent(false, generateTxOp);
}

void Mac1609_4::channelBusy() {
    if (!idleChannel)
        return;

    //the channel turned busy because someone else is sending
    idleChannel = false;
    DBG_MAC << "Channel turned busy: External sender" << std::endl;
    lastBusy = simTime();

    //channel turned busy
    if (nextMacEvent->isScheduled() == true) {
        cancelEvent(nextMacEvent);
    }
    else {
        //the edca subsystem was not doing anything anyway.
    }
    myEDCA[activeChannel]->stopContent(true,false);

}
void Mac1609_4::channelIdle(bool afterSwitch) {
    DBG_MAC << "Channel turned idle: Switch: " << afterSwitch << std::endl;

    if (nextMacEvent->isScheduled() == true) {
        //this rare case can happen when another node's time has such a big offset that the node sent a packet although we already changed the channel
        //the workaround is not trivial and requires a lot of changes to the phy and decider
        return;
        //opp_error("channel turned idle but contention timer was scheduled!");
    }

    idleChannel = true;

    simtime_t delay = 0;

    //account for 1609.4 guards
    if (afterSwitch) {
        //  delay = GUARD_INTERVAL_11P;
    }
    if (useSCH) {
        delay += timeLeftTillGuardOver();
    }

    //channel turned idle! lets start contention!
    lastIdle = delay + simTime();
    statsTotalBusyTime += simTime() - lastBusy;

    //get next Event from current EDCA subsystem
    simtime_t nextEvent = myEDCA[activeChannel]->startContent(lastIdle,guardActive());
    if (nextEvent != -1) {
        if((!useSCH) ||(nextEvent + uniform(AckSendingDuration,SimTime(1,SIMTIME_MS)) < nextChannelSwitch->getArrivalTime())){
            scheduleAt(nextEvent + uniform(AckSendingDuration, SimTime(1,SIMTIME_MS)),nextMacEvent);
//        if ((!useSCH) || (nextEvent < nextChannelSwitch->getArrivalTime())) {//previous
//            scheduleAt(nextEvent,nextMacEvent);//previous
            DBG_MAC << "next Event is at " << nextMacEvent->getArrivalTime().raw() << std::endl;
        }
        else {
            DBG_MAC << "Too little time in this interval. will not schedule macEvent" << std::endl;
            statsNumTooLittleTime++;
            myEDCA[activeChannel]->revokeTxOPs();
        }
    }
    else {
        DBG_MAC << "I don't have any new events in this EDCA sub system" << std::endl;
    }
}

void Mac1609_4::setParametersForBitrate(int bitrate) {
    for (unsigned int i = 0; i < NUM_BITRATES_80211P; i++) {
        if (bitrate == BITRATES_80211P[i]) {
            n_dbps = N_DBPS_80211P[i];
            return;
        }
    }
    opp_error("Chosen Bitrate is not valid for 802.11p: Valid rates are: 3Mbps, 4.5Mbps, 6Mbps, 9Mbps, 12Mbps, 18Mbps, 24Mbps and 27Mbps. Please adjust your omnetpp.ini file accordingly.");
}

simtime_t Mac1609_4::getFrameDuration(int payloadLengthBits) const {
    // calculate frame duration according to Equation (17-29) of the IEEE 802.11-2007 standard
    simtime_t duration = PHY_HDR_PREAMBLE_DURATION + PHY_HDR_PLCPSIGNAL_DURATION + T_SYM_80211P * ceil((16 + payloadLengthBits + 6) / (n_dbps));

    return duration;
}

/*In this function, We choose the intersections we need to place the RSU
 * We find its TraCI coordinates and convert into Omnet Coordinates
 * Save Coordinates into srucoord.txt later to be used in omnetpp.ini*/
void Mac1609_4::RSUsCoordinatesFile(){
    ofstream rsf;
    rsf.open("/home/aime/Downloads/TBDVADD/src/graph-configuration/srucoord.txt");
    if (rsf.is_open()){
        Veins::TraCICoord tc1 = Vm->getCommandInterface()->getJunctionPosition("1/7");
        Veins::TraCICoord tc2 = Vm->getCommandInterface()->getJunctionPosition("2/6");
        Veins::TraCICoord tc3 = Vm->getCommandInterface()->getJunctionPosition("3/5");
        Veins::TraCICoord tc4 = Vm->getCommandInterface()->getJunctionPosition("5/7");
        Veins::TraCICoord tc5 = Vm->getCommandInterface()->getJunctionPosition("4/6");
        Veins::TraCICoord tc6 = Vm->getCommandInterface()->getJunctionPosition("3/4");
        Veins::TraCICoord tc7 = Vm->getCommandInterface()->getJunctionPosition("3/3");
        Veins::TraCICoord tc8 = Vm->getCommandInterface()->getJunctionPosition("2/2");
        Veins::TraCICoord tc9 = Vm->getCommandInterface()->getJunctionPosition("1/1");
        Veins::TraCICoord tc10 = Vm->getCommandInterface()->getJunctionPosition("4/2");
        Veins::TraCICoord tc11 = Vm->getCommandInterface()->getJunctionPosition("5/1");
        Coord c1 = Vm->getManager()->traci2omnet(tc1);
        Coord c2 = Vm->getManager()->traci2omnet(tc2);
        Coord c3 = Vm->getManager()->traci2omnet(tc3);
        Coord c4 = Vm->getManager()->traci2omnet(tc4);
        Coord c5 = Vm->getManager()->traci2omnet(tc5);
        Coord c6 = Vm->getManager()->traci2omnet(tc6);
        Coord c7 = Vm->getManager()->traci2omnet(tc7);
        Coord c8 = Vm->getManager()->traci2omnet(tc8);
        Coord c9 = Vm->getManager()->traci2omnet(tc9);
        Coord c10 = Vm->getManager()->traci2omnet(tc10);
        Coord c11 = Vm->getManager()->traci2omnet(tc11);
        rsf << "rsu[0]:"<<"1/7: ("<<c1.x<<","<<c1.y<<","<<c1.z<<")"<<endl;
        rsf << "rsu[1]:"<<"2/6: ("<<c2.x<<","<<c2.y<<","<<c2.z<<")"<< endl;
        rsf << "rsu[2]:"<<"3/5: ("<<c3.x<<","<<c3.y<<","<<c3.z<<")"<<endl;
        rsf << "rsu[3]:"<<"5/7: ("<<c4.x<<","<<c4.y<<","<<c4.z<<")"<<endl;
        rsf << "rsu[4]:"<<"4/6: ("<<c5.x<<","<<c5.y<<","<<c5.z<<")"<<endl;
        rsf << "rsu[5]:"<<"3/4: ("<<c6.x<<","<<c6.y<<","<<c6.z<<")"<<endl;
        rsf << "rsu[6]:"<<"3/3: ("<<c7.x<<","<<c7.y<<","<<c7.z<<")"<<endl;
        rsf << "rsu[7]:"<<"2/2: ("<<c8.x<<","<<c8.y<<","<<c8.z<<")"<<endl;
        rsf << "rsu[8]:"<<"1/1: ("<<c9.x<<","<<c9.y<<","<<c9.z<<")"<<endl;
        rsf << "rsu[9]:"<<"4/2: ("<<c10.x<<","<<c10.y<<","<<c10.z<<")"<<endl;
        rsf << "rsu[10]:"<<"5/1: ("<<c11.x<<","<<c11.y<<","<<c11.z<<")"<<endl;
    }
    rsf.close();
}

void Mac1609_4::macPktTracing(std::string where_are_we, multipleRSUsRTpkt* pkt){
    if (macpktfile.is_open() == false){
        macpktfile.open("/home/aime/Downloads/TBDVADD/examples/veins/VADDResults/pktinMac.txt", fstream::in | fstream::out | fstream::app);
    }
    if (macpktfile.is_open() == true){
        if (findHost()->getName() != "rsu"){
            macpktfile <<where_are_we/*<<"  , Current Position : ("<<myMobi->getCurrentPosition().x<<", "<<myMobi->getCurrentPosition().y<<", "<<myMobi->getCurrentPosition().z<<")"*/
                    <<" Vehicle ID : "<< findHost()->getFullName() << " Pkt Seq. Number: "<<pkt->getSeqNumber() << " Time : "<<simTime()<<endl;
        }
        else{
            macpktfile <<" My ID : "<< findHost()->getFullName() << " Pkt Seq. Number: "<<pkt->getSeqNumber() << " Time : "<<simTime()<<endl;
        }
    }
    macpktfile.close();
}
void Mac1609_4::EDCA::WriteEDCAQueueContents(multipleRSUsRTpkt* pkt){
    if (edcaQueuecontentfile.is_open() == false){
        edcaQueuecontentfile.open("/home/aime/Downloads/TBDVADD/examples/veins/VADDResults/edcaqueueContents.txt", fstream::in | fstream::out | fstream::app);
    }
    if (edcaQueuecontentfile.is_open() == true){
        macpktfile << " Pkt Seq. Number: "<<pkt->getSeqNumber() << " Time : "<<simTime()<<endl;
    }

}


