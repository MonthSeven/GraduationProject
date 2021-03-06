//
// Generated file, do not edit! Created by nedtool 4.6 from src/modules/messages/Previous_VRTandPKT.msg.
//

#ifndef _PREVIOUS_VRTANDPKT_M_H_
#define _PREVIOUS_VRTANDPKT_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "Coord.h"
#include <map>
// }}

/**
 * Struct generated from src/modules/messages/Previous_VRTandPKT.msg:14 by nedtool.
 */
struct vrtStruct_Prev
{
    vrtStruct_Prev();
    int nodeMacAdd;
    opp_string nodeID;
    Coord nodePosition;
    double nodeSpeed;
    double nodeEDD_Value;
    simtime_t lastUpdateTime;
    int NumHopsToDst;
    simtime_t rtTTL;
};

void doPacking(cCommBuffer *b, vrtStruct_Prev& a);
void doUnpacking(cCommBuffer *b, vrtStruct_Prev& a);

/**
 * Class generated from <tt>src/modules/messages/Previous_VRTandPKT.msg:27</tt> by nedtool.
 * <pre>
 * packet vrtpkt_Prev
 * {
 *     string RSUDestID;//for multiple RSUs, we have different EDDs, resulting into different Routing Tables.
 *     double senderEDD_value; //RT Sender EDD
 *     //here include send routing table in packet
 *     string senderID;
 *     Coord senderPosition; //RT Sender Position
 *     double senderSpeed; //RT Sender Speed
 *     simtime_t sendingTime; //RT Sending time stamp
 * //    int priority;
 * //    end of send routing table packet   
 * 
 *     vrtStruct_Prev RT[];
 * }
 * </pre>
 */
class vrtpkt_Prev : public ::cPacket
{
  protected:
    opp_string RSUDestID_var;
    double senderEDD_value_var;
    opp_string senderID_var;
    Coord senderPosition_var;
    double senderSpeed_var;
    simtime_t sendingTime_var;
    vrtStruct_Prev *RT_var; // array ptr
    unsigned int RT_arraysize;

  private:
    void copy(const vrtpkt_Prev& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const vrtpkt_Prev&);

