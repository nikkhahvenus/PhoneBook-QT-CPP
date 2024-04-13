#ifndef DBINTERFACE_H
#define DBINTERFACE_H
#include "../model/phoneowner.h"
#include "logger.h"
#include "repository.h"


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

    QSqlQueryModel* searchText(QString txtSearch);
    void printContacts();
    void printGroups();
    bool InitializeForCurrentLogin();
//    void clearCommercialGroupMemberList();
};

#endif // DBINTERFACE_H
