#ifndef DBINTERFACE_H
#define DBINTERFACE_H
#include "../model/phoneowner.h"
#include "logger.h"
#include "repository.h"
#include "../model/ContactInfo.h"
#include "../model/search.h"

class DbInterface
{
protected:
    static DbInterface* dbInterfacePtr;
    DbInterface();
    Repository *repo;

private:
    PhoneOwner phoneOwner;
    QList<Contact*> contactList;
    QList<Group*> groupList;
//    QList<int, Contact*> contactList;

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

    bool searchText(QString txtSearch);
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
};

#endif // DBINTERFACE_H
