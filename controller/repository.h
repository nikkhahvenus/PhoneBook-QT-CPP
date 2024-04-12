#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include "logger.h"
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
    QSqlQueryModel* searchInFullNameColomn(QString txtSearch,PhoneOwner &owner);
    bool loadGeneralContacts(QString ownerId,QList<Contact*>&);
    bool loadCommercialContacts(QString ownerId,QList<Contact*>&);

public:
    ~Repository();
    Repository(Repository &other) = delete;
    void operator=(const Repository &) = delete;

    static Repository *getInstance();

    PhoneOwner fetchOwnerInformation(QString );
    QSqlQueryModel* searchText(QString txtSearch, PhoneOwner owner);
    bool loadContacts(QString,QList<Contact*>&);
};

#endif // REPOSITORY_H

