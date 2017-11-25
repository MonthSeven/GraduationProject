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

#include "application/traci/VADDRSU11p.h"

using Veins::AnnotationManagerAccess;

Define_Module(VADDRSU11p);

/*
void TraCIDemoRSU11p::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);
    if (stage == 0) {
        mobi = dynamic_cast<BaseMobility*> (getParentModule()->getSubmodule("mobility"));
        ASSERT(mobi);
        annotations = AnnotationManagerAccess().getIfExists();
        ASSERT(annotations);
        sentMessage = false;
    }
}*/
void VADDRSU11p::initialize(int stage)
{
    //std::cout << "VADDRSU11p::initialize" << endl;
    VADDBaseWaveApplLayer::initialize(stage);
    if (stage == 0)
    {
        mobi = dynamic_cast<BaseMobility*> (getParentModule()->getSubmodule("mobility"));
        ASSERT(mobi);
        annotations = AnnotationManagerAccess().getIfExists();
        ASSERT(annotations);
        bool TSF = true;
        if(TSF)
        {
           //sentMessage = false;
        }
    }
}

void VADDRSU11p::onBeacon(multipleRSUsRTpkt* pkts)
{
    //std::cout << "VADDRSU11p::onBeacon" << endl;
}
/*
void TraCIDemoRSU11p::onData(kwon* kpm) {
    findHost()->getDisplayString().updateWith("r=16,green");

  //  annotations->scheduleErase(1, annotations->drawLine(kpm->getSenderPos(), mobi->getCurrentPosition(), "blue"));

    if (!sentMessage) sendMessage(kpm->getKwonData());

}
*/
void VADDRSU11p::onData(multipleRSUsRTpkt* pkts)
{
    //std::cout << "VADDRSU11p::onData" << endl;
    findHost()->getDisplayString().updateWith("r=16,green");
    //annotations->scheduleErase(1, annotations->drawLine(pkts->getSenderPos(), mobi->getCurrentPosition(), "blue"));
    //if (!sentMessage) sendMessage(pkts->getWsmData());
    bool TSF = true;
    if(TSF)
    {
        std::cout << "VADDRSU11p::onData" << endl;
      //  annotations->scheduleErase(1, annotations->drawLine(pkts->getSenderPos(), mobi->getCurrentPosition(), "blue"));
        if (!sentMessage)
        {
            //sendMessage(pkts->getFullPath());
            // getpktsData 가 없어서,,,
        }
    }
}
/*
void TraCIDemoRSU11p::sendMessage(std::string blockedRoadId) {
    sentMessage = true;
    t_channel channel = dataOnSch ? type_SCH : type_CCH;
    kwon* kpm = prepareKP("data", dataLengthBits, channel, dataPriority, -1,2);
    kpm->setKwonData(blockedRoadId.c_str());
    sendKPM(kpm);
}
*/
//void VADDRSU11p::sendMessage(std::string blockedRoadId)
void VADDRSU11p::sendMessage(std::string rsuname)
{
   // std::cout << "VADDRSU11p::sendMessage" << endl;
    sentMessage = true;
    t_channel channel = dataOnSch ? type_SCH : type_CCH;
    //pkt_Send* pkts = preparepkts("data", dataLengthBits, channel, dataPriority, -1,2);
    //pkt_Send* pkts = preparepkts();
    //pkts->setWsmData(blockedRoadId.c_str());
    //sendpkts(pkts);
    bool TSF = true;
    if(TSF)
    {
        //VADDBaseWaveApplLayer 에서 보낸다.
        //std::cout << "VADDRSU11p::sendMessage::rsuname: " << rsuname << endl;
        std::cout << "VADDRSU11p::sendMessage packet by RSU are sent!" << endl;
        multipleRSUsRTpkt* pkt = preparepkts();
        sendDown(pkt);
        scheduleAt(simTime() + 1.0, rsugeneratepkt);

    }
    else
    {
        // multipleRSUsRTpkt* pkts = preparepkts();
         //pkts->set
         //pkt_Send* pkts = preparepkts("data", dataLengthBits, channel, dataPriority, -1,2);
    }
}
/*
void TraCIDemoRSU11p::sendKPM(kwon* kpm) {
    sendDelayedDown(kpm,individualOffset);
}
*/
void VADDRSU11p::sendpkts(multipleRSUsRTpkt* pkts)
{
    //std::cout << "VADDRSU11p::sendpkts" << endl;
    sendDelayedDown(pkts, individualOffset);
}
