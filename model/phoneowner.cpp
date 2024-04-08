#include "phoneowner.h"

PhoneOwner::PhoneOwner()
{

}

QString PhoneOwner::getId()
{
    return  id;
}

QString PhoneOwner::getPhone()
{
    return phone;
}

QString PhoneOwner::getFullName()
{
    return fullName;
}

bool PhoneOwner::setPhoneNumber(QString phoneNumber)
{
    //first validate phoneNumber then assign
    this->phone = phoneNumber;
    return true;
}

bool PhoneOwner::setFullName(QString fullName)
{
    //first validate fullName then assign
    this->fullName = fullName;
    return true;
}


