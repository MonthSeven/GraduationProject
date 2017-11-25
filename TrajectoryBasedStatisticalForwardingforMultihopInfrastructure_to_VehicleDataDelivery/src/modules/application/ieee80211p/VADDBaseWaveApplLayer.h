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

#ifndef VADDBASEWAVEAPPLLAYER_H_
#define VADDBASEWAVEAPPLLAYER_H_

#include <map>
#include <BaseApplLayer.h>
#include <Consts80211p.h>
#include "base/connectionManager/ChannelAccess.h"
#include <WaveAppToMac1609_4Interface.h>
//#include <Vehicle_Routing_Table_m.h>
#include <VRTandPKT_m.h>
#include <BaseMobility.h>
#include <TraCIMobility.h>
#include <vector>
#include <iostream>
#include <algorithm>

#define VADDLambda(I) (( I == INFINITY) ? (0) : (1/I))

//End of Mac codes migrations

#ifndef DBG
#define DBG EV
#endif

//#define DBG std::cerr << "[" << simTime().raw() << "] " << getParentModule()->getFullPath() << " "

/**
 * @brief
 * WAVE application layer base class.
 *
 * @author David Eckhoff
 *
 * @ingroup applLayer
 *
 * @see BaseWaveApplLayer
 * @see Mac1609_4
 * @see PhyLayer80211p
 * @see Decider80211p
 */
using namespace std;

class VADDBaseWaveApplLayer : public BaseApplLayer, public GaussianElimination{

    public:
        ~VADDBaseWaveApplLayer();
        virtual void initialize(int stage);
        virtual void finish();
        virtual  void receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj);

        enum pktsendTypes {
            SERVICE_PROVIDER = LAST_BASE_APPL_MESSAGE_KIND,
            SEND_BEACON_EVT
        };
        std::map<std::string, std::vector<std::string>>::iterator mpiter;

//        globalVar* Gv;
        Veins::TraCIMobility* vehTraCIMobi;
        std::map<std::string, std::vector<std::string>> EdJunc;
        std::map<std::string, double> EdMeanSpeeds;
        std::map<std::string, double>::iterator mpit;
        double cRange;
        int returnVehIDWithSmallEDD(std::vector<vrtStruct> vehrt);
        int returnVehDestinationMac(std::vector<vrtStruct> vehrt, int vid);
        void checkAndSendPkt();
        void pktTraceInApp(std::string where_are_we, multipleRSUsRTpkt* pkt);


        //Migration of Mac codes

        struct JunctionAccessCout{
            string currentJunction;
            std::map<string,int> CountToDestination;
            std::map<std::string,std::map<string,int>> SourceToDestinationCount;
            std::map<std::string,std::map<string,std::map<string,int>>> SourceCurrentToDestinationCount;

        }JunctAcces;
        struct JunctionProbCount{
            string junctionProb;
            std::map<std::string,double> ProbabilitiesToDestination;
            std::map<std::string,std::map<std::string,double>> ProbabilitiesSourceToDestination;
            std::map<std::string,std::map<std::string,std::map<std::string,double>>> ProbabilitiesSourceCurrentToDestination;
            std::map<std::string, double> AverageForwardingProb;
        } ProbCount;
        std::map<std::string,std::map<string,std::map<string,std::vector<string> > > > dupCheckVehID;
        std::map<string,std::map<string, simtime_t> > VehArrivals;
        std::map<std::string, cModule*> hosts_Map;
        std::map<std::string, cModule*> temphosts_Map;
        std::map<std::string, cModule*> vehinmobility;
        string NODEID;
        string CurEdID;
        list <string> PlanEd;

        cModule* NodeModule;
        string runjunct;
        std::map <string, int> NumJunctAccess;
        string tempjunct;
        int tempcount;
        std::map <string, int>::iterator JIter;
        string RouteID;
        list <string> RouteEdgeIDs;
        list <string>::iterator li;

        vector <string> PlanEdVector;
        std::vector <string> adjEdge;
        std::map<string,std::map<string, simtime_t> >::iterator arrit2;
        map<string,vector<simtime_t>> EdgeVehArrivals; //key: Edge Id, value: Arrival time
        map<string,map<string, vector<simtime_t>>> EdgeVehicles;//key1:EdgeId, key2: VehicleId, value: arrival time
        map<string, int> JunctionVehicles;//key1: Junction Id, value: Number of Count
        simtime_t compTime ;//Comparison Time for duplication check
        std::map<std::string,simtime_t> EdgeSumOfInterravals;
        std::map<std::string,int> EdgeNumOfArrivals;
        std::vector <simtime_t> VehInterrarrivals;
        void intersectionTrafficsCollection();//From Mac
        void CollectEdgeWeights(); //from Mac
        void ForwardingProbabilities();//from Mac
        void ComputeEDD();
        void ComputeEDDForMultipleRSUs();
        void getRSUPosition();
        double computeAngle(std::string curJunct,std::string adjJunct, std::string rsuJunct);
        std::map<std::string,std::string> rsujunctionsmap();
        void AssignCommonStatisticsInGlobalGraphStructure();
        map<string,double> EdgeEDD;
        std::map <std::string, simtime_t>::iterator arrit1;
        std::map<std::string, cModule*>::iterator Iter;
        std::map<std::string, cModule*>::iterator tempIter;

