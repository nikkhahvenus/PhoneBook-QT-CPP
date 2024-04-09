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
    Logger::log( "DbInterface destructor executed");
}

DbInterface *DbInterface::getInstance()
{
    if(dbInterfacePtr== nullptr){
        dbInterfacePtr = new DbInterface();
        Logger::log("new DbInterface");
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
        Logger::log("create an instance of DbInterface, then call fetchOwnerInformation");
        return  false;
    }

    //validate phone number then fetch owner and then assign
    PhoneOwner owner = repo->fetchOwnerInformation(phoneNumber);
    if(owner.getPhone() == phoneNumber)
    {
        dbInterfacePtr->phoneOwner.setOwner(owner);
        return true;
    }
    return false;
}

void DbInterface::reset()
{
    phoneOwner.setOwner(new PhoneOwner("0","",""));
}
