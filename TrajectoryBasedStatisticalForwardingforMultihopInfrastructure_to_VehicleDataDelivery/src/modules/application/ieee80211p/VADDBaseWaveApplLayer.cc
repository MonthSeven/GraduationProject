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

#include "VADDBaseWaveApplLayer.h"
//#include "VaddPktTraceDebug.h"

const simsignalwrap_t VADDBaseWaveApplLayer::mobilityStateChangedSignal = simsignalwrap_t(MIXIM_SIGNAL_MOBILITY_CHANGE_NAME);
//Veins::TraCIMobility* GlobalMobi;
const simsignalwrap_t VADDBaseWaveApplLayer::checkingUpdatedRTsignal = simsignalwrap_t("RT check signal");
static int numGenPkts = 0; //Number of generated packets
static int numRecPkts = 0; //Number of received packets
static int numDiscDueTtlExp; //Discarded packets due to TTL expiration
static vector<simtime_t> PktDeliveryDelays; //Delivery delays
int SN = 0;
fstream appPktfile;
//fstream pkTr ("/home/aime/Downloads/veins-veins-vadd/examples/veins/VADDResults/pktTracing.txt");
std::vector<adjacentnodes> globalAdjacentStr;
fstream pkTr;
//Migration of Mac codes
static double fixedSpeed = 10;
static int forwardingChoice = 0;
double c = 0.001;
static double PreviousDelays = true;
static bool OriginalStatistics = false;
std::string Destination;
Veins::TraCIMobility* Vm2;
std::vector <std::string> globAllEdges;
std::vector <std::string> RSUsids;
std::map <std::string,std::vector<std::string>> globEdgeJunctionMap;
static bool ismultipleRSUs = true;
std::vector <MultipleRSUsGraph> glabalMultiPleRSUGraph;
//End of Mac codes migrations
bool sortNeigbours (std::map<string, double>::iterator i,std::map<string, double>::iterator j) {
    return (i->second < j->second);
}
void VADDBaseWaveApplLayer::initialize(int stage)
{
  //std::cout << "DEBUGING::VADDBaseWaveApplLayer::initialize" << end;
    BaseApplLayer::initialize(stage);
    if (stage == 0)
    {
        pktTr.clear(); // packet trace, (int, vector<string>) -> packet seq, different nodes
//        std::cout<<" VADD AppLayer Initialization : "<<endl;
        myMac = FindModule<WaveAppToMac1609_4Interface*>::findSubModule(getParentModule());
        assert(myMac);
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
        // I added
        generatepkt = new cMessage("Actual Packet"); // sendig from RSUs
        rtEvent = new cMessage(" Vehicle RT Event");
        checkvehedge = new cMessage("Check Edge");
        selfRTcheck = new cMessage("Checking self RT");
        packetforward = new cMessage("Pkt forward");
        rsutestevent = new cMessage(" rsu test ");//from Mac
        //----------------------------------  %%%%%%%% I added
        rsu0event = new cMessage("rsu[0]");
        rsugeneratepkt = new cMessage("rsugenerate");
        // -----------------------------------------------------
        initialization = new cMessage("Initialize Road Graph");//from Mac
        HostCollectionEvent = new cMessage("Hosts collection ");//from Mac
        collectstatisticsevent = new cMessage("Collecting Statistics");//Delays,FloydWarshall,Probabilities and EDD (From Mac)
        //simulate asynchronous channel access
        double offSet = dblrand() * (par("beaconInterval").doubleValue()/2);
        offSet = offSet + floor(offSet/0.050)*0.050;
        individualOffset = dblrand() * maxOffset;
        findHost()->subscribe(mobilityStateChangedSignal, this);
//      findHost()->subscribe(checkingUpdatedRTsignal,this);
//      std::cout<<"::::::: Host Name :::::::"<<findHost()->getFullName()<<endl;
        cm = (ConnectionManager*)getOwner()->getOwner()->findObject("connectionManager",true);

        scheduleAt(simTime()  + 183, rtEvent);
//        scheduleAt(simTime() + 0.01, initialization);
        if (sendBeacons)
        {
//          scheduleAt(selfRTchecksimTime() + offSet, sendBeaconEvt);
        }
        // Here I/
        bool TSF = true;
        if(TSF)
        {
             //Veins::TraCIMobility* Vm;
            /* 나줄에 쓰일수도 있지않을까?
            // Veins::TraCIMobility* Vm;
            int i = 0;
            std::list <std::string> allJunctions = Vm->getCommandInterface()->getJunctionIds();
            for(std::list <std::string>::iterator iter = allJunctions.begin(); iter != allJunctions.end(); iter++)
            {
                Veins::TraCICoord junctionPosition = Vm->getCommandInterface()->getJunctionPosition(*iter);
                Coord C = Vm->getManager()->traci2omnet(junctionPosition);
                //std::cout << "RSU[" << i++ << "]" << "X: "  << C.x << "Y: " << C.y << "Z: " << C.z << endl;
            }
             */

//            if (strcmp(findHost()->getFullName(), "rsu[0]") == 0)
//            {
//                scheduleAt(simTime() + 1.0, rsu0event);
//                std::cout << "initialization afrer rsu[0]" << endl;
//            }
            if (strcmp(findHost()->getName(), "rsu") == 0)
            {
                //std::cout << "scheduled!" << endl;
                //scheduleAt(simTime() + 185 + dblrand() * 0.01, rsugeneratepkt);
                // 왜 위의 초가 안먹을
                scheduleAt(simTime() + 1.0, rsugeneratepkt);
            }
        }
        else
        {
            if (strcmp(findHost()->getFullName(), "node[0]") == 0)
            {
                Vm2 = (Veins::TraCIMobility*)getOwner()->findObject("veinsmobility", true);
            }
            if (strcmp(findHost()->getName(), "node") == 0)
            {
                //scheduleAt(simTime() + 183, rtEvent);
                //cout << findHost()->getFullName() << " schedules rtEvent at " << rtEvent->getArrivalTime() << endl;
                vehTraCIMobi = (Veins::TraCIMobility*)getOwner()->findObject("veinsmobility", true);
                //scheduleAt(simTime() + 64, checkvehedge);
                scheduleAt(simTime() + 185 + dblrand() * 0.01, generatepkt);
            }
            if (strcmp(findHost()->getFullName(), "rsu[0]") == 0)
            { //from Mac

    //            cout<< " Host id : "<< findHost()->getFullName()<<endl;

                scheduleAt(simTime() + 1, rsutestevent);
            }//end from Mac
            vehBaseMobi = (BaseMobility*)getOwner()->findObject("mobility", true);
        }

    }
}
multipleRSUsRTpkt*  VADDBaseWaveApplLayer::preparepkts()
{
    bool TSF = true;
    if(TSF)
    {
        //std::cout << "DEBUGGING::VADDWaveApplLayer::preparepkts__FOR TSF" << endl;
        multipleRSUsRTpkt* pkts = new multipleRSUsRTpkt("RSUGeneratedPkt");
        //pkts->setMyid(findHost()->getFullName());
        pkts->setMyid("RSU_Packet");
//        if(strcmp(findHost()->getName(), "rsu") == 0)
//        {
//
//            pkts->setPktSourceID(findHost()->getFullName());
//            pkts->setPktActualsrcID(findHost()->getFullName());
//        }
        //pkts->setPktSourceID(findHost()->getFullName());
        pkts->setPktGenerationTime(simTime());
        //pkts->setPktActualsrcID(findHost()->getFullName());
        pkts->setPktlastReceiveTime(0);
        pkts->setSeqNumber(SN);
        pkts->setPktTTL(1800);
        //pkts->setPriority(3);
        pkts->setPriority(0);
        pkts->setChannelNumber(Channels::SCH1);
        if (ismultipleRSUs)
        {
        // std::cout << "Get in the 'ismultipleRSUs' " << endl;
        //    std::st6ring edgeid = vehTraCIMobi->getCommandInterface()->getEdgeId(vehTraCIMobi->getExternalId());
        //  std::cout << "edgeid: " << edgeid << endl;
        //   std::string DestRSU = chooseDestinationRSU(edgeid);
        //   cout <<" The chosen Destination is : "<< DestRSU << endl;
        //   pkts->setPktDestinationID(DestRSU.c_str());

        }
        else
        {
           // pkts->setPktDestinationID("rsu[0]");
        }
        ++SN;
        return pkts;

    }
    else
    {
        multipleRSUsRTpkt* pkts = new multipleRSUsRTpkt("GeneratedPkt");
        pkts->setPktSourceID(findHost()->getFullName());
        pkts->setPktGenerationTime(simTime());
        pkts->setPktActualsrcID(findHost()->getFullName());
        pkts->setPktlastReceiveTime(0);
        pkts->setSeqNumber(SN);
        pkts->setPktTTL(1800);
        pkts->setPriority(3);
        pkts->setChannelNumber(Channels::SCH1);
        if (ismultipleRSUs)
        {
            std::string edgeid = vehTraCIMobi->getCommandInterface()->getEdgeId(vehTraCIMobi->getExternalId());
            std::cout << "edgeid: " << edgeid << endl;
            std::string DestRSU = chooseDestinationRSU(edgeid);
            std::cout <<" The chosen Destination is : "<< DestRSU << endl;
            pkts->setPktDestinationID(DestRSU.c_str());
            std::cout << "preparepkts" << endl;
        }
        else
        {
            pkts->setPktDestinationID("rsu[0]");
        }
        ++SN;
        return pkts;
    }
}
std::string VADDBaseWaveApplLayer::chooseDestinationRSU(std::string curVehEdgeId) //useful in multiple RSUs data forwarding // 
{
  //  printf("DEBUGING::VADDBaseWaveApplLayer::chooseDestinationRSU\n");
  // deleted by copyright issue
    return RSUid;
}
void VADDBaseWaveApplLayer::UpdateReceivedPacket(multipleRSUsRTpkt* pkts){
    // deleted by copyright issue 
}
void VADDBaseWaveApplLayer::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj)
{
    bool TSF = true;
    if(TSF)
    {
        Enter_Method_Silent();
        if(signalID == mobilityStateChangedSignal)
        {
            //handlePositionUpdate(obj);
        }

    }
    else
    {
        //Enter_Method_Silent();
        Veins::TraCIMobility* veh = (Veins::TraCIMobility*)getOwner()->findObject("veinsmobility", true);
        if (signalID == mobilityStateChangedSignal) {
           // cout << "mobilityStateChangedSignal" << endl;
            handlePositionUpdate(obj);
            if (strcmp(findHost()->getName(), "node") == 0){
               // cout <<veh->getExternalId() /*<<" OmnetID: " <<findHost()->getFullName()  */<<" Edge : " <<veh->getCommandInterface()->getEdgeId(veh->getExternalId())<<endl;
            }

        }
    }
}
void VADDBaseWaveApplLayer::checkAndSendPkt(){
  // deleted by copyright issue
}
void VADDBaseWaveApplLayer::handlePositionUpdate(cObject* obj)
{
    //std::cout << "VADDBaseWaveApplLayer::handlePositionUpdate" << endl;
    bool TSF = true;
    if(TSF)
    {
            ;
    }
    else
    {
        ChannelMobilityPtrType const mobility = check_and_cast<ChannelMobilityPtrType>(obj);
        curPosition = mobility->getCurrentPosition();
    }
}
void VADDBaseWaveApplLayer::handleLowerMsg(cMessage* msg)
{
    // 여기서 받은 것을 가지고 누가 보냇는지 정보를 추출..
    std::cout << "handleLowerMsg" << endl;
    bool TSF = true;
    if(TSF)
    {
        multipleRSUsRTpkt* packet = dynamic_cast<multipleRSUsRTpkt*>(msg);
        ASSERT(packet);
        if(strcmp(packet->getPktSourceID(), "RSUGeneratedPkt") == 0)
        {
            std::cout << "Get in if statement" << endl;
            std::cout <<" My Generated packet is properly received"<< endl;
            std::cout<<" Sender ID: "<< packet->getPktSourceID() << " RCR ID : "<<findHost()->getFullName() << endl;
        }
        delete(packet);
    }
    else
    {
  // deleted by copyright issue
    }
}
void VADDBaseWaveApplLayer::handleSelfMsg(cMessage* msg)
{
    // 여기서 그냥 rsuevent면 senddown, 한다 브로드캐스트
    //std::cout << "VADDBaseWaveApplLayer::handleSelfMsg" << endl;
    bool TSF = true;
    if(TSF)
    {
        if(msg == rsu0event)
        {
            ;
        }
        else if(msg == rsugeneratepkt)
        {
            //std::cout << "Appl HandleSelfMsg packet by RSU are sent!" << endl;
            multipleRSUsRTpkt* pkt = preparepkts();
            sendDown(pkt);
            scheduleAt(simTime() + 10, rsugeneratepkt);
            //std::cout << "handleSelfMsg scheduled!" << endl;
        }
    }
    else
    {
          // deleted by copyright issue
    }
}
void VADDBaseWaveApplLayer::sendpkts(multipleRSUsRTpkt* pkts)
{
    //std::cout << "DEBUGING::VADDBaseWaveApplLayer::sendpkts" << endl;
    sendDelayedDown(pkts, individualOffset);
}
void VADDBaseWaveApplLayer::finish() {
    //std::cout << "DEBUGING::VADDBaseWaveApplLayer::finish" << endl;;
    if (sendBeaconEvt->isScheduled())
    {
        cancelAndDelete(sendBeaconEvt);
    }
    else
    {
        delete sendBeaconEvt;
    }

//    Finishing VADD added events
    adjacent.clear();
    EdgeJunctionsmap.clear();
    exterEdgeMeanSpeeds.clear();

    if (rtEvent->isScheduled()){
        cancelAndDelete(rtEvent);
    }
    else{
        delete rtEvent;
    }
    if (checkvehedge->isScheduled()){
        cancelAndDelete(checkvehedge);
    }
    else{
        delete checkvehedge;
    }
    if (selfRTcheck->isScheduled()){
        cancelAndDelete(selfRTcheck);
    }
    else{
        delete selfRTcheck;
    }
 
    simtime_t SumDeliveryDelays = 0;
    simtime_t AverageDeliveryRatio = 0;
    for(unsigned int i = 0; i < PktDeliveryDelays.size(); i++){
//       res <<PktDeliveryDelays[i]<<endl;
//       std::cout<<PktDeliveryDelays[i] << " ; "<<endl;
       SumDeliveryDelays += PktDeliveryDelays[i];
    }
    AverageDeliveryRatio = SumDeliveryDelays/PktDeliveryDelays.size();
    // -----------------------------------------------------------------------------------------------------------
//    res << " Average Delivery Delay Ratio : "<<AverageDeliveryRatio<<endl;
//    std::cout <<"Average Delivery Delay Ratio :  "<<AverageDeliveryRatio<<endl;
//    res.close();
    // ------------------------------------------------------------------------------------------------------------
   /* std::map<int, std::vector <std::string>>::iterator tit;
       for (tit = pktTr.begin(); tit != pktTr.end(); tit++){
           cout <<" Packet "<<tit->first<<" :  "<<endl;
           for (unsigned int i = 0; i < tit->second.size(); tit++){
               cout<<tit->second[i]<<" <=> ";
           }
           cout<<endl;
       }*/
//    End of finishing VADD added events
    findHost()->unsubscribe(mobilityStateChangedSignal, this);
}

