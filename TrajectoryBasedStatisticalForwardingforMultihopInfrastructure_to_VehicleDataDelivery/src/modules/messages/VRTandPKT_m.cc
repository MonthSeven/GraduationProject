//
// Generated file, do not edit! Created by nedtool 4.6 from src/modules/messages/VRTandPKT.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "VRTandPKT_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

vrtStruct::vrtStruct()
{
    nodeMacAdd = 0;
    nodeID = 0;
    nodeSpeed = 0;
    nodeEDD_Value = 0;
    lastUpdateTime = 0;
    NumHopsToDst = 0;
    rtTTL = 0.3;
}

void doPacking(cCommBuffer *b, vrtStruct& a)
{
    doPacking(b,a.nodeMacAdd);
    doPacking(b,a.nodeID);
    doPacking(b,a.nodePosition);
    doPacking(b,a.nodeSpeed);
    doPacking(b,a.nodeEDD_Value);
    doPacking(b,a.lastUpdateTime);
    doPacking(b,a.NumHopsToDst);
    doPacking(b,a.rtTTL);
}

void doUnpacking(cCommBuffer *b, vrtStruct& a)
{
    doUnpacking(b,a.nodeMacAdd);
    doUnpacking(b,a.nodeID);
    doUnpacking(b,a.nodePosition);
    doUnpacking(b,a.nodeSpeed);
    doUnpacking(b,a.nodeEDD_Value);
    doUnpacking(b,a.lastUpdateTime);
    doUnpacking(b,a.NumHopsToDst);
    doUnpacking(b,a.rtTTL);
}

class vrtStructDescriptor : public cClassDescriptor
{
  public:
    vrtStructDescriptor();
    virtual ~vrtStructDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(vrtStructDescriptor);

vrtStructDescriptor::vrtStructDescriptor() : cClassDescriptor("vrtStruct", "")
{
}

vrtStructDescriptor::~vrtStructDescriptor()
{
}

bool vrtStructDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<vrtStruct *>(obj)!=NULL;
}

const char *vrtStructDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int vrtStructDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount(object) : 8;
}

unsigned int vrtStructDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *vrtStructDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "nodeMacAdd",
        "nodeID",
        "nodePosition",
        "nodeSpeed",
        "nodeEDD_Value",
        "lastUpdateTime",
        "NumHopsToDst",
        "rtTTL",
    };
    return (field>=0 && field<8) ? fieldNames[field] : NULL;
}

int vrtStructDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeMacAdd")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeID")==0) return base+1;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodePosition")==0) return base+2;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeSpeed")==0) return base+3;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeEDD_Value")==0) return base+4;
    if (fieldName[0]=='l' && strcmp(fieldName, "lastUpdateTime")==0) return base+5;
    if (fieldName[0]=='N' && strcmp(fieldName, "NumHopsToDst")==0) return base+6;
    if (fieldName[0]=='r' && strcmp(fieldName, "rtTTL")==0) return base+7;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *vrtStructDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "string",
        "Coord",
        "double",
        "double",
        "simtime_t",
        "int",
        "simtime_t",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : NULL;
}

const char *vrtStructDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int vrtStructDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    vrtStruct *pp = (vrtStruct *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string vrtStructDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    vrtStruct *pp = (vrtStruct *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->nodeMacAdd);
        case 1: return oppstring2string(pp->nodeID);
        case 2: {std::stringstream out; out << pp->nodePosition; return out.str();}
        case 3: return double2string(pp->nodeSpeed);
        case 4: return double2string(pp->nodeEDD_Value);
        case 5: return double2string(pp->lastUpdateTime);
        case 6: return long2string(pp->NumHopsToDst);
        case 7: return double2string(pp->rtTTL);
        default: return "";
    }
}

bool vrtStructDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    vrtStruct *pp = (vrtStruct *)object; (void)pp;
    switch (field) {
        case 0: pp->nodeMacAdd = string2long(value); return true;
        case 1: pp->nodeID = (value); return true;
        case 3: pp->nodeSpeed = string2double(value); return true;
        case 4: pp->nodeEDD_Value = string2double(value); return true;
        case 5: pp->lastUpdateTime = string2double(value); return true;
        case 6: pp->NumHopsToDst = string2long(value); return true;
        case 7: pp->rtTTL = string2double(value); return true;
        default: return false;
    }
}

const char *vrtStructDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 2: return opp_typename(typeid(Coord));
        default: return NULL;
    };
}

void *vrtStructDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    vrtStruct *pp = (vrtStruct *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->nodePosition); break;
        default: return NULL;
    }
}

