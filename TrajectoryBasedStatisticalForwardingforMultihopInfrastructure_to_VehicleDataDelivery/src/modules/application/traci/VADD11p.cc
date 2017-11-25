//
// Copyright (C) 2006-2011 Christoph Sommer <christoph.sommer@uibk.ac.at>
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

#include "application/traci/VADD11p.h"

using Veins::TraCIMobilityAccess;
using Veins::AnnotationManagerAccess;

const simsignalwrap_t VADD11p::parkingStateChangedSignal = simsignalwrap_t(TRACI_SIGNAL_PARKING_CHANGE_NAME);

Define_Module(VADD11p);

/*
 void TraCIDemo11p::initialize(int stage) {
    std::cout << "TraCIDemo11p::initialize" << endl;
    BaseWaveApplLayer::initialize(stage);
    if (stage == 0) {
        mobility = TraCIMobilityAccess().get(getParentModule());
        traci = mobility->getCommandInterface();
        traciVehicle = mobility->getVehicleCommandInterface();
        annotations = AnnotationManagerAccess().getIfExists();
        ASSERT(annotations);

        sentMessage = false;
        lastDroveAt = simTime();
        findHost()->subscribe(parkingStateChangedSignal, this);
        isParking = false;
        sendWhileParking = par("sendWhileParking").boolValue();
    }
}
 */
void VADD11p::initialize(int stage)
{
    //std::cout << endl << "VADD11p::initialize" << endl;
    VADDBaseWaveApplLayer::initialize(stage);
    if (stage == 0)
    {
        traci = TraCIMobilityAccess().get(getParentModule());
        annotations = AnnotationManagerAccess().getIfExists();
        ASSERT(annotations);
        sentMessage = false;
        lastDroveAt = simTime();
        findHost()->subscribe(parkingStateChangedSignal, this);
        isParking = false;
        sendWhileParking = par("sendWhileParking").boolValue();
    }
}

void VADD11p::onBeacon(multipleRSUsRTpkt* pkts)
{
    //std::cout << endl << "VADD11p::onBeacon" << endl;
}
/*
void TraCIDemo11p::onData(kwon* kpm)
{
    findHost()->getDisplayString().updateWith("r=16,green");
   // annotations->scheduleErase(1, annotations->drawLine(kpm->getSenderPos(), mobility->getPositionAt(simTime()), "blue"));

    if (mobility->getRoadId()[0] != ':') traciVehicle->changeRoute(kpm->getKwonData(), 9999);
    if (!sentMessage) sendMessage(kpm->getKwonData());
}
*/
void VADD11p::onData(multipleRSUsRTpkt* pkts)
{
    //std::cout << endl << "VADD11p::onData" << endl;
    findHost()->getDisplayString().updateWith("r=16,green");
    //annotations->scheduleErase(1, annotations->drawLine(pkts->getSenderPos(), traci->getPositionAt(simTime()), "blue"));
    //if (traci->getRoadId()[0] != ':') traci->commandChangeRoute(pkts->getWsmData(), 9999);
    //if (!sentMessage) sendMessage(pkts->getWsmData());
}
/*
void TraCIDemo11p::sendMessage(std::string blockedRoadId)
{
    sentMessage = true;
    t_channel channel = dataOnSch ? type_SCH : type_CCH;
    kwon* kpm = prepareKP("data", dataLengthBits, channel, dataPriority, -1,2);
    kpm->setKwonData(blockedRoadId.c_str());
    sendKPM(kpm);
}
*/
void VADD11p::sendMessage(std::string blockedRoadId)
{
    //std::cout << endl << "VADD11p::sendMessage" << endl;
    sentMessage = true;
    t_channel channel = dataOnSch ? type_SCH : type_CCH;
    bool TSF = true;
    if(TSF)
    {
        ;
        // 차량에선 안보내보겠다.
    }
    else
    {
        //pkt_Send* pkts = preparepkts("data", dataLengthBits, channel, dataPriority, -1,2);
        multipleRSUsRTpkt* pkts = preparepkts();
        //pkts->setWsmData(blockedRoadId.c_str());
        sendpkts(pkts);
    }
}
/*
void TraCIDemo11p::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj) {
    Enter_Method_Silent();
    if (signalID == mobilityStateChangedSignal) {
        handlePositionUpdate(obj);
    }
    else if (signalID == parkingStateChangedSignal) {
        handleParkingUpdate(obj);
    }
}
*/
void VADD11p::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj)
{
    //std::cout << endl << "VADD11p::receiveSignal" << endl;
    Enter_Method_Silent();
    /*Denotes module class member function as callable from other modules.
     */
    if (signalID == mobilityStateChangedSignal)
    {
        handlePositionUpdate(obj);
    }
    else if (signalID == parkingStateChangedSignal)
    {
        handleParkingUpdate(obj);
    }
}
/*
void TraCIDemo11p::handleParkingUpdate(cObject* obj) {
    isParking = mobility->getParkingState();
    if (sendWhileParking == false) {
        if (isParking == true) {
            (FindModule<BaseConnectionManager*>::findGlobalModule())->unregisterNic(this->getParentModule()->getSubmodule("nic"));
        }
        else {
            Coord pos = mobility->getCurrentPosition();
            (FindModule<BaseConnectionManager*>::findGlobalModule())->registerNic(this->getParentModule()->getSubmodule("nic"), (ChannelAccess*) this->getParentModule()->getSubmodule("nic")->getSubmodule("phy80211p"), &pos);
        }
    }
}
*/
void VADD11p::handleParkingUpdate(cObject* obj)
{
    //std::cout << endl << "VADD11p::handleParkingUpdate" << endl;
    isParking = traci->getParkingState();
    if (sendWhileParking == false)
    {
        if (isParking == true)
        {
            (FindModule<BaseConnectionManager*>::findGlobalModule())->unregisterNic(this->getParentModule()->getSubmodule("nic"));
        }
        else
        {
            Coord pos = traci->getCurrentPosition();
            (FindModule<BaseConnectionManager*>::findGlobalModule())->registerNic(this->getParentModule()->getSubmodule("nic"), (ChannelAccess*) this->getParentModule()->getSubmodule("nic")->getSubmodule("phy80211p"), &pos);
        }
    }
}
/*
void TraCIDemo11p::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);

    // stopped for for at least 10s?
    if (mobility->getSpeed() < 1) {
        if (simTime() - lastDroveAt >= 10) {
            findHost()->getDisplayString().updateWith("r=16,red");
            if (!sentMessage) sendMessage(mobility->getRoadId());
        }
    }
    else {
        lastDroveAt = simTime();
    }
}
*/
void VADD11p::handlePositionUpdate(cObject* obj)
{
    //std::cout << endl << "VADD11p::handlePositionUpdate" << endl;
    VADDBaseWaveApplLayer::handlePositionUpdate(obj);
    // stopped for for at least 10s?
    if (traci->getSpeed() < 1)
    {
        if (simTime() - lastDroveAt >= 10)
        {
            findHost()->getDisplayString().updateWith("r=16,red");
            if (!sentMessage) sendMessage(traci->getRoadId());
        }
    }
    else
    {
        lastDroveAt = simTime();
    }
}
/*
void TraCIDemo11p::sendKPM(kwon* kpm)
{
    if (isParking && !sendWhileParking) return;
    sendDelayedDown(kpm,individualOffset);
}
*/
void VADD11p::sendpkts(multipleRSUsRTpkt* pkts)
{
    //std::cout << endl << "VADD11p::sendpkts" << endl;
    //if (isParking && !sendWhileParking) return;
    sendDelayedDown(pkts,individualOffset);
}
