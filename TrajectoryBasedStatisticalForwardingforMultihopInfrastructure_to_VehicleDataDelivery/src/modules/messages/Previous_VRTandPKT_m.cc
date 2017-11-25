//
// Generated file, do not edit! Created by nedtool 4.6 from src/modules/messages/Previous_VRTandPKT.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "Previous_VRTandPKT_m.h"

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

vrtStruct_Prev::vrtStruct_Prev()
{
    nodeMacAdd = 0;
    nodeID = 0;
    nodeSpeed = 0;
    nodeEDD_Value = 0;
    lastUpdateTime = 0;
    NumHopsToDst = 0;
    rtTTL = 0.3;
}

void doPacking(cCommBuffer *b, vrtStruct_Prev& a)
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

void doUnpacking(cCommBuffer *b, vrtStruct_Prev& a)
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

class vrtStruct_PrevDescriptor : public cClassDescriptor
{
  public:
    vrtStruct_PrevDescriptor();
    virtual ~vrtStruct_PrevDescriptor();

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

Register_ClassDescriptor(vrtStruct_PrevDescriptor);

vrtStruct_PrevDescriptor::vrtStruct_PrevDescriptor() : cClassDescriptor("vrtStruct_Prev", "")
{
}

vrtStruct_PrevDescriptor::~vrtStruct_PrevDescriptor()
{
}

bool vrtStruct_PrevDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<vrtStruct_Prev *>(obj)!=NULL;
}

const char *vrtStruct_PrevDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int vrtStruct_PrevDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount(object) : 8;
}

unsigned int vrtStruct_PrevDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *vrtStruct_PrevDescriptor::getFieldName(void *object, int field) const
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

int vrtStruct_PrevDescriptor::findField(void *object, const char *fieldName) const
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

const char *vrtStruct_PrevDescriptor::getFieldTypeString(void *object, int field) const
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

const char *vrtStruct_PrevDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int vrtStruct_PrevDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    vrtStruct_Prev *pp = (vrtStruct_Prev *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string vrtStruct_PrevDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    vrtStruct_Prev *pp = (vrtStruct_Prev *)object; (void)pp;
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

bool vrtStruct_PrevDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    vrtStruct_Prev *pp = (vrtStruct_Prev *)object; (void)pp;
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

const char *vrtStruct_PrevDescriptor::getFieldStructName(void *object, int field) const
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

void *vrtStruct_PrevDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    vrtStruct_Prev *pp = (vrtStruct_Prev *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->nodePosition); break;
        default: return NULL;
    }
}

Register_Class(vrtpkt_Prev);

vrtpkt_Prev::vrtpkt_Prev(const char *name, int kind) : ::cPacket(name,kind)
{
    this->RSUDestID_var = 0;
    this->senderEDD_value_var = 0;
    this->senderID_var = 0;
    this->senderSpeed_var = 0;
    this->sendingTime_var = 0;
    RT_arraysize = 0;
    this->RT_var = 0;
}

vrtpkt_Prev::vrtpkt_Prev(const vrtpkt_Prev& other) : ::cPacket(other)
{
    RT_arraysize = 0;
    this->RT_var = 0;
    copy(other);
}

vrtpkt_Prev::~vrtpkt_Prev()
{
    delete [] RT_var;
}

vrtpkt_Prev& vrtpkt_Prev::operator=(const vrtpkt_Prev& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void vrtpkt_Prev::copy(const vrtpkt_Prev& other)
{
    this->RSUDestID_var = other.RSUDestID_var;
    this->senderEDD_value_var = other.senderEDD_value_var;
    this->senderID_var = other.senderID_var;
    this->senderPosition_var = other.senderPosition_var;
    this->senderSpeed_var = other.senderSpeed_var;
    this->sendingTime_var = other.sendingTime_var;
    delete [] this->RT_var;
    this->RT_var = (other.RT_arraysize==0) ? NULL : new vrtStruct_Prev[other.RT_arraysize];
    RT_arraysize = other.RT_arraysize;
    for (unsigned int i=0; i<RT_arraysize; i++)
        this->RT_var[i] = other.RT_var[i];
}

void vrtpkt_Prev::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->RSUDestID_var);
    doPacking(b,this->senderEDD_value_var);
    doPacking(b,this->senderID_var);
    doPacking(b,this->senderPosition_var);
    doPacking(b,this->senderSpeed_var);
    doPacking(b,this->sendingTime_var);
    b->pack(RT_arraysize);
    doPacking(b,this->RT_var,RT_arraysize);
}

