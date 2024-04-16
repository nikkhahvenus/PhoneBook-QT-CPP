#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include "../model/phoneowner.h"
#include "../model/commercial.h"
#include "../model/general.h"
#include "../model/group.h"

class Repository
{
protected:
    static Repository* repositoryPtr;
    Repository();
private:
    bool loadGeneralContacts(QString ownerId);
    bool loadCommercialContacts(QString ownerId);
    int indexOfContactInContactList(QString , QString );

public:
    ~Repository();
    Repository(Repository &other) = delete;
    void operator=(const Repository &) = delete;

    static Repository *getInstance();

    PhoneOwner fetchOwnerInformation(QString);
    bool loadContacts(QString);
    bool loadGroups(QString);
    bool loadCommercialGroupMembers(QString , QString);
    bool loadGeneralGroupMembers(QString , QString);

    //add Contact
    bool inserContactIntoCommertialTable(QString ,ContactInfo*);
    bool inserContactIntoGeneralTable(QString ,ContactInfo*);
    //delete Contact
    bool deleteCommercialGroupContactRelation(QString , QString , QString );
    bool deleteGeneralGroupContactRelation(QString , QString , QString );
    bool deleteGroupFromDB(QString ownerId, QString groupId);
    bool deleteCommercialContact(QString , QString );
    bool deleteGeneralContact(QString , QString );
};

#endif // REPOSITORY_H

