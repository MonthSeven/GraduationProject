//
// Generated file, do not edit! Created by nedtool 4.6 from src/modules/messages/packetToSend.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "packetToSend_m.h"

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

Register_Class(pkt_Send);

pkt_Send::pkt_Send(const char *name, int kind) : ::cPacket(name,kind)
{
    this->sourceID_var = 0;
    this->seqNumber_var = 0;
    this->destinationID_var = 0;
    this->destinationMac_var = 0;
    this->actualsrcID_var = 0;
    this->actualsrcMac_var = 0;
    this->actualdestMac_var = 0;
    this->pktGenerationTime_var = 0;
    this->lastReceiveTime_var = 0;
    this->DestArrivalTime_var = 0;
    this->ttl_var = 0;
    this->priority_var = 1;
}

pkt_Send::pkt_Send(const pkt_Send& other) : ::cPacket(other)
{
    copy(other);
}

pkt_Send::~pkt_Send()
{
}

pkt_Send& pkt_Send::operator=(const pkt_Send& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void pkt_Send::copy(const pkt_Send& other)
{
    this->sourceID_var = other.sourceID_var;
    this->seqNumber_var = other.seqNumber_var;
    this->destinationID_var = other.destinationID_var;
    this->destinationMac_var = other.destinationMac_var;
    this->actualsrcID_var = other.actualsrcID_var;
    this->actualsrcMac_var = other.actualsrcMac_var;
    this->actualdestMac_var = other.actualdestMac_var;
    this->pktGenerationTime_var = other.pktGenerationTime_var;
    this->lastReceiveTime_var = other.lastReceiveTime_var;
    this->DestArrivalTime_var = other.DestArrivalTime_var;
    this->ttl_var = other.ttl_var;
    this->priority_var = other.priority_var;
}

void pkt_Send::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->sourceID_var);
    doPacking(b,this->seqNumber_var);
    doPacking(b,this->destinationID_var);
    doPacking(b,this->destinationMac_var);
    doPacking(b,this->actualsrcID_var);
    doPacking(b,this->actualsrcMac_var);
    doPacking(b,this->actualdestMac_var);
    doPacking(b,this->pktGenerationTime_var);
    doPacking(b,this->lastReceiveTime_var);
    doPacking(b,this->DestArrivalTime_var);
    doPacking(b,this->ttl_var);
    doPacking(b,this->priority_var);
}

void pkt_Send::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->sourceID_var);
    doUnpacking(b,this->seqNumber_var);
    doUnpacking(b,this->destinationID_var);
    doUnpacking(b,this->destinationMac_var);
    doUnpacking(b,this->actualsrcID_var);
    doUnpacking(b,this->actualsrcMac_var);
    doUnpacking(b,this->actualdestMac_var);
    doUnpacking(b,this->pktGenerationTime_var);
    doUnpacking(b,this->lastReceiveTime_var);
    doUnpacking(b,this->DestArrivalTime_var);
    doUnpacking(b,this->ttl_var);
    doUnpacking(b,this->priority_var);
}

const char * pkt_Send::getSourceID() const
{
    return sourceID_var.c_str();
}

void pkt_Send::setSourceID(const char * sourceID)
{
    this->sourceID_var = sourceID;
}

int pkt_Send::getSeqNumber() const
{
    return seqNumber_var;
}

void pkt_Send::setSeqNumber(int seqNumber)
{
    this->seqNumber_var = seqNumber;
}

const char * pkt_Send::getDestinationID() const
{
    return destinationID_var.c_str();
}

void pkt_Send::setDestinationID(const char * destinationID)
{
    this->destinationID_var = destinationID;
}

int pkt_Send::getDestinationMac() const
{
    return destinationMac_var;
}

void pkt_Send::setDestinationMac(int destinationMac)
{
    this->destinationMac_var = destinationMac;
}

const char * pkt_Send::getActualsrcID() const
{
    return actualsrcID_var.c_str();
}

void pkt_Send::setActualsrcID(const char * actualsrcID)
{
    this->actualsrcID_var = actualsrcID;
}

int pkt_Send::getActualsrcMac() const
{
    return actualsrcMac_var;
}

void pkt_Send::setActualsrcMac(int actualsrcMac)
{
    this->actualsrcMac_var = actualsrcMac;
}

int pkt_Send::getActualdestMac() const
{
    return actualdestMac_var;
}

void pkt_Send::setActualdestMac(int actualdestMac)
{
    this->actualdestMac_var = actualdestMac;
}

simtime_t pkt_Send::getPktGenerationTime() const
{
    return pktGenerationTime_var;
}

void pkt_Send::setPktGenerationTime(simtime_t pktGenerationTime)
{
    this->pktGenerationTime_var = pktGenerationTime;
}

simtime_t pkt_Send::getLastReceiveTime() const
{
    return lastReceiveTime_var;
}

