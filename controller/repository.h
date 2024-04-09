#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include "logger.h"
#include "../model/phoneowner.h"


class Repository
{
protected:
    static Repository* repositoryPtr;
    Repository();
private:
    QSqlQueryModel* searchInFullNameColomn(QString txtSearch,PhoneOwner &owner);
public:
    ~Repository();
    Repository(Repository &other) = delete;
    void operator=(const Repository &) = delete;

    static Repository *getInstance();

    PhoneOwner fetchOwnerInformation(QString );
    QSqlQueryModel* searchText(QString txtSearch, PhoneOwner owner);
};

#endif // REPOSITORY_H

