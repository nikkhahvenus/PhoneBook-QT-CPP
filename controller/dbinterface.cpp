#include "dbinterface.h"

DbInterface* DbInterface::dbInterfacePtr= nullptr;;

DbInterface::DbInterface()
{
    repo = Repository::getInstance();
}

DbInterface::~DbInterface()
{
    if(repo){
      delete repo;
    }
    Logger::dLog( "DbInterface destructor executed");
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
        return  false;
    }

    //validate phone number then assign
    PhoneOwner owner = repo->fetchOwnerInformation(phoneNumber);
    Logger::dLog(owner.getId());

    dbInterfacePtr->phoneOwner.setPhoneNumber( phoneNumber);
    return false;
}