void vrtpkt_Prev::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->RSUDestID_var);
    doUnpacking(b,this->senderEDD_value_var);
    doUnpacking(b,this->senderID_var);
    doUnpacking(b,this->senderPosition_var);
    doUnpacking(b,this->senderSpeed_var);
    doUnpacking(b,this->sendingTime_var);
    delete [] this->RT_var;
    b->unpack(RT_arraysize);
    if (RT_arraysize==0) {
        this->RT_var = 0;
    } else {
        this->RT_var = new vrtStruct_Prev[RT_arraysize];
        doUnpacking(b,this->RT_var,RT_arraysize);
    }
}

const char * vrtpkt_Prev::getRSUDestID() const
{
    return RSUDestID_var.c_str();
}

void vrtpkt_Prev::setRSUDestID(const char * RSUDestID)
{
    this->RSUDestID_var = RSUDestID;
}

double vrtpkt_Prev::getSenderEDD_value() const
{
    return senderEDD_value_var;
}

void vrtpkt_Prev::setSenderEDD_value(double senderEDD_value)
{
    this->senderEDD_value_var = senderEDD_value;
}

const char * vrtpkt_Prev::getSenderID() const
{
    return senderID_var.c_str();
}

void vrtpkt_Prev::setSenderID(const char * senderID)
{
    this->senderID_var = senderID;
}

Coord& vrtpkt_Prev::getSenderPosition()
{
    return senderPosition_var;
}

void vrtpkt_Prev::setSenderPosition(const Coord& senderPosition)
{
    this->senderPosition_var = senderPosition;
}

double vrtpkt_Prev::getSenderSpeed() const
{
    return senderSpeed_var;
}

void vrtpkt_Prev::setSenderSpeed(double senderSpeed)
{
    this->senderSpeed_var = senderSpeed;
}

simtime_t vrtpkt_Prev::getSendingTime() const
{
    return sendingTime_var;
}

void vrtpkt_Prev::setSendingTime(simtime_t sendingTime)
{
    this->sendingTime_var = sendingTime;
}

void vrtpkt_Prev::setRTArraySize(unsigned int size)
{
    vrtStruct_Prev *RT_var2 = (size==0) ? NULL : new vrtStruct_Prev[size];
    unsigned int sz = RT_arraysize < size ? RT_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        RT_var2[i] = this->RT_var[i];
    RT_arraysize = size;
    delete [] this->RT_var;
    this->RT_var = RT_var2;
}

unsigned int vrtpkt_Prev::getRTArraySize() const
{
    return RT_arraysize;
}

vrtStruct_Prev& vrtpkt_Prev::getRT(unsigned int k)
{
    if (k>=RT_arraysize) throw cRuntimeError("Array of size %d indexed by %d", RT_arraysize, k);
    return RT_var[k];
}

void vrtpkt_Prev::setRT(unsigned int k, const vrtStruct_Prev& RT)
{
    if (k>=RT_arraysize) throw cRuntimeError("Array of size %d indexed by %d", RT_arraysize, k);
    this->RT_var[k] = RT;
}

class vrtpkt_PrevDescriptor : public cClassDescriptor
{
  public:
    vrtpkt_PrevDescriptor();
    virtual ~vrtpkt_PrevDescriptor();

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

Register_ClassDescriptor(vrtpkt_PrevDescriptor);

vrtpkt_PrevDescriptor::vrtpkt_PrevDescriptor() : cClassDescriptor("vrtpkt_Prev", "cPacket")
{
}

vrtpkt_PrevDescriptor::~vrtpkt_PrevDescriptor()
{
}

bool vrtpkt_PrevDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<vrtpkt_Prev *>(obj)!=NULL;
}

const char *vrtpkt_PrevDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int vrtpkt_PrevDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int vrtpkt_PrevDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *vrtpkt_PrevDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "RSUDestID",
        "senderEDD_value",
        "senderID",
        "senderPosition",
        "senderSpeed",
        "sendingTime",
        "RT",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int vrtpkt_PrevDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='R' && strcmp(fieldName, "RSUDestID")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderEDD_value")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderID")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderPosition")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderSpeed")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "sendingTime")==0) return base+5;
    if (fieldName[0]=='R' && strcmp(fieldName, "RT")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *vrtpkt_PrevDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "double",
        "string",
        "Coord",
        "double",
        "simtime_t",
        "vrtStruct_Prev",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *vrtpkt_PrevDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int vrtpkt_PrevDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    vrtpkt_Prev *pp = (vrtpkt_Prev *)object; (void)pp;
    switch (field) {
        case 6: return pp->getRTArraySize();
        default: return 0;
    }
}

