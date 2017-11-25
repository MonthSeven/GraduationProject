//
// Generated file, do not edit! Created by nedtool 4.6 from src/modules/messages/pkAck.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "pkAck_m.h"

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

Register_Class(ackn);

ackn::ackn(const char *name, int kind) : ::cPacket(name,kind)
{
    this->myNodeID_var = 0;
    this->myMac_var = 0;
    this->pktSeqNum_var = 0;
}

ackn::ackn(const ackn& other) : ::cPacket(other)
{
    copy(other);
}

ackn::~ackn()
{
}

ackn& ackn::operator=(const ackn& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void ackn::copy(const ackn& other)
{
    this->myNodeID_var = other.myNodeID_var;
    this->myMac_var = other.myMac_var;
    this->pktSeqNum_var = other.pktSeqNum_var;
}

void ackn::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->myNodeID_var);
    doPacking(b,this->myMac_var);
    doPacking(b,this->pktSeqNum_var);
}

void ackn::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->myNodeID_var);
    doUnpacking(b,this->myMac_var);
    doUnpacking(b,this->pktSeqNum_var);
}

const char * ackn::getMyNodeID() const
{
    return myNodeID_var.c_str();
}

void ackn::setMyNodeID(const char * myNodeID)
{
    this->myNodeID_var = myNodeID;
}

int ackn::getMyMac() const
{
    return myMac_var;
}

void ackn::setMyMac(int myMac)
{
    this->myMac_var = myMac;
}

int ackn::getPktSeqNum() const
{
    return pktSeqNum_var;
}

void ackn::setPktSeqNum(int pktSeqNum)
{
    this->pktSeqNum_var = pktSeqNum;
}

class acknDescriptor : public cClassDescriptor
{
  public:
    acknDescriptor();
    virtual ~acknDescriptor();

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

Register_ClassDescriptor(acknDescriptor);

acknDescriptor::acknDescriptor() : cClassDescriptor("ackn", "cPacket")
{
}

acknDescriptor::~acknDescriptor()
{
}

bool acknDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ackn *>(obj)!=NULL;
}

const char *acknDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int acknDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int acknDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *acknDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "myNodeID",
        "myMac",
        "pktSeqNum",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int acknDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "myNodeID")==0) return base+0;
    if (fieldName[0]=='m' && strcmp(fieldName, "myMac")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "pktSeqNum")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *acknDescriptor::getFieldTypeString(void *object, int field) const
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
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *acknDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int acknDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ackn *pp = (ackn *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string acknDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ackn *pp = (ackn *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getMyNodeID());
        case 1: return long2string(pp->getMyMac());
        case 2: return long2string(pp->getPktSeqNum());
        default: return "";
    }
}

bool acknDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ackn *pp = (ackn *)object; (void)pp;
    switch (field) {
        case 0: pp->setMyNodeID((value)); return true;
        case 1: pp->setMyMac(string2long(value)); return true;
        case 2: pp->setPktSeqNum(string2long(value)); return true;
        default: return false;
    }
}

const char *acknDescriptor::getFieldStructName(void *object, int field) const
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

void *acknDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ackn *pp = (ackn *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


