#include "dbinterface.h"
#include "dbinterface.h"

DbInterface* DbInterface::dbInterfacePtr= nullptr;;

DbInterface::DbInterface()
{
    repo = Repository::getInstance();
    clearContactList();
    clearGroupList();
}

DbInterface::~DbInterface()
{
    if(repo){
      delete repo;
    }
    reset();
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
    clearContactList();
    clearGroupList();
}

bool DbInterface::fetchContacts()
{
    clearContactList();
    repo->loadContacts(phoneOwner.getId(), contactList);
    //    printContacts();
    return true;
}

bool DbInterface::fetchGroups()
{
    clearGroupList();
    repo->loadGroups(phoneOwner.getId(), groupList);
    printGroups();
    return true;
}

bool DbInterface::fetchGroupMembers()
{
    for (int i=0; i< groupList.length(); i++)
    {
        Group * group = groupList[i];
        repo->loadCommercialGroupMembers(phoneOwner.getId(), *group, contactList );
        repo->loadGeneralGroupMembers(phoneOwner.getId(), *group, contactList );
    }
    return true;
}

void DbInterface::clearGroupList()
{
    if(groupList.isEmpty())
        return;
    for(int i = 0; i < groupList.length() ; i++)
            delete groupList[i];

    groupList.clear();
}

void DbInterface::clearContactList()
{
    if(contactList.isEmpty())
        return;
    for(int i = 0; i < contactList.length() ; i++)
            delete contactList[i];

    contactList.clear();
}

QSqlQueryModel* DbInterface::searchText(QString txtSearch)
{
    return repo->searchText(txtSearch, phoneOwner);

}

void DbInterface::printContacts()
{
    Logger::log(" id  fullName  phoneNumber  address  postalcode  email  marked  comment");

    for(int i = 0; i < contactList.length() ; i++)
    {
        Logger::log(contactList[i]->toString());
    }
}

void DbInterface::printGroups()
{
    Logger::log(" id name description");

    for(int i = 0; i < groupList.length() ; i++)
    {
        Logger::log(groupList[i]->toString());
    }
}