Register_Class(multipleRSUsRTpkt);

multipleRSUsRTpkt::multipleRSUsRTpkt(const char *name, int kind) : ::cPacket(name,kind)
{
    this->priority_var = 0;
    this->pktSourceID_var = 0;
    this->seqNumber_var = 0;
    this->pktDestinationID_var = 0;
    this->pktDestinationMac_var = 0;
    this->pktActualsrcID_var = 0;
    this->pktActualsrcMac_var = 0;
    this->pktActualdestMac_var = 0;
    this->pktGenerationTime_var = 0;
    this->pktlastReceiveTime_var = 0;
    this->DestArrivalTime_var = 0;
    this->pktTTL_var = 0;
    this->channelNumber_var = 0;
    this->rtsenderMacAdd_var = 0;
    this->rtsenderID_var = 0;
    this->rtsenderSpeed_var = 0;
    this->rtsendingTime_var = 0;
    this->myid_var = 0;
}

multipleRSUsRTpkt::multipleRSUsRTpkt(const multipleRSUsRTpkt& other) : ::cPacket(other)
{
    copy(other);
}

multipleRSUsRTpkt::~multipleRSUsRTpkt()
{
}

multipleRSUsRTpkt& multipleRSUsRTpkt::operator=(const multipleRSUsRTpkt& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void multipleRSUsRTpkt::copy(const multipleRSUsRTpkt& other)
{
    this->priority_var = other.priority_var;
    this->pktSourceID_var = other.pktSourceID_var;
    this->seqNumber_var = other.seqNumber_var;
    this->pktDestinationID_var = other.pktDestinationID_var;
    this->pktDestinationMac_var = other.pktDestinationMac_var;
    this->pktActualsrcID_var = other.pktActualsrcID_var;
    this->pktActualsrcMac_var = other.pktActualsrcMac_var;
    this->pktActualdestMac_var = other.pktActualdestMac_var;
    this->pktGenerationTime_var = other.pktGenerationTime_var;
    this->pktlastReceiveTime_var = other.pktlastReceiveTime_var;
    this->DestArrivalTime_var = other.DestArrivalTime_var;
    this->pktTTL_var = other.pktTTL_var;
    this->channelNumber_var = other.channelNumber_var;
    this->rtsenderMacAdd_var = other.rtsenderMacAdd_var;
    this->rtsenderID_var = other.rtsenderID_var;
    this->rtsenderPosition_var = other.rtsenderPosition_var;
    this->rtsenderSpeed_var = other.rtsenderSpeed_var;
    this->rtsendingTime_var = other.rtsendingTime_var;
    this->rtmyEDDs_var = other.rtmyEDDs_var;
    this->rtrouting_table_var = other.rtrouting_table_var;
    this->myid_var = other.myid_var;
}

void multipleRSUsRTpkt::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->priority_var);
    doPacking(b,this->pktSourceID_var);
    doPacking(b,this->seqNumber_var);
    doPacking(b,this->pktDestinationID_var);
    doPacking(b,this->pktDestinationMac_var);
    doPacking(b,this->pktActualsrcID_var);
    doPacking(b,this->pktActualsrcMac_var);
    doPacking(b,this->pktActualdestMac_var);
    doPacking(b,this->pktGenerationTime_var);
    doPacking(b,this->pktlastReceiveTime_var);
    doPacking(b,this->DestArrivalTime_var);
    doPacking(b,this->pktTTL_var);
    doPacking(b,this->channelNumber_var);
    doPacking(b,this->rtsenderMacAdd_var);
    doPacking(b,this->rtsenderID_var);
    doPacking(b,this->rtsenderPosition_var);
    doPacking(b,this->rtsenderSpeed_var);
    doPacking(b,this->rtsendingTime_var);
    doPacking(b,this->rtmyEDDs_var);
    doPacking(b,this->rtrouting_table_var);
    doPacking(b,this->myid_var);
}

void multipleRSUsRTpkt::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->priority_var);
    doUnpacking(b,this->pktSourceID_var);
    doUnpacking(b,this->seqNumber_var);
    doUnpacking(b,this->pktDestinationID_var);
    doUnpacking(b,this->pktDestinationMac_var);
    doUnpacking(b,this->pktActualsrcID_var);
    doUnpacking(b,this->pktActualsrcMac_var);
    doUnpacking(b,this->pktActualdestMac_var);
    doUnpacking(b,this->pktGenerationTime_var);
    doUnpacking(b,this->pktlastReceiveTime_var);
    doUnpacking(b,this->DestArrivalTime_var);
    doUnpacking(b,this->pktTTL_var);
    doUnpacking(b,this->channelNumber_var);
    doUnpacking(b,this->rtsenderMacAdd_var);
    doUnpacking(b,this->rtsenderID_var);
    doUnpacking(b,this->rtsenderPosition_var);
    doUnpacking(b,this->rtsenderSpeed_var);
    doUnpacking(b,this->rtsendingTime_var);
    doUnpacking(b,this->rtmyEDDs_var);
    doUnpacking(b,this->rtrouting_table_var);
    doUnpacking(b,this->myid_var);
}