void pkt_Send::setLastReceiveTime(simtime_t lastReceiveTime)
{
    this->lastReceiveTime_var = lastReceiveTime;
}

simtime_t pkt_Send::getDestArrivalTime() const
{
    return DestArrivalTime_var;
}

void pkt_Send::setDestArrivalTime(simtime_t DestArrivalTime)
{
    this->DestArrivalTime_var = DestArrivalTime;
}

simtime_t pkt_Send::getTtl() const
{
    return ttl_var;
}

void pkt_Send::setTtl(simtime_t ttl)
{
    this->ttl_var = ttl;
}

int pkt_Send::getPriority() const
{
    return priority_var;
}

void pkt_Send::setPriority(int priority)
{
    this->priority_var = priority;
}

class pkt_SendDescriptor : public cClassDescriptor
{
  public:
    pkt_SendDescriptor();
    virtual ~pkt_SendDescriptor();

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

Register_ClassDescriptor(pkt_SendDescriptor);

pkt_SendDescriptor::pkt_SendDescriptor() : cClassDescriptor("pkt_Send", "cPacket")
{
}

pkt_SendDescriptor::~pkt_SendDescriptor()
{
}

bool pkt_SendDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<pkt_Send *>(obj)!=NULL;
}

const char *pkt_SendDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int pkt_SendDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 12+basedesc->getFieldCount(object) : 12;
}

unsigned int pkt_SendDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<12) ? fieldTypeFlags[field] : 0;
}

const char *pkt_SendDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "sourceID",
        "seqNumber",
        "destinationID",
        "destinationMac",
        "actualsrcID",
        "actualsrcMac",
        "actualdestMac",
        "pktGenerationTime",
        "lastReceiveTime",
        "DestArrivalTime",
        "ttl",
        "priority",
    };
    return (field>=0 && field<12) ? fieldNames[field] : NULL;
}

int pkt_SendDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceID")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "seqNumber")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationID")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationMac")==0) return base+3;
    if (fieldName[0]=='a' && strcmp(fieldName, "actualsrcID")==0) return base+4;
    if (fieldName[0]=='a' && strcmp(fieldName, "actualsrcMac")==0) return base+5;
    if (fieldName[0]=='a' && strcmp(fieldName, "actualdestMac")==0) return base+6;
    if (fieldName[0]=='p' && strcmp(fieldName, "pktGenerationTime")==0) return base+7;
    if (fieldName[0]=='l' && strcmp(fieldName, "lastReceiveTime")==0) return base+8;
    if (fieldName[0]=='D' && strcmp(fieldName, "DestArrivalTime")==0) return base+9;
    if (fieldName[0]=='t' && strcmp(fieldName, "ttl")==0) return base+10;
    if (fieldName[0]=='p' && strcmp(fieldName, "priority")==0) return base+11;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *pkt_SendDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
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
    };
    return (field>=0 && field<12) ? fieldTypeStrings[field] : NULL;
}

const char *pkt_SendDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int pkt_SendDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    pkt_Send *pp = (pkt_Send *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string pkt_SendDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    pkt_Send *pp = (pkt_Send *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getSourceID());
        case 1: return long2string(pp->getSeqNumber());
        case 2: return oppstring2string(pp->getDestinationID());
        case 3: return long2string(pp->getDestinationMac());
        case 4: return oppstring2string(pp->getActualsrcID());
        case 5: return long2string(pp->getActualsrcMac());
        case 6: return long2string(pp->getActualdestMac());
        case 7: return double2string(pp->getPktGenerationTime());
        case 8: return double2string(pp->getLastReceiveTime());
        case 9: return double2string(pp->getDestArrivalTime());
        case 10: return double2string(pp->getTtl());
        case 11: return long2string(pp->getPriority());
        default: return "";
    }
}

bool pkt_SendDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    pkt_Send *pp = (pkt_Send *)object; (void)pp;
    switch (field) {
        case 0: pp->setSourceID((value)); return true;
        case 1: pp->setSeqNumber(string2long(value)); return true;
        case 2: pp->setDestinationID((value)); return true;
        case 3: pp->setDestinationMac(string2long(value)); return true;
        case 4: pp->setActualsrcID((value)); return true;
        case 5: pp->setActualsrcMac(string2long(value)); return true;
        case 6: pp->setActualdestMac(string2long(value)); return true;
        case 7: pp->setPktGenerationTime(string2double(value)); return true;
        case 8: pp->setLastReceiveTime(string2double(value)); return true;
        case 9: pp->setDestArrivalTime(string2double(value)); return true;
        case 10: pp->setTtl(string2double(value)); return true;
        case 11: pp->setPriority(string2long(value)); return true;
        default: return false;
    }
}

const char *pkt_SendDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *pkt_SendDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    pkt_Send *pp = (pkt_Send *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


