#include "ContactInfo.h"
#include "ContactInfo.h"
#include "ContactInfo.h"

ContactInfo::ContactInfo()
{
    id = "";
    fullName = "";
    address = "";
    postalcode = "";
    email = "";
    phoneNumber = "";
    comment = "";
    typeInfo = "";
}

ContactInfo::ContactInfo(QString fullName, QString address, QString postalcode,
          QString email, QString phoneNumber, QString comment, QString typeInfo, QString id )
{
    this->fullName = fullName;
    this->address = address;
    this->postalcode = postalcode;
    this->email = email;
    this->phoneNumber = phoneNumber;
    this->comment = comment;
    this->typeInfo = typeInfo;
    this->id = id;
}

void ContactInfo::setId(QString id)
{
    //validate id before assignment
    this->id = id;
}

QString ContactInfo::getId()
{
    return id;
}

ContactInfo::~ContactInfo()
{

}

QString ContactInfo::getFullName()
{
    return fullName;
}

QString ContactInfo::getAddress()
{
    return  address;
}

QString ContactInfo::getPostalcode()
{
    return postalcode;
}

QString ContactInfo::getEmail()
{
    return email;
}

QString ContactInfo::getPhoneNumber()
{
    return phoneNumber;
}

QString ContactInfo::getComment()
{
    return comment;
}

QString ContactInfo::getTypeInfo()
{
    return typeInfo;
}