multipleRSUsRTpkt* VADDBaseWaveApplLayer::multipleRSUsNodeRT()
{
  // deleted by copyright issue
}
void VADDBaseWaveApplLayer::sendVRT(multipleRSUsRTpkt* vroute){
    printf("DEBUGING::VADDBaseWaveApplLayer::sendVRT\n");
    sendDown(vroute);
}
void VADDBaseWaveApplLayer::sendMultipleRSUVRT(multipleRSUsRTpkt* rt){
    printf("DEBUGING::VADDBaseWaveApplLayer::sendMultipleRSUVRT\n");
    sendDown(rt);
}
void VADDBaseWaveApplLayer::sendPktFromQueue(vrtStruct actualSenderRt, cPacketQueue mypktQueue){
  // deleted by copyright issue
}
double VADDBaseWaveApplLayer::getCurrentEdgeEDD(string vehEdge) // 이부분도 내가?
{
  // deleted by copyright issue
}
double VADDBaseWaveApplLayer::getCurrentEdgeEDDMultipleRSUSGraph(std::string vehEdge, std::string DestRSU) // 이부분도 내
{
  // deleted by copyright issue
}
double VADDBaseWaveApplLayer::getVehEDDValue(string VID, std::string dstRSU) // 이부분
{
  // deleted by copyright issue
}
void VADDBaseWaveApplLayer::packetTrace(multipleRSUsRTpkt* pkt){
  // deleted by copyright issue

}
void VADDBaseWaveApplLayer::writetrace(std::string where_are_we, multipleRSUsRTpkt* pkt, double asrcedd, double arcvedd){
  // deleted by copyright issue
}
bool VADDBaseWaveApplLayer::checkVehicleisAtTheIntersectionArea(std::string VID){
  // deleted by copyright issue

}
void VADDBaseWaveApplLayer::pktTraceInApp(std::string where_are_we, multipleRSUsRTpkt* pkt){
  // deleted by copyright issue
}
//Migration of Mac codes
void VADDBaseWaveApplLayer::intersectionTrafficsCollection() {
  // deleted by copyright issue
//    globalAdjacentStr = adjacent;
}
void VADDBaseWaveApplLayer::CollectEdgeWeights() {
  // deleted by copyright issue
}
/*We first of all for each junction sort its adjacent junctions weight and prioritize them
 * The one with high priority is the one with shortest path is all pairs Shortest path Map
 * This with high priority, we assign its Forwarding priority equals its contact probability
 * Next, Following priorities order for all adjacent junctions by setting the FProbijk = (1-FProbijs) * CProbijk
 * refer Equation 6 in TBD paper */
