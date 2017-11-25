//
// Generated file, do not edit! Created by nedtool 4.6 from src/modules/messages/Vehicle_Routing_Table.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "Vehicle_Routing_Table_m.h"

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

Veh_Routing_Table::Veh_Routing_Table()
{
    nodeMacAdd = 0;
    nodestrid = 0;
    vehSpeed = 0;
    EDD_Value = 0;
    lastUpdateTime = 0;
    rtTTL = 10;
}

void doPacking(cCommBuffer *b, Veh_Routing_Table& a)
{
    doPacking(b,a.nodeMacAdd);
    doPacking(b,a.nodestrid);
    doPacking(b,a.vehPosition);
    doPacking(b,a.vehSpeed);
    doPacking(b,a.EDD_Value);
    doPacking(b,a.lastUpdateTime);
    doPacking(b,a.rtTTL);
}

void doUnpacking(cCommBuffer *b, Veh_Routing_Table& a)
{
    doUnpacking(b,a.nodeMacAdd);
    doUnpacking(b,a.nodestrid);
    doUnpacking(b,a.vehPosition);
    doUnpacking(b,a.vehSpeed);
    doUnpacking(b,a.EDD_Value);
    doUnpacking(b,a.lastUpdateTime);
    doUnpacking(b,a.rtTTL);
}

class Veh_Routing_TableDescriptor : public cClassDescriptor
{
  public:
    Veh_Routing_TableDescriptor();
    virtual ~Veh_Routing_TableDescriptor();

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

Register_ClassDescriptor(Veh_Routing_TableDescriptor);

Veh_Routing_TableDescriptor::Veh_Routing_TableDescriptor() : cClassDescriptor("Veh_Routing_Table", "")
{
}

Veh_Routing_TableDescriptor::~Veh_Routing_TableDescriptor()
{
}

bool Veh_Routing_TableDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Veh_Routing_Table *>(obj)!=NULL;
}

const char *Veh_Routing_TableDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int Veh_Routing_TableDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int Veh_Routing_TableDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *Veh_Routing_TableDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "nodeMacAdd",
        "nodestrid",
        "vehPosition",
        "vehSpeed",
        "EDD_Value",
        "lastUpdateTime",
        "rtTTL",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int Veh_Routing_TableDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeMacAdd")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodestrid")==0) return base+1;
    if (fieldName[0]=='v' && strcmp(fieldName, "vehPosition")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "vehSpeed")==0) return base+3;
    if (fieldName[0]=='E' && strcmp(fieldName, "EDD_Value")==0) return base+4;
    if (fieldName[0]=='l' && strcmp(fieldName, "lastUpdateTime")==0) return base+5;
    if (fieldName[0]=='r' && strcmp(fieldName, "rtTTL")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *Veh_Routing_TableDescriptor::getFieldTypeString(void *object, int field) const
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
        "simtime_t",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *Veh_Routing_TableDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int Veh_Routing_TableDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Veh_Routing_Table *pp = (Veh_Routing_Table *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string Veh_Routing_TableDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Veh_Routing_Table *pp = (Veh_Routing_Table *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->nodeMacAdd);
        case 1: return oppstring2string(pp->nodestrid);
        case 2: {std::stringstream out; out << pp->vehPosition; return out.str();}
        case 3: return double2string(pp->vehSpeed);
        case 4: return double2string(pp->EDD_Value);
        case 5: return double2string(pp->lastUpdateTime);
        case 6: return double2string(pp->rtTTL);
        default: return "";
    }
}

bool Veh_Routing_TableDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Veh_Routing_Table *pp = (Veh_Routing_Table *)object; (void)pp;
    switch (field) {
        case 0: pp->nodeMacAdd = string2long(value); return true;
        case 1: pp->nodestrid = (value); return true;
        case 3: pp->vehSpeed = string2double(value); return true;
        case 4: pp->EDD_Value = string2double(value); return true;
        case 5: pp->lastUpdateTime = string2double(value); return true;
        case 6: pp->rtTTL = string2double(value); return true;
        default: return false;
    }
}

const char *Veh_Routing_TableDescriptor::getFieldStructName(void *object, int field) const
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

void *Veh_Routing_TableDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Veh_Routing_Table *pp = (Veh_Routing_Table *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->vehPosition); break;
        default: return NULL;
    }
}

Register_Class(VRT);