std::string vrtpkt_PrevDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    vrtpkt_Prev *pp = (vrtpkt_Prev *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getRSUDestID());
        case 1: return double2string(pp->getSenderEDD_value());
        case 2: return oppstring2string(pp->getSenderID());
        case 3: {std::stringstream out; out << pp->getSenderPosition(); return out.str();}
        case 4: return double2string(pp->getSenderSpeed());
        case 5: return double2string(pp->getSendingTime());
        case 6: {std::stringstream out; out << pp->getRT(i); return out.str();}
        default: return "";
    }
}

bool vrtpkt_PrevDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    vrtpkt_Prev *pp = (vrtpkt_Prev *)object; (void)pp;
    switch (field) {
        case 0: pp->setRSUDestID((value)); return true;
        case 1: pp->setSenderEDD_value(string2double(value)); return true;
        case 2: pp->setSenderID((value)); return true;
        case 4: pp->setSenderSpeed(string2double(value)); return true;
        case 5: pp->setSendingTime(string2double(value)); return true;
        default: return false;
    }
}

const char *vrtpkt_PrevDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 3: return opp_typename(typeid(Coord));
        case 6: return opp_typename(typeid(vrtStruct_Prev));
        default: return NULL;
    };
}

void *vrtpkt_PrevDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    vrtpkt_Prev *pp = (vrtpkt_Prev *)object; (void)pp;
    switch (field) {
        case 3: return (void *)(&pp->getSenderPosition()); break;
        case 6: return (void *)(&pp->getRT(i)); break;
        default: return NULL;
    }
}

Register_Class(MultipleRSUsRTpkt);

MultipleRSUsRTpkt::MultipleRSUsRTpkt(const char *name, int kind) : ::vrtpkt_Prev(name,kind)
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
    this->AckNodeID_var = 0;
    this->AckSenderMac_var = 0;
    this->AckDestMac_var = 0;
    this->AckPktSeqNum_var = 0;
    this->channelNumber_var = 0;
    this->senderMacAdd_var = 0;
}

MultipleRSUsRTpkt::MultipleRSUsRTpkt(const MultipleRSUsRTpkt& other) : ::vrtpkt_Prev(other)
{
    copy(other);
}

MultipleRSUsRTpkt::~MultipleRSUsRTpkt()
{
}

MultipleRSUsRTpkt& MultipleRSUsRTpkt::operator=(const MultipleRSUsRTpkt& other)
{
    if (this==&other) return *this;
    ::vrtpkt_Prev::operator=(other);
    copy(other);
    return *this;
}

void MultipleRSUsRTpkt::copy(const MultipleRSUsRTpkt& other)
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
    this->AckNodeID_var = other.AckNodeID_var;
    this->AckSenderMac_var = other.AckSenderMac_var;
    this->AckDestMac_var = other.AckDestMac_var;
    this->AckPktSeqNum_var = other.AckPktSeqNum_var;
    this->channelNumber_var = other.channelNumber_var;
    this->senderMacAdd_var = other.senderMacAdd_var;
    this->routing_table_var = other.routing_table_var;
}

void MultipleRSUsRTpkt::parsimPack(cCommBuffer *b)
{
    ::vrtpkt_Prev::parsimPack(b);
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
    doPacking(b,this->AckNodeID_var);
    doPacking(b,this->AckSenderMac_var);
    doPacking(b,this->AckDestMac_var);
    doPacking(b,this->AckPktSeqNum_var);
    doPacking(b,this->channelNumber_var);
    doPacking(b,this->senderMacAdd_var);
    doPacking(b,this->routing_table_var);
}

void MultipleRSUsRTpkt::parsimUnpack(cCommBuffer *b)
{
    ::vrtpkt_Prev::parsimUnpack(b);
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
    doUnpacking(b,this->AckNodeID_var);
    doUnpacking(b,this->AckSenderMac_var);
    doUnpacking(b,this->AckDestMac_var);
    doUnpacking(b,this->AckPktSeqNum_var);
    doUnpacking(b,this->channelNumber_var);
    doUnpacking(b,this->senderMacAdd_var);
    doUnpacking(b,this->routing_table_var);
}

int MultipleRSUsRTpkt::getPriority() const
{
    return priority_var;
}

void MultipleRSUsRTpkt::setPriority(int priority)
{
    this->priority_var = priority;
}

