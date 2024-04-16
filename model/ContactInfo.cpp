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
    valid = false;
}

ContactInfo::ContactInfo(QString fullName, QString address, QString postalcode,
          QString email, QString phoneNumber, QString comment, QString typeInfo, QString id, bool valid )
{
    setValues(fullName, address, postalcode, email, phoneNumber, comment, typeInfo, id, valid);
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

void ContactInfo::setValues(QString fullName, QString address, QString postalcode, QString email, QString phoneNumber, QString comment, QString typeInfo, QString id, bool valid)
{
    this->fullName = fullName;
    this->address = address;
    this->postalcode = postalcode;
    this->email = email;
    this->phoneNumber = phoneNumber;
    this->comment = comment;
    this->typeInfo = typeInfo;
    this->id = id;
    this->valid = valid;
}

bool ContactInfo::isValid()
{
    return valid;
}
