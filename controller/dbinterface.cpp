#include "dbinterface.h"

DbInterface* DbInterface::dbInterfacePtr= nullptr;;

DbInterface::DbInterface()
{

}

DbInterface::~DbInterface()
{
    delete dbInterfacePtr;
}

DbInterface *DbInterface::getInstance()
{
    if(dbInterfacePtr== nullptr){
        dbInterfacePtr = new DbInterface();
        Logger::dLog("new DbInterface");
    }
    return dbInterfacePtr;
}

QString DbInterface::getPhoneOwner_s_Phone()
{
    return phoneOwner.getPhone();
}

QString DbInterface::getPhoneOwner_s_FullName()
{
    return phoneOwner.getFullName();
}

bool DbInterface::fetchOwnerInformation(QString phoneNumber)
{
    if(!dbInterfacePtr)
    {
        Logger::dLog("create an instance of DbInterface, then call fetchOwnerInformation");
    }

    //validate phone number then assign
    dbInterfacePtr->phoneOwner.setPhoneNumber( phoneNumber);
    return false;
}