void VADDBaseWaveApplLayer::ForwardingProbabilities() {
  // deleted by copyright issue
}
/* We check duplication at the end of vehicle collection
 * We subtract for each junction the times it was duplicated*/
void VADDBaseWaveApplLayer::insideDuplicationCheck() {
  // deleted by copyright issue
}
/* Edge the packet Carrier heads to
 * Know its EDD and compare it with other adjacent edges
 * Apply formula 7 of TBD paper
 * */
double VADDBaseWaveApplLayer::ConditionalForwardingProbabilities(int k, int h, adjacentnodes cNode, std::vector<std::map<string, double>::iterator> w) {
  // deleted by copyright issue
}
void VADDBaseWaveApplLayer::ComputeEDD() {
    // deleted by copyright issue

}
void VADDBaseWaveApplLayer::ComputeEDDForMultipleRSUs(){
  // deleted by copyright issue

}
std::map<std::string,std::string> VADDBaseWaveApplLayer::rsujunctionsmap(){
  // deleted by copyright issue
}
double VADDBaseWaveApplLayer::computeAngle(std::string curJunct,std::string adjJunct, std::string rsuJunct){
   // deleted by copyright issue
    }



//End of Mac codes migrations
VADDBaseWaveApplLayer::~VADDBaseWaveApplLayer() {

}
