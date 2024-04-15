#ifndef DBINTERFACE_H
#define DBINTERFACE_H
#include "../model/phoneowner.h"
#include "repository.h"
#include "searchengine.h"
#include "../model/ContactInfo.h"

class DbInterface
{
protected:
    static DbInterface* dbInterfacePtr;
    DbInterface();
    Repository *repositoryPtr;
    SearchEngine *searchEnginePtr;

private:
    PhoneOwner phoneOwner;
    QList<Contact*> contactList;
    QList<Group*> groupList;


public:
    ~DbInterface();
    DbInterface(DbInterface &other) = delete;
    void operator=(const DbInterface &) = delete;

    static DbInterface *getInstance();
    QString getPhoneOwner_s_Phone();
    QString getPhoneOwner_s_FullName();

    bool fetchOwnerInformation(QString phoneNumber);
    void reset();
    bool fetchContacts();
    bool fetchGroups();
    bool fetchGroupMembers();
    void clearContactList();
    void clearGroupList();
    void printContacts();
    void printGroups();
    bool InitializeForCurrentLogin();
    bool appendContact(Contact *);
    bool appendGroup(Group *);
    int getLengthOfContactList();
    QString getIdOfContactInPlaceOfIndexInContactList(int );
    QString getTypeOfContactInPlaceOfIndexInContactList(int);
    Contact *getContactPtr(int);
    bool appendNewMemberForGroup(int , QString );

    //addContact
    bool addContact(ContactInfo *contactInfo);

    //search
    bool searchText(QString txtSearch);    
    ContactInfo getContactInfoOf(int index);
};

#endif // DBINTERFACE_H
