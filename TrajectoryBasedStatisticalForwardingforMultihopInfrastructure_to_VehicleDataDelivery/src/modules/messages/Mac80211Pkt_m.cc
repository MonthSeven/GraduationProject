//
// Generated file, do not edit! Created by nedtool 4.6 from src/modules/messages/Mac80211Pkt.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "Mac80211Pkt_m.h"

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

Register_Class(Mac80211Pkt);

Mac80211Pkt::Mac80211Pkt(const char *name, int kind) : ::MacPkt(name,kind)
{
    this->sendeMac_var = 0;
    this->receiverMac_var = 0;
    this->sequenceNumber_var = 0;
    this->sendingTime_var = 0;
    this->sequenceControl_var = 0;
    this->retry_var = 0;
    this->duration_var = 0;
}

Mac80211Pkt::Mac80211Pkt(const Mac80211Pkt& other) : ::MacPkt(other)
{
    copy(other);
}

Mac80211Pkt::~Mac80211Pkt()
{
}

Mac80211Pkt& Mac80211Pkt::operator=(const Mac80211Pkt& other)
{
    if (this==&other) return *this;
    ::MacPkt::operator=(other);
    copy(other);
    return *this;
}

void Mac80211Pkt::copy(const Mac80211Pkt& other)
{
    this->sendeMac_var = other.sendeMac_var;
    this->receiverMac_var = other.receiverMac_var;
    this->sequenceNumber_var = other.sequenceNumber_var;
    this->sendingTime_var = other.sendingTime_var;
    this->sequenceControl_var = other.sequenceControl_var;
    this->retry_var = other.retry_var;
    this->duration_var = other.duration_var;
}

void Mac80211Pkt::parsimPack(cCommBuffer *b)
{
    ::MacPkt::parsimPack(b);
    doPacking(b,this->sendeMac_var);
    doPacking(b,this->receiverMac_var);
    doPacking(b,this->sequenceNumber_var);
    doPacking(b,this->sendingTime_var);
    doPacking(b,this->sequenceControl_var);
    doPacking(b,this->retry_var);
    doPacking(b,this->duration_var);
}

void Mac80211Pkt::parsimUnpack(cCommBuffer *b)
{
    ::MacPkt::parsimUnpack(b);
    doUnpacking(b,this->sendeMac_var);
    doUnpacking(b,this->receiverMac_var);
    doUnpacking(b,this->sequenceNumber_var);
    doUnpacking(b,this->sendingTime_var);
    doUnpacking(b,this->sequenceControl_var);
    doUnpacking(b,this->retry_var);
    doUnpacking(b,this->duration_var);
}

int Mac80211Pkt::getSendeMac() const
{
    return sendeMac_var;
}

void Mac80211Pkt::setSendeMac(int sendeMac)
{
    this->sendeMac_var = sendeMac;
}

int Mac80211Pkt::getReceiverMac() const
{
    return receiverMac_var;
}

void Mac80211Pkt::setReceiverMac(int receiverMac)
{
    this->receiverMac_var = receiverMac;
}

int Mac80211Pkt::getSequenceNumber() const
{
    return sequenceNumber_var;
}

void Mac80211Pkt::setSequenceNumber(int sequenceNumber)
{
    this->sequenceNumber_var = sequenceNumber;
}

int Mac80211Pkt::getSendingTime() const
{
    return sendingTime_var;
}

void Mac80211Pkt::setSendingTime(int sendingTime)
{
    this->sendingTime_var = sendingTime;
}

int Mac80211Pkt::getSequenceControl() const
{
    return sequenceControl_var;
}

void Mac80211Pkt::setSequenceControl(int sequenceControl)
{
    this->sequenceControl_var = sequenceControl;
}

bool Mac80211Pkt::getRetry() const
{
    return retry_var;
}

void Mac80211Pkt::setRetry(bool retry)
{
    this->retry_var = retry;
}

simtime_t Mac80211Pkt::getDuration() const
{
    return duration_var;
}

void Mac80211Pkt::setDuration(simtime_t duration)
{
    this->duration_var = duration;
}

class Mac80211PktDescriptor : public cClassDescriptor
{
  public:
    Mac80211PktDescriptor();
    virtual ~Mac80211PktDescriptor();

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

Register_ClassDescriptor(Mac80211PktDescriptor);

Mac80211PktDescriptor::Mac80211PktDescriptor() : cClassDescriptor("Mac80211Pkt", "MacPkt")
{
}

Mac80211PktDescriptor::~Mac80211PktDescriptor()
{
}

bool Mac80211PktDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Mac80211Pkt *>(obj)!=NULL;
}

const char *Mac80211PktDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int Mac80211PktDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int Mac80211PktDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *Mac80211PktDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "sendeMac",
        "receiverMac",
        "sequenceNumber",
        "sendingTime",
        "sequenceControl",
        "retry",
        "duration",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int Mac80211PktDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sendeMac")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "receiverMac")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "sequenceNumber")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "sendingTime")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "sequenceControl")==0) return base+4;
    if (fieldName[0]=='r' && strcmp(fieldName, "retry")==0) return base+5;
    if (fieldName[0]=='d' && strcmp(fieldName, "duration")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *Mac80211PktDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
        "bool",
        "simtime_t",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *Mac80211PktDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int Mac80211PktDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Mac80211Pkt *pp = (Mac80211Pkt *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string Mac80211PktDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Mac80211Pkt *pp = (Mac80211Pkt *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSendeMac());
        case 1: return long2string(pp->getReceiverMac());
        case 2: return long2string(pp->getSequenceNumber());
        case 3: return long2string(pp->getSendingTime());
        case 4: return long2string(pp->getSequenceControl());
        case 5: return bool2string(pp->getRetry());
        case 6: return double2string(pp->getDuration());
        default: return "";
    }
}

bool Mac80211PktDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Mac80211Pkt *pp = (Mac80211Pkt *)object; (void)pp;
    switch (field) {
        case 0: pp->setSendeMac(string2long(value)); return true;
        case 1: pp->setReceiverMac(string2long(value)); return true;
        case 2: pp->setSequenceNumber(string2long(value)); return true;
        case 3: pp->setSendingTime(string2long(value)); return true;
        case 4: pp->setSequenceControl(string2long(value)); return true;
        case 5: pp->setRetry(string2bool(value)); return true;
        case 6: pp->setDuration(string2double(value)); return true;
        default: return false;
    }
}

const char *Mac80211PktDescriptor::getFieldStructName(void *object, int field) const
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

void *Mac80211PktDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Mac80211Pkt *pp = (Mac80211Pkt *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