const char * MultipleRSUsRTpkt::getPktSourceID() const
{
    return pktSourceID_var.c_str();
}

void MultipleRSUsRTpkt::setPktSourceID(const char * pktSourceID)
{
    this->pktSourceID_var = pktSourceID;
}

int MultipleRSUsRTpkt::getSeqNumber() const
{
    return seqNumber_var;
}

void MultipleRSUsRTpkt::setSeqNumber(int seqNumber)
{
    this->seqNumber_var = seqNumber;
}

const char * MultipleRSUsRTpkt::getPktDestinationID() const
{
    return pktDestinationID_var.c_str();
}

void MultipleRSUsRTpkt::setPktDestinationID(const char * pktDestinationID)
{
    this->pktDestinationID_var = pktDestinationID;
}

int MultipleRSUsRTpkt::getPktDestinationMac() const
{
    return pktDestinationMac_var;
}

void MultipleRSUsRTpkt::setPktDestinationMac(int pktDestinationMac)
{
    this->pktDestinationMac_var = pktDestinationMac;
}

const char * MultipleRSUsRTpkt::getPktActualsrcID() const
{
    return pktActualsrcID_var.c_str();
}

void MultipleRSUsRTpkt::setPktActualsrcID(const char * pktActualsrcID)
{
    this->pktActualsrcID_var = pktActualsrcID;
}

int MultipleRSUsRTpkt::getPktActualsrcMac() const
{
    return pktActualsrcMac_var;
}

void MultipleRSUsRTpkt::setPktActualsrcMac(int pktActualsrcMac)
{
    this->pktActualsrcMac_var = pktActualsrcMac;
}

int MultipleRSUsRTpkt::getPktActualdestMac() const
{
    return pktActualdestMac_var;
}

void MultipleRSUsRTpkt::setPktActualdestMac(int pktActualdestMac)
{
    this->pktActualdestMac_var = pktActualdestMac;
}

simtime_t MultipleRSUsRTpkt::getPktGenerationTime() const
{
    return pktGenerationTime_var;
}

void MultipleRSUsRTpkt::setPktGenerationTime(simtime_t pktGenerationTime)
{
    this->pktGenerationTime_var = pktGenerationTime;
}

simtime_t MultipleRSUsRTpkt::getPktlastReceiveTime() const
{
    return pktlastReceiveTime_var;
}

void MultipleRSUsRTpkt::setPktlastReceiveTime(simtime_t pktlastReceiveTime)
{
    this->pktlastReceiveTime_var = pktlastReceiveTime;
}

simtime_t MultipleRSUsRTpkt::getDestArrivalTime() const
{
    return DestArrivalTime_var;
}

void MultipleRSUsRTpkt::setDestArrivalTime(simtime_t DestArrivalTime)
{
    this->DestArrivalTime_var = DestArrivalTime;
}

simtime_t MultipleRSUsRTpkt::getPktTTL() const
{
    return pktTTL_var;
}

void MultipleRSUsRTpkt::setPktTTL(simtime_t pktTTL)
{
    this->pktTTL_var = pktTTL;
}

const char * MultipleRSUsRTpkt::getAckNodeID() const
{
    return AckNodeID_var.c_str();
}

void MultipleRSUsRTpkt::setAckNodeID(const char * AckNodeID)
{
    this->AckNodeID_var = AckNodeID;
}

int MultipleRSUsRTpkt::getAckSenderMac() const
{
    return AckSenderMac_var;
}

void MultipleRSUsRTpkt::setAckSenderMac(int AckSenderMac)
{
    this->AckSenderMac_var = AckSenderMac;
}

int MultipleRSUsRTpkt::getAckDestMac() const
{
    return AckDestMac_var;
}

void MultipleRSUsRTpkt::setAckDestMac(int AckDestMac)
{
    this->AckDestMac_var = AckDestMac;
}

int MultipleRSUsRTpkt::getAckPktSeqNum() const
{
    return AckPktSeqNum_var;
}

void MultipleRSUsRTpkt::setAckPktSeqNum(int AckPktSeqNum)
{
    this->AckPktSeqNum_var = AckPktSeqNum;
}

int MultipleRSUsRTpkt::getChannelNumber() const
{
    return channelNumber_var;
}

void MultipleRSUsRTpkt::setChannelNumber(int channelNumber)
{
    this->channelNumber_var = channelNumber;
}

int MultipleRSUsRTpkt::getSenderMacAdd() const
{
    return senderMacAdd_var;
}