VRT::VRT(const char *name, int kind) : ::cPacket(name,kind)
{
    this->extID_var = 0;
    this->senderMacAdd_var = 0;
    this->sendernodeStrId_var = 0;
    this->senderSpeed_var = 0;
    this->senderEDD_value_var = 0;
    this->sendingTime_var = 0;
    this->priority_var = 3;
    RT_arraysize = 0;
    this->RT_var = 0;
}

VRT::VRT(const VRT& other) : ::cPacket(other)
{
    RT_arraysize = 0;
    this->RT_var = 0;
    copy(other);
}

VRT::~VRT()
{
    delete [] RT_var;
}

VRT& VRT::operator=(const VRT& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void VRT::copy(const VRT& other)
{
    this->extID_var = other.extID_var;
    this->senderMacAdd_var = other.senderMacAdd_var;
    this->sendernodeStrId_var = other.sendernodeStrId_var;
    this->senderPosition_var = other.senderPosition_var;
    this->senderSpeed_var = other.senderSpeed_var;
    this->senderEDD_value_var = other.senderEDD_value_var;
    this->sendingTime_var = other.sendingTime_var;
    this->priority_var = other.priority_var;
    delete [] this->RT_var;
    this->RT_var = (other.RT_arraysize==0) ? NULL : new Veh_Routing_Table[other.RT_arraysize];
    RT_arraysize = other.RT_arraysize;
    for (unsigned int i=0; i<RT_arraysize; i++)
        this->RT_var[i] = other.RT_var[i];
}

void VRT::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->extID_var);
    doPacking(b,this->senderMacAdd_var);
    doPacking(b,this->sendernodeStrId_var);
    doPacking(b,this->senderPosition_var);
    doPacking(b,this->senderSpeed_var);
    doPacking(b,this->senderEDD_value_var);
    doPacking(b,this->sendingTime_var);
    doPacking(b,this->priority_var);
    b->pack(RT_arraysize);
    doPacking(b,this->RT_var,RT_arraysize);
}

void VRT::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->extID_var);
    doUnpacking(b,this->senderMacAdd_var);
    doUnpacking(b,this->sendernodeStrId_var);
    doUnpacking(b,this->senderPosition_var);
    doUnpacking(b,this->senderSpeed_var);
    doUnpacking(b,this->senderEDD_value_var);
    doUnpacking(b,this->sendingTime_var);
    doUnpacking(b,this->priority_var);
    delete [] this->RT_var;
    b->unpack(RT_arraysize);
    if (RT_arraysize==0) {
        this->RT_var = 0;
    } else {
        this->RT_var = new Veh_Routing_Table[RT_arraysize];
        doUnpacking(b,this->RT_var,RT_arraysize);
    }
}

const char * VRT::getExtID() const
{
    return extID_var.c_str();
}

void VRT::setExtID(const char * extID)
{
    this->extID_var = extID;
}

int VRT::getSenderMacAdd() const
{
    return senderMacAdd_var;
}

void VRT::setSenderMacAdd(int senderMacAdd)
{
    this->senderMacAdd_var = senderMacAdd;
}

const char * VRT::getSendernodeStrId() const
{
    return sendernodeStrId_var.c_str();
}

void VRT::setSendernodeStrId(const char * sendernodeStrId)
{
    this->sendernodeStrId_var = sendernodeStrId;
}

Coord& VRT::getSenderPosition()
{
    return senderPosition_var;
}

void VRT::setSenderPosition(const Coord& senderPosition)
{
    this->senderPosition_var = senderPosition;
}

double VRT::getSenderSpeed() const
{
    return senderSpeed_var;
}

void VRT::setSenderSpeed(double senderSpeed)
{
    this->senderSpeed_var = senderSpeed;
}

double VRT::getSenderEDD_value() const
{
    return senderEDD_value_var;
}

void VRT::setSenderEDD_value(double senderEDD_value)
{
    this->senderEDD_value_var = senderEDD_value;
}

simtime_t VRT::getSendingTime() const
{
    return sendingTime_var;
}

void VRT::setSendingTime(simtime_t sendingTime)
{
    this->sendingTime_var = sendingTime;
}

int VRT::getPriority() const
{
    return priority_var;
}

void VRT::setPriority(int priority)
{
    this->priority_var = priority;
}

