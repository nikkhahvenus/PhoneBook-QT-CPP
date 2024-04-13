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
    bool returnValue = false;
    clearContactList();
    returnValue = repo->loadContacts(phoneOwner.getId());
//    printContacts();
    return returnValue;
}

bool DbInterface::fetchGroups()
{
    bool returnValue = false;
    clearGroupList();
    returnValue = repo->loadGroups(phoneOwner.getId());
//    printGroups();
    return returnValue;
}

bool DbInterface::fetchGroupMembers()
{
    bool returnValue = true;
    for (int i=0; i< groupList.length(); i++)
    {
        Group * group = groupList[i];
        if(!(repo->loadCommercialGroupMembers(phoneOwner.getId(), group->getId() ) &&
             repo->loadGeneralGroupMembers(phoneOwner.getId(), group->getId()  ))
                )
        {
                returnValue = false;
        }
    }
    return returnValue;
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

bool DbInterface::InitializeForCurrentLogin()
{
    return
    (DbInterface::getInstance())->fetchContacts() &&
    (DbInterface::getInstance())->fetchGroups()&&
    (DbInterface::getInstance())->fetchGroupMembers();
}

bool DbInterface::appendContact(Contact * newContact)
{
    contactList.append (newContact);
    return true;
}

bool DbInterface::appendGroup(Group * newGroup)
{
    groupList.append (newGroup);
    return true;
}

int DbInterface::getLengthOfContactList()
{
    return contactList.length();
}

QString DbInterface::getIdOfContactInPlaceOfIndexInContactList(int indexInContactList)
{
    return contactList[indexInContactList]->getId();
}
QString DbInterface::getTypeOfContactInPlaceOfIndexInContactList(int indexInContactList)
{
    return contactList[indexInContactList]->typeInfo();
}

Contact* DbInterface::getContactPtr(int indexInContactList)
{
    return contactList[indexInContactList];
}

bool DbInterface::appendNewMemberForGroup(int index, QString groupId)
{
    bool returnValue = false;
    bool exitLoop = false;
    for (int i=0; i< groupList.length() && !exitLoop; i++)
    {
        Group * group = groupList[i];
        if(group->getId() == groupId)
        {
            group->appendMemberList(contactList[index]);
            returnValue = true;
            exitLoop = true;
        }
    }
    return returnValue;
}

bool DbInterface::addContact(ContactInfo *contactInfo)
{
    bool returnValue = true;
    if (contactInfo->getTypeInfo() == "Commercial")
        returnValue = repo->inserContactIntoCommertialTable(phoneOwner.getId(),contactInfo);
    else
        returnValue = repo->inserContactIntoGeneralTable(phoneOwner.getId(),contactInfo);

    return returnValue;

}
