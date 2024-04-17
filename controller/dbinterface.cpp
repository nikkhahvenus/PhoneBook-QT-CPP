#include "dbinterface.h"

DbInterface* DbInterface::dbInterfacePtr= nullptr;;

DbInterface::DbInterface()
{

    repositoryPtr = Repository::getInstance();
    searchEnginePtr = SearchEngine::getInstance();

}

DbInterface::~DbInterface()
{
    if(repositoryPtr){
        delete repositoryPtr;
        repositoryPtr = nullptr;
    }
    if(searchEnginePtr){
        delete searchEnginePtr;
        searchEnginePtr = nullptr;
    }

    reset();
}

DbInterface *DbInterface::getInstance()
{
    if(DbInterface::dbInterfacePtr == nullptr){
        DbInterface::dbInterfacePtr = new DbInterface();
    }
    return DbInterface::dbInterfacePtr;
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
    PhoneOwner owner = repositoryPtr->fetchOwnerInformation(phoneNumber);
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
    if(searchEnginePtr)
        searchEnginePtr->clearResultList();
}

bool DbInterface::fetchContacts()
{
    bool returnValue = false;
    clearContactList();
    returnValue = repositoryPtr->loadContacts(phoneOwner.getId());
//    printContacts();
    return returnValue;
}

bool DbInterface::fetchGroups()
{
    bool returnValue = false;
    clearGroupList();
    returnValue = repositoryPtr->loadGroups(phoneOwner.getId());
    return returnValue;
}

bool DbInterface::fetchGroupMembers()
{
    bool returnValue = true;
    for (int i=0; i< groupList.length(); i++)
    {
        Group * group = groupList[i];
        if(!(repositoryPtr->loadCommercialGroupMembers(phoneOwner.getId(), group->getId() ) &&
             repositoryPtr->loadGeneralGroupMembers(phoneOwner.getId(), group->getId()  ))
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
    if (contactInfo->getTypeInfo() == COMMERCIAL )
        returnValue = repositoryPtr->inserContactIntoCommertialTable(phoneOwner.getId(),contactInfo);
    else
        returnValue = repositoryPtr->inserContactIntoGeneralTable(phoneOwner.getId(),contactInfo);

    return returnValue;
}

bool DbInterface::searchText(QString txtSearch)
{
    bool returnValue = false;
    searchEnginePtr->clearResultList();
    returnValue = searchEnginePtr->searchInSensitive(txtSearch, contactList);
    //    printResults();
    return returnValue;
}

ContactInfo DbInterface::getContactInfoOf(int index)
{
    ContactInfo contactInfo;
    if(index < 0 && index >= contactList.length())
        return contactInfo;

    Contact * contact = contactList[index];

    contactInfo.setValues(contact->getFullName(), contact->getAddress(), contact->getPostalcode(), contact->getEmail(),
                contact->getPhoneNumber(), contact->getComment(),  contact->getTypeInfo(), contact->getId() , true);

    return contactInfo;
}

bool DbInterface::deleteContactFromMemory(int index)
{
    Logger::log("deleteContactFromMemory: index in contactList = "+ QVariant(index).toString());
    Logger::log("contactList value in index = "+ QVariant(index).toString()+ " is "+contactList[index]->toString());

    bool returnValue = false;
    if(index < 0 || index >= contactList.length())
        return returnValue;
    Contact * contact = contactList[index];
    returnValue = true;
    returnValue &= deleteContactFromAllGroups( contact);

    if(contact->getTypeInfo() == COMMERCIAL)
    {
        returnValue &= (Repository::getInstance())->deleteCommercialContact(phoneOwner.getId(),contact->getId());
    }
    else
    {
        returnValue &= (Repository::getInstance())->deleteGeneralContact(phoneOwner.getId(),contact->getId());
    }
    if( returnValue)
    {
        delete contact;
        contactList.removeAt(index);
    }

    return returnValue;
}

bool DbInterface::deleteContactFromAllGroups(Contact * contact)
{
    bool returnValue = true;
    int groupLength = groupList.length();

    Logger::log("deleteContactFromAllGroups : "+contact->toString());
    Logger::log("groupLength : "+QVariant(groupLength).toString());

    for(int i=0; i< groupLength; i++ )
    {
        Group *group = groupList[i];
        Logger::log("*********** 1");
        group->printGroupMembers();
        Logger::log("*********** 2" );
        returnValue = group->deleteContactFromMemberList(contact, phoneOwner.getId());
        if(returnValue && group->getMemberListLength() == 0)
        {
            returnValue = (Repository::getInstance())->deleteGroupFromDB(phoneOwner.getId(),groupList[i]->getId());
            groupList.removeAt(i);
            i--;
            groupLength--;
        }
    }
    return returnValue;
}

bool DbInterface::updateContact(ContactInfo *contactInfo)
{
    bool returnValue = true;

    if (contactInfo->getTypeInfo() == COMMERCIAL)
        returnValue = repositoryPtr->updateCommertialContact(contactInfo);
    else
        returnValue = repositoryPtr->updateGeneralContact(contactInfo);

    if( returnValue )
    {
        returnValue = updateContactInContactList( contactInfo);
    }

    return returnValue;
}

bool DbInterface::updateContactInContactList( ContactInfo *contactInfo)
{
    bool returnValue = true;
    int contactIndexInContactList = (SearchEngine::getInstance())->getContactIndexInContactList();

    Logger::log(QVariant(contactIndexInContactList).toString());

    Contact * contact = contactList[contactIndexInContactList];
    if(!contact)
        returnValue = false;
    else
        contact->setValues(contactInfo->getId(), contactInfo->getFullName(), contactInfo->getAddress(), contactInfo->getPostalcode(),
                       contactInfo->getEmail(), contactInfo->getPhoneNumber(), contactInfo->getComment(), contact->getMarked());

    return returnValue;
}

int DbInterface::indexOfContactInContactList( QString contactId, QString ContactType)
{
//    Logger::log(contactId+ " "+ ContactType);
    int CLlength = contactList.length();
//    int CLlength = getLengthOfContactList();
    for ( int i = 0 ; i < CLlength ; i++ )
    {
//        QString CId = getIdOfContactInPlaceOfIndexInContactList(i);
//        QString CType = getTypeOfContactInPlaceOfIndexInContactList(i);
        QString CId = contactList[i]->getId();
        QString CType = contactList[i]->getTypeInfo();
        if(CId == contactId && CType == ContactType ){
//            Logger::log("founded "+ CId + " "+ CType);
            return i;
        }
    }
    Logger::log("Can not find "+contactId + " contactId with " + ContactType + " type");
    return -1;
}

//int DbInterface::getLengthOfContactList()
//{
//    return contactList.length();
//}

//QString DbInterface::getIdOfContactInPlaceOfIndexInContactList(int indexInContactList)
//{
//    return contactList[indexInContactList]->getId();
//}
//QString DbInterface::getTypeOfContactInPlaceOfIndexInContactList(int indexInContactList)
//{
//    return contactList[indexInContactList]->getTypeInfo();
//}