//                Key: CurNode, second Key: Adjacent Junction, Value Count
        std::map<std::string, std::map<std::string, double>> NewCounts;
        std::map<std::string, double>::iterator NIT1;
        std::map<std::string, std::map<std::string, double>>::iterator NIT2;
        std::vector <double> tmpholdFProbs; //temporarily hold the Forwarding probabilities of best Edge than the one the carrier heads to.

        std::vector<string>::iterator vit;
        std::vector<string> tmpvect[70];
        std::vector<string>::iterator tmpit;
        std::map<string, vector <string>>::iterator mit;
        std::map<std::string, cModule*> tmpholder;
        std::map<std::string, cModule*>::iterator tmpIter;
        std::map<string,int>::iterator it1;
        std::map<std::string,std::map<string,int>>::iterator it2;
        std::map<std::string,std::map<string,std::map<string,int>>>::iterator it3;
        std::map<std::string,double>::iterator prit1;
        std::map<std::string,std::map<std::string,double>>::iterator prit2;
        std::map<std::string,std::map<std::string,std::map<std::string,double>>>::iterator prit3;
        void insideDuplicationCheck();
        double ContactProbabilities(double Lamda, double T);
        double CP;//contact probabilities
        enum dataforwardingscheme{
            angleBasedForwarding = 0,
            delayBasedForwarding = 1,
            distanceBasesForwarding = 2
        };
        double ConditionalForwardingProbabilities(int k, int h, adjacentnodes cNode, std::vector<std::map<string, double>::iterator> w);


        //End of Mac codes migrations


    protected:

        static const simsignalwrap_t mobilityStateChangedSignal;
        static const simsignalwrap_t checkingUpdatedRTsignal;
        /** @brief handle messages from below */
        virtual void handleLowerMsg(cMessage* msg);
        /** @brief handle self messages */
        virtual void handleSelfMsg(cMessage* msg);

        multipleRSUsRTpkt* preparepkts();
        std::string chooseDestinationRSU(std::string curVehEdgeId);
        std::string ForwadingDestination ="";
        void UpdateReceivedPacket(multipleRSUsRTpkt* pkts);
        void sendpkts(multipleRSUsRTpkt* pkts);
        virtual void onBeacon(multipleRSUsRTpkt* pkts) = 0;
        virtual void onData(multipleRSUsRTpkt* pkts) = 0;
//        cPacketQueue prePack;
        virtual void handlePositionUpdate(cObject* obj);
//        Added
        cMessage* sendBeaconEvt;
//        vrtpkt* VehicleRT();
//        void VehicleRT(std::string dstRSU, vrtpkt*);//Following Multiple RSUs case
        multipleRSUsRTpkt* multipleRSUsNodeRT();
        multipleRSUsRTpkt* UpdateVehicleRT(multipleRSUsRTpkt* vr);
        void PackRT(multipleRSUsRTpkt*);
        void sendVRT(multipleRSUsRTpkt*);
        void sendMultipleRSUVRT(multipleRSUsRTpkt*);
        multipleRSUsRTpkt* myRT;
        multipleRSUsRTpkt* pktForw;
        multipleRSUsRTpkt* packetForward(multipleRSUsRTpkt* pk);
        double getVehEDDValue(std::string VID, std::string dstRSU);//Added dstRSU for multiple RSUs
        double getCurrentEdgeEDD(std::string VID);
        double getCurrentEdgeEDDMultipleRSUSGraph(std::string CurrEdgeID, std::string DestRSU);
        bool checkRTSenderisOnMyWay(std::string VID);
        std::map<int, std::vector <std::string>> pktTr; //include pkt sequence and the different nodes (vehicles) it traversed.
        void packetTrace(multipleRSUsRTpkt* pkt);
        void writetrace(std::string where_are_we, multipleRSUsRTpkt* pkt, double asrcedd, double arcvedd);
        bool checkVehicleisAtTheIntersectionArea(std::string vehId);
    protected:
        int beaconLengthBits;
        int beaconPriority;
        bool sendData;
        bool sendBeacons;
        simtime_t individualOffset;
        int dataLengthBits;
        bool dataOnSch;
        int dataPriority;
        Coord curPosition;
        Coord recPosition;//added
        int mySCH;
        int myId;
        std::string myname;
//        cPacketQueue mypktQueue;
        std::map<std::string,cPacketQueue>  mypktQueuesMultiRSUs;//PacketQueues Considering Each Packet Destination for multiple RSUs Graph
        void sendPktFromQueue(vrtStruct actualsenderRt, cPacketQueue mypkt);
        void RemoveFromQueueSentPacket(std::string destinationId,std::map<std::string,cPacketQueue> vehPktQueue);
        std::map<int,std::vector<std::string>> PacketTrace;//to trace the packet forwarding toward the packet destination
        int destID; //Added
        BaseMobility* vehBaseMobi;
//        std::vector<vrtStruct> rt;
        std::map<std::string,std::vector<vrtStruct>> multipleRSUsRT;
        std::string vehCurrentEdge;
        WaveAppToMac1609_4Interface* myMac;
        WaveAppToMac1609_4Interface* nextCarrierMac; //added
        cMessage* rtEvent;
        cMessage* broadcastRT;
        cMessage* generatepkt;
        cMessage* packetforward;
        cMessage* checkvehedge;
        cMessage* selfRTcheck; //Message to be scheduled simply if the packet is created but that the destination is not in my RT and no vehicle with small EDD to mine
        cMessage* rsutestevent;//from Mac
        // I added ----------------------------
        cMessage* rsu0event;
        cMessage* rsugeneratepkt;
        // -----------------------------------------
        cMessage* initialization;//from Mac
        cMessage* HostCollectionEvent;//from Mac
        cMessage* collectstatisticsevent;//from Mac
        bool checkmyRThasDestination(std::vector<vrtStruct> rt, std::string DestinationID);
        std::vector<multipleRSUsRTpkt*> sentPacketscopy;
        ConnectionManager* cm; //From Mac
        std::map<std::string, double> exterEdgeMeanSpeeds;//From Mac

};

#endif  VADDBASEWAVEAPPLLAYER_H_
