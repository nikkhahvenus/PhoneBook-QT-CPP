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

    bool updateContactInContactList(ContactInfo *contactInfo);
    bool deleteContactFromMemberList(Group *group, Contact *contact, QString ownerId);
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
    Contact *getContactPtr(int);
    bool appendNewMemberForGroup(int , QString );

    //add contact
    bool addContact(ContactInfo *);

    //search contacts
    bool searchText(QString );
    ContactInfo getContactInfoOf(int );
    bool deleteContactFromMemory(int );
    bool deleteContactFromAllGroups(Contact * );

    //edit contact
    bool updateContact(ContactInfo *);
    int indexOfContactInContactList(QString contactId, QString ContactType);
};

#endif // DBINTERFACE_H