int multipleRSUsRTpkt::getPriority() const
{
    return priority_var;
}

void multipleRSUsRTpkt::setPriority(int priority)
{
    this->priority_var = priority;
}

const char * multipleRSUsRTpkt::getPktSourceID() const
{
    return pktSourceID_var.c_str();
}

void multipleRSUsRTpkt::setPktSourceID(const char * pktSourceID)
{
    this->pktSourceID_var = pktSourceID;
}

int multipleRSUsRTpkt::getSeqNumber() const
{
    return seqNumber_var;
}

void multipleRSUsRTpkt::setSeqNumber(int seqNumber)
{
    this->seqNumber_var = seqNumber;
}

const char * multipleRSUsRTpkt::getPktDestinationID() const
{
    return pktDestinationID_var.c_str();
}

void multipleRSUsRTpkt::setPktDestinationID(const char * pktDestinationID)
{
    this->pktDestinationID_var = pktDestinationID;
}

int multipleRSUsRTpkt::getPktDestinationMac() const
{
    return pktDestinationMac_var;
}

void multipleRSUsRTpkt::setPktDestinationMac(int pktDestinationMac)
{
    this->pktDestinationMac_var = pktDestinationMac;
}

const char * multipleRSUsRTpkt::getPktActualsrcID() const
{
    return pktActualsrcID_var.c_str();
}

void multipleRSUsRTpkt::setPktActualsrcID(const char * pktActualsrcID)
{
    this->pktActualsrcID_var = pktActualsrcID;
}

int multipleRSUsRTpkt::getPktActualsrcMac() const
{
    return pktActualsrcMac_var;
}

void multipleRSUsRTpkt::setPktActualsrcMac(int pktActualsrcMac)
{
    this->pktActualsrcMac_var = pktActualsrcMac;
}

int multipleRSUsRTpkt::getPktActualdestMac() const
{
    return pktActualdestMac_var;
}

void multipleRSUsRTpkt::setPktActualdestMac(int pktActualdestMac)
{
    this->pktActualdestMac_var = pktActualdestMac;
}

simtime_t multipleRSUsRTpkt::getPktGenerationTime() const
{
    return pktGenerationTime_var;
}

void multipleRSUsRTpkt::setPktGenerationTime(simtime_t pktGenerationTime)
{
    this->pktGenerationTime_var = pktGenerationTime;
}

simtime_t multipleRSUsRTpkt::getPktlastReceiveTime() const
{
    return pktlastReceiveTime_var;
}

void multipleRSUsRTpkt::setPktlastReceiveTime(simtime_t pktlastReceiveTime)
{
    this->pktlastReceiveTime_var = pktlastReceiveTime;
}

simtime_t multipleRSUsRTpkt::getDestArrivalTime() const
{
    return DestArrivalTime_var;
}

void multipleRSUsRTpkt::setDestArrivalTime(simtime_t DestArrivalTime)
{
    this->DestArrivalTime_var = DestArrivalTime;
}

simtime_t multipleRSUsRTpkt::getPktTTL() const
{
    return pktTTL_var;
}

void multipleRSUsRTpkt::setPktTTL(simtime_t pktTTL)
{
    this->pktTTL_var = pktTTL;
}

int multipleRSUsRTpkt::getChannelNumber() const
{
    return channelNumber_var;
}

void multipleRSUsRTpkt::setChannelNumber(int channelNumber)
{
    this->channelNumber_var = channelNumber;
}

int multipleRSUsRTpkt::getRtsenderMacAdd() const
{
    return rtsenderMacAdd_var;
}

void multipleRSUsRTpkt::setRtsenderMacAdd(int rtsenderMacAdd)
{
    this->rtsenderMacAdd_var = rtsenderMacAdd;
}

const char * multipleRSUsRTpkt::getRtsenderID() const
{
    return rtsenderID_var.c_str();
}

void multipleRSUsRTpkt::setRtsenderID(const char * rtsenderID)
{
    this->rtsenderID_var = rtsenderID;
}

Coord& multipleRSUsRTpkt::getRtsenderPosition()
{
    return rtsenderPosition_var;
}

