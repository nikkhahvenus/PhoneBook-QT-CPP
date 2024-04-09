#include "phoneowner.h"

PhoneOwner::PhoneOwner()
{
    setId("0");
    setPhone("");
    setFullName("");
}

PhoneOwner::PhoneOwner(QString id,QString phone,QString fullName)
{
    setOwner(id,phone,fullName);
}
bool PhoneOwner::setOwner(QString id,QString phone,QString fullName)
{
    return setId(id) && setPhone(phone) && setFullName(fullName);
}

bool PhoneOwner::setOwner(PhoneOwner& owner)
{
    return setOwner(owner.id, owner.phone, owner.fullName);
}

bool PhoneOwner::setOwner(PhoneOwner *owner)
{
    if(owner)
        return setOwner(*owner);
    return false;
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





bool PhoneOwner::setId(QString id)
{
    //first validate Id then assign
    this->id = id;
    return true;
}

bool PhoneOwner::setPhone(QString phoneNumber)
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

QString PhoneOwner::toString()
{
    return getId() + " " + getPhone() + " " + getFullName();
}