void MultipleRSUsRTpkt::setSenderMacAdd(int senderMacAdd)
{
    this->senderMacAdd_var = senderMacAdd;
}

MultRSUsRt& MultipleRSUsRTpkt::getRouting_table()
{
    return routing_table_var;
}

void MultipleRSUsRTpkt::setRouting_table(const MultRSUsRt& routing_table)
{
    this->routing_table_var = routing_table;
}

class MultipleRSUsRTpktDescriptor : public cClassDescriptor
{
  public:
    MultipleRSUsRTpktDescriptor();
    virtual ~MultipleRSUsRTpktDescriptor();

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

Register_ClassDescriptor(MultipleRSUsRTpktDescriptor);

MultipleRSUsRTpktDescriptor::MultipleRSUsRTpktDescriptor() : cClassDescriptor("MultipleRSUsRTpkt", "vrtpkt_Prev")
{
}

MultipleRSUsRTpktDescriptor::~MultipleRSUsRTpktDescriptor()
{
}

bool MultipleRSUsRTpktDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<MultipleRSUsRTpkt *>(obj)!=NULL;
}

const char *MultipleRSUsRTpktDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int MultipleRSUsRTpktDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 19+basedesc->getFieldCount(object) : 19;
}

unsigned int MultipleRSUsRTpktDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<19) ? fieldTypeFlags[field] : 0;
}

const char *MultipleRSUsRTpktDescriptor::getFieldName(void *object, int field) const
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
        "AckNodeID",
        "AckSenderMac",
        "AckDestMac",
        "AckPktSeqNum",
        "channelNumber",
        "senderMacAdd",
        "routing_table",
    };
    return (field>=0 && field<19) ? fieldNames[field] : NULL;
}

int MultipleRSUsRTpktDescriptor::findField(void *object, const char *fieldName) const
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
    if (fieldName[0]=='A' && strcmp(fieldName, "AckNodeID")==0) return base+12;
    if (fieldName[0]=='A' && strcmp(fieldName, "AckSenderMac")==0) return base+13;
    if (fieldName[0]=='A' && strcmp(fieldName, "AckDestMac")==0) return base+14;
    if (fieldName[0]=='A' && strcmp(fieldName, "AckPktSeqNum")==0) return base+15;
    if (fieldName[0]=='c' && strcmp(fieldName, "channelNumber")==0) return base+16;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderMacAdd")==0) return base+17;
    if (fieldName[0]=='r' && strcmp(fieldName, "routing_table")==0) return base+18;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *MultipleRSUsRTpktDescriptor::getFieldTypeString(void *object, int field) const
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
        "string",
        "int",
        "int",
        "int",
        "int",
        "int",
        "MultRSUsRt",
    };
    return (field>=0 && field<19) ? fieldTypeStrings[field] : NULL;
}

const char *MultipleRSUsRTpktDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int MultipleRSUsRTpktDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    MultipleRSUsRTpkt *pp = (MultipleRSUsRTpkt *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string MultipleRSUsRTpktDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    MultipleRSUsRTpkt *pp = (MultipleRSUsRTpkt *)object; (void)pp;
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
        case 12: return oppstring2string(pp->getAckNodeID());
        case 13: return long2string(pp->getAckSenderMac());
        case 14: return long2string(pp->getAckDestMac());
        case 15: return long2string(pp->getAckPktSeqNum());
        case 16: return long2string(pp->getChannelNumber());
        case 17: return long2string(pp->getSenderMacAdd());
        case 18: {std::stringstream out; out << pp->getRouting_table(); return out.str();}
        default: return "";
    }
}

bool MultipleRSUsRTpktDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    MultipleRSUsRTpkt *pp = (MultipleRSUsRTpkt *)object; (void)pp;
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
        case 12: pp->setAckNodeID((value)); return true;
        case 13: pp->setAckSenderMac(string2long(value)); return true;
        case 14: pp->setAckDestMac(string2long(value)); return true;
        case 15: pp->setAckPktSeqNum(string2long(value)); return true;
        case 16: pp->setChannelNumber(string2long(value)); return true;
        case 17: pp->setSenderMacAdd(string2long(value)); return true;
        default: return false;
    }
}

const char *MultipleRSUsRTpktDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 18: return opp_typename(typeid(MultRSUsRt));
        default: return NULL;
    };
}

void *MultipleRSUsRTpktDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    MultipleRSUsRTpkt *pp = (MultipleRSUsRTpkt *)object; (void)pp;
    switch (field) {
        case 18: return (void *)(&pp->getRouting_table()); break;
        default: return NULL;
    }
}