void VRT::setRTArraySize(unsigned int size)
{
    Veh_Routing_Table *RT_var2 = (size==0) ? NULL : new Veh_Routing_Table[size];
    unsigned int sz = RT_arraysize < size ? RT_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        RT_var2[i] = this->RT_var[i];
    RT_arraysize = size;
    delete [] this->RT_var;
    this->RT_var = RT_var2;
}

unsigned int VRT::getRTArraySize() const
{
    return RT_arraysize;
}

Veh_Routing_Table& VRT::getRT(unsigned int k)
{
    if (k>=RT_arraysize) throw cRuntimeError("Array of size %d indexed by %d", RT_arraysize, k);
    return RT_var[k];
}

void VRT::setRT(unsigned int k, const Veh_Routing_Table& RT)
{
    if (k>=RT_arraysize) throw cRuntimeError("Array of size %d indexed by %d", RT_arraysize, k);
    this->RT_var[k] = RT;
}

class VRTDescriptor : public cClassDescriptor
{
  public:
    VRTDescriptor();
    virtual ~VRTDescriptor();

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

Register_ClassDescriptor(VRTDescriptor);

VRTDescriptor::VRTDescriptor() : cClassDescriptor("VRT", "cPacket")
{
}

VRTDescriptor::~VRTDescriptor()
{
}

bool VRTDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<VRT *>(obj)!=NULL;
}

const char *VRTDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int VRTDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 9+basedesc->getFieldCount(object) : 9;
}

unsigned int VRTDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<9) ? fieldTypeFlags[field] : 0;
}

const char *VRTDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "extID",
        "senderMacAdd",
        "sendernodeStrId",
        "senderPosition",
        "senderSpeed",
        "senderEDD_value",
        "sendingTime",
        "priority",
        "RT",
    };
    return (field>=0 && field<9) ? fieldNames[field] : NULL;
}

int VRTDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='e' && strcmp(fieldName, "extID")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderMacAdd")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "sendernodeStrId")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderPosition")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderSpeed")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderEDD_value")==0) return base+5;
    if (fieldName[0]=='s' && strcmp(fieldName, "sendingTime")==0) return base+6;
    if (fieldName[0]=='p' && strcmp(fieldName, "priority")==0) return base+7;
    if (fieldName[0]=='R' && strcmp(fieldName, "RT")==0) return base+8;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *VRTDescriptor::getFieldTypeString(void *object, int field) const
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
        "Coord",
        "double",
        "double",
        "simtime_t",
        "int",
        "Veh_Routing_Table",
    };
    return (field>=0 && field<9) ? fieldTypeStrings[field] : NULL;
}

const char *VRTDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int VRTDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    VRT *pp = (VRT *)object; (void)pp;
    switch (field) {
        case 8: return pp->getRTArraySize();
        default: return 0;
    }
}

std::string VRTDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    VRT *pp = (VRT *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getExtID());
        case 1: return long2string(pp->getSenderMacAdd());
        case 2: return oppstring2string(pp->getSendernodeStrId());
        case 3: {std::stringstream out; out << pp->getSenderPosition(); return out.str();}
        case 4: return double2string(pp->getSenderSpeed());
        case 5: return double2string(pp->getSenderEDD_value());
        case 6: return double2string(pp->getSendingTime());
        case 7: return long2string(pp->getPriority());
        case 8: {std::stringstream out; out << pp->getRT(i); return out.str();}
        default: return "";
    }
}

bool VRTDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    VRT *pp = (VRT *)object; (void)pp;
    switch (field) {
        case 0: pp->setExtID((value)); return true;
        case 1: pp->setSenderMacAdd(string2long(value)); return true;
        case 2: pp->setSendernodeStrId((value)); return true;
        case 4: pp->setSenderSpeed(string2double(value)); return true;
        case 5: pp->setSenderEDD_value(string2double(value)); return true;
        case 6: pp->setSendingTime(string2double(value)); return true;
        case 7: pp->setPriority(string2long(value)); return true;
        default: return false;
    }
}

const char *VRTDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 3: return opp_typename(typeid(Coord));
        case 8: return opp_typename(typeid(Veh_Routing_Table));
        default: return NULL;
    };
}

void *VRTDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    VRT *pp = (VRT *)object; (void)pp;
    switch (field) {
        case 3: return (void *)(&pp->getSenderPosition()); break;
        case 8: return (void *)(&pp->getRT(i)); break;
        default: return NULL;
    }
}