void multipleRSUsRTpkt::setRtsenderPosition(const Coord& rtsenderPosition)
{
    this->rtsenderPosition_var = rtsenderPosition;
}

double multipleRSUsRTpkt::getRtsenderSpeed() const
{
    return rtsenderSpeed_var;
}

void multipleRSUsRTpkt::setRtsenderSpeed(double rtsenderSpeed)
{
    this->rtsenderSpeed_var = rtsenderSpeed;
}

simtime_t multipleRSUsRTpkt::getRtsendingTime() const
{
    return rtsendingTime_var;
}

void multipleRSUsRTpkt::setRtsendingTime(simtime_t rtsendingTime)
{
    this->rtsendingTime_var = rtsendingTime;
}

senderEDDs& multipleRSUsRTpkt::getRtmyEDDs()
{
    return rtmyEDDs_var;
}

void multipleRSUsRTpkt::setRtmyEDDs(const senderEDDs& rtmyEDDs)
{
    this->rtmyEDDs_var = rtmyEDDs;
}

multRSUsRt& multipleRSUsRTpkt::getRtrouting_table()
{
    return rtrouting_table_var;
}

void multipleRSUsRTpkt::setRtrouting_table(const multRSUsRt& rtrouting_table)
{
    this->rtrouting_table_var = rtrouting_table;
}

const char * multipleRSUsRTpkt::getMyid() const
{
    return myid_var.c_str();
}

void multipleRSUsRTpkt::setMyid(const char * myid)
{
    this->myid_var = myid;
}

class multipleRSUsRTpktDescriptor : public cClassDescriptor
{
  public:
    multipleRSUsRTpktDescriptor();
    virtual ~multipleRSUsRTpktDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(multipleRSUsRTpktDescriptor);

multipleRSUsRTpktDescriptor::multipleRSUsRTpktDescriptor() : cClassDescriptor("multipleRSUsRTpkt", "cPacket")
{
}

multipleRSUsRTpktDescriptor::~multipleRSUsRTpktDescriptor()
{
}

bool multipleRSUsRTpktDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<multipleRSUsRTpkt *>(obj)!=NULL;
}

const char *multipleRSUsRTpktDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int multipleRSUsRTpktDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 21+basedesc->getFieldCount(object) : 21;
}

unsigned int multipleRSUsRTpktDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<21) ? fieldTypeFlags[field] : 0;
}

const char *multipleRSUsRTpktDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "priority",
        "pktSourceID",
        "seqNumber",
        "pktDestinationID",
        "pktDestinationMac",
        "pktActualsrcID",
        "pktActualsrcMac",
        "pktActualdestMac",
        "pktGenerationTime",
        "pktlastReceiveTime",
        "DestArrivalTime",
        "pktTTL",
        "channelNumber",
        "rtsenderMacAdd",
        "rtsenderID",
        "rtsenderPosition",
        "rtsenderSpeed",
        "rtsendingTime",
        "rtmyEDDs",
        "rtrouting_table",
        "myid",
    };
    return (field>=0 && field<21) ? fieldNames[field] : NULL;
}

int multipleRSUsRTpktDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "priority")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "pktSourceID")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "seqNumber")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "pktDestinationID")==0) return base+3;
    if (fieldName[0]=='p' && strcmp(fieldName, "pktDestinationMac")==0) return base+4;
    if (fieldName[0]=='p' && strcmp(fieldName, "pktActualsrcID")==0) return base+5;
    if (fieldName[0]=='p' && strcmp(fieldName, "pktActualsrcMac")==0) return base+6;
    if (fieldName[0]=='p' && strcmp(fieldName, "pktActualdestMac")==0) return base+7;
    if (fieldName[0]=='p' && strcmp(fieldName, "pktGenerationTime")==0) return base+8;
    if (fieldName[0]=='p' && strcmp(fieldName, "pktlastReceiveTime")==0) return base+9;
    if (fieldName[0]=='D' && strcmp(fieldName, "DestArrivalTime")==0) return base+10;
    if (fieldName[0]=='p' && strcmp(fieldName, "pktTTL")==0) return base+11;
    if (fieldName[0]=='c' && strcmp(fieldName, "channelNumber")==0) return base+12;
    if (fieldName[0]=='r' && strcmp(fieldName, "rtsenderMacAdd")==0) return base+13;
    if (fieldName[0]=='r' && strcmp(fieldName, "rtsenderID")==0) return base+14;
    if (fieldName[0]=='r' && strcmp(fieldName, "rtsenderPosition")==0) return base+15;
    if (fieldName[0]=='r' && strcmp(fieldName, "rtsenderSpeed")==0) return base+16;
    if (fieldName[0]=='r' && strcmp(fieldName, "rtsendingTime")==0) return base+17;
    if (fieldName[0]=='r' && strcmp(fieldName, "rtmyEDDs")==0) return base+18;
    if (fieldName[0]=='r' && strcmp(fieldName, "rtrouting_table")==0) return base+19;
    if (fieldName[0]=='m' && strcmp(fieldName, "myid")==0) return base+20;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *multipleRSUsRTpktDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "string",
        "int",
        "string",
        "int",
        "string",
        "int",
        "int",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "int",
        "int",
        "string",
        "Coord",
        "double",
        "simtime_t",
        "senderEDDs",
        "multRSUsRt",
        "string",
    };
    return (field>=0 && field<21) ? fieldTypeStrings[field] : NULL;
}