  public:
    vrtpkt_Prev(const char *name=NULL, int kind=0);
    vrtpkt_Prev(const vrtpkt_Prev& other);
    virtual ~vrtpkt_Prev();
    vrtpkt_Prev& operator=(const vrtpkt_Prev& other);
    virtual vrtpkt_Prev *dup() const {return new vrtpkt_Prev(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual const char * getRSUDestID() const;
    virtual void setRSUDestID(const char * RSUDestID);
    virtual double getSenderEDD_value() const;
    virtual void setSenderEDD_value(double senderEDD_value);
    virtual const char * getSenderID() const;
    virtual void setSenderID(const char * senderID);
    virtual Coord& getSenderPosition();
    virtual const Coord& getSenderPosition() const {return const_cast<vrtpkt_Prev*>(this)->getSenderPosition();}
    virtual void setSenderPosition(const Coord& senderPosition);
    virtual double getSenderSpeed() const;
    virtual void setSenderSpeed(double senderSpeed);
    virtual simtime_t getSendingTime() const;
    virtual void setSendingTime(simtime_t sendingTime);
    virtual void setRTArraySize(unsigned int size);
    virtual unsigned int getRTArraySize() const;
    virtual vrtStruct_Prev& getRT(unsigned int k);
    virtual const vrtStruct_Prev& getRT(unsigned int k) const {return const_cast<vrtpkt_Prev*>(this)->getRT(k);}
    virtual void setRT(unsigned int k, const vrtStruct_Prev& RT);
};

inline void doPacking(cCommBuffer *b, vrtpkt_Prev& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, vrtpkt_Prev& obj) {obj.parsimUnpack(b);}

// cplusplus {{
#include "map"
typedef std::map<std::string, vrtpkt_Prev*> MultRSUsRt;
// }}

/**
 * Class generated from <tt>src/modules/messages/Previous_VRTandPKT.msg:46</tt> by nedtool.
 * <pre>
 * packet MultipleRSUsRTpkt extends vrtpkt_Prev
 * {
 *     int priority;
 *     //    packet to be sent 
 *     string pktSourceID;
 *     int seqNumber = 0;
 *     string pktDestinationID;//The id of RSU destinned the packet
 *     int pktDestinationMac;//The Mac of RSU destinned the packet
 *     string pktActualsrcID;//the id of next carrier of packet
 *     int pktActualsrcMac;//the Mac of the next carrier of the packet 
 *     int pktActualdestMac;//Current Carrier Mac Address
 *     simtime_t pktGenerationTime;//The time the packet is generated
 *     simtime_t pktlastReceiveTime;//The time the current carrier received the packet
 *     simtime_t DestArrivalTime;//The time the packet reached the destination
 *     simtime_t pktTTL;//time to live of the packet
 * 
 *     // end of packet to be sent 
 *     //Acknowlegement
 *     string AckNodeID;
 *     int AckSenderMac;
 *     int AckDestMac;
 *     int AckPktSeqNum;
 *     //Acknowlegement End
 *     int channelNumber; //  Channel Number on which this packet was sent (Used in mac handle upperMessage)
 *     //    for routing table
 *     int senderMacAdd; //RT sender ID
 *     MultRSUsRt routing_table;
 * }
 * </pre>
 */
class MultipleRSUsRTpkt : public ::vrtpkt_Prev
{
  protected:
    int priority_var;
    opp_string pktSourceID_var;
    int seqNumber_var;
    opp_string pktDestinationID_var;
    int pktDestinationMac_var;
    opp_string pktActualsrcID_var;
    int pktActualsrcMac_var;
    int pktActualdestMac_var;
    simtime_t pktGenerationTime_var;
    simtime_t pktlastReceiveTime_var;
    simtime_t DestArrivalTime_var;
    simtime_t pktTTL_var;
    opp_string AckNodeID_var;
    int AckSenderMac_var;
    int AckDestMac_var;
    int AckPktSeqNum_var;
    int channelNumber_var;
    int senderMacAdd_var;
    MultRSUsRt routing_table_var;

  private:
    void copy(const MultipleRSUsRTpkt& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const MultipleRSUsRTpkt&);

  public:
    MultipleRSUsRTpkt(const char *name=NULL, int kind=0);
    MultipleRSUsRTpkt(const MultipleRSUsRTpkt& other);
    virtual ~MultipleRSUsRTpkt();
    MultipleRSUsRTpkt& operator=(const MultipleRSUsRTpkt& other);
    virtual MultipleRSUsRTpkt *dup() const {return new MultipleRSUsRTpkt(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getPriority() const;
    virtual void setPriority(int priority);
    virtual const char * getPktSourceID() const;
    virtual void setPktSourceID(const char * pktSourceID);
    virtual int getSeqNumber() const;
    virtual void setSeqNumber(int seqNumber);
    virtual const char * getPktDestinationID() const;
    virtual void setPktDestinationID(const char * pktDestinationID);
    virtual int getPktDestinationMac() const;
    virtual void setPktDestinationMac(int pktDestinationMac);
    virtual const char * getPktActualsrcID() const;
    virtual void setPktActualsrcID(const char * pktActualsrcID);
    virtual int getPktActualsrcMac() const;
    virtual void setPktActualsrcMac(int pktActualsrcMac);
    virtual int getPktActualdestMac() const;
    virtual void setPktActualdestMac(int pktActualdestMac);
    virtual simtime_t getPktGenerationTime() const;
    virtual void setPktGenerationTime(simtime_t pktGenerationTime);
    virtual simtime_t getPktlastReceiveTime() const;
    virtual void setPktlastReceiveTime(simtime_t pktlastReceiveTime);
    virtual simtime_t getDestArrivalTime() const;
    virtual void setDestArrivalTime(simtime_t DestArrivalTime);
    virtual simtime_t getPktTTL() const;
    virtual void setPktTTL(simtime_t pktTTL);
    virtual const char * getAckNodeID() const;
    virtual void setAckNodeID(const char * AckNodeID);
    virtual int getAckSenderMac() const;
    virtual void setAckSenderMac(int AckSenderMac);
    virtual int getAckDestMac() const;
    virtual void setAckDestMac(int AckDestMac);
    virtual int getAckPktSeqNum() const;
    virtual void setAckPktSeqNum(int AckPktSeqNum);
    virtual int getChannelNumber() const;
    virtual void setChannelNumber(int channelNumber);
    virtual int getSenderMacAdd() const;
    virtual void setSenderMacAdd(int senderMacAdd);
    virtual MultRSUsRt& getRouting_table();
    virtual const MultRSUsRt& getRouting_table() const {return const_cast<MultipleRSUsRTpkt*>(this)->getRouting_table();}
    virtual void setRouting_table(const MultRSUsRt& routing_table);
};

inline void doPacking(cCommBuffer *b, MultipleRSUsRTpkt& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, MultipleRSUsRTpkt& obj) {obj.parsimUnpack(b);}


#endif // ifndef _PREVIOUS_VRTANDPKT_M_H_