const char *multipleRSUsRTpktDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int multipleRSUsRTpktDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    multipleRSUsRTpkt *pp = (multipleRSUsRTpkt *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string multipleRSUsRTpktDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    multipleRSUsRTpkt *pp = (multipleRSUsRTpkt *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getPriority());
        case 1: return oppstring2string(pp->getPktSourceID());
        case 2: return long2string(pp->getSeqNumber());
        case 3: return oppstring2string(pp->getPktDestinationID());
        case 4: return long2string(pp->getPktDestinationMac());
        case 5: return oppstring2string(pp->getPktActualsrcID());
        case 6: return long2string(pp->getPktActualsrcMac());
        case 7: return long2string(pp->getPktActualdestMac());
        case 8: return double2string(pp->getPktGenerationTime());
        case 9: return double2string(pp->getPktlastReceiveTime());
        case 10: return double2string(pp->getDestArrivalTime());
        case 11: return double2string(pp->getPktTTL());
        case 12: return long2string(pp->getChannelNumber());
        case 13: return long2string(pp->getRtsenderMacAdd());
        case 14: return oppstring2string(pp->getRtsenderID());
        case 15: {std::stringstream out; out << pp->getRtsenderPosition(); return out.str();}
        case 16: return double2string(pp->getRtsenderSpeed());
        case 17: return double2string(pp->getRtsendingTime());
        case 18: {std::stringstream out; out << pp->getRtmyEDDs(); return out.str();}
        case 19: {std::stringstream out; out << pp->getRtrouting_table(); return out.str();}
        case 20: return oppstring2string(pp->getMyid());
        default: return "";
    }
}

bool multipleRSUsRTpktDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    multipleRSUsRTpkt *pp = (multipleRSUsRTpkt *)object; (void)pp;
    switch (field) {
        case 0: pp->setPriority(string2long(value)); return true;
        case 1: pp->setPktSourceID((value)); return true;
        case 2: pp->setSeqNumber(string2long(value)); return true;
        case 3: pp->setPktDestinationID((value)); return true;
        case 4: pp->setPktDestinationMac(string2long(value)); return true;
        case 5: pp->setPktActualsrcID((value)); return true;
        case 6: pp->setPktActualsrcMac(string2long(value)); return true;
        case 7: pp->setPktActualdestMac(string2long(value)); return true;
        case 8: pp->setPktGenerationTime(string2double(value)); return true;
        case 9: pp->setPktlastReceiveTime(string2double(value)); return true;
        case 10: pp->setDestArrivalTime(string2double(value)); return true;
        case 11: pp->setPktTTL(string2double(value)); return true;
        case 12: pp->setChannelNumber(string2long(value)); return true;
        case 13: pp->setRtsenderMacAdd(string2long(value)); return true;
        case 14: pp->setRtsenderID((value)); return true;
        case 16: pp->setRtsenderSpeed(string2double(value)); return true;
        case 17: pp->setRtsendingTime(string2double(value)); return true;
        case 20: pp->setMyid((value)); return true;
        default: return false;
    }
}

const char *multipleRSUsRTpktDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 15: return opp_typename(typeid(Coord));
        case 18: return opp_typename(typeid(senderEDDs));
        case 19: return opp_typename(typeid(multRSUsRt));
        default: return NULL;
    };
}

void *multipleRSUsRTpktDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    multipleRSUsRTpkt *pp = (multipleRSUsRTpkt *)object; (void)pp;
    switch (field) {
        case 15: return (void *)(&pp->getRtsenderPosition()); break;
        case 18: return (void *)(&pp->getRtmyEDDs()); break;
        case 19: return (void *)(&pp->getRtrouting_table()); break;
        default: return NULL;
    }
}


