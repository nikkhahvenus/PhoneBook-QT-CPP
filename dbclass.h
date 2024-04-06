#ifndef DBCLASS_H
#define DBCLASS_H


#include <QtSql>
#include <QSqlQueryModel>
#include <QDebug>
#include <QMessageBox>
#include "logger.h"

class DbClass
{
protected:
    static DbClass* dbClassPtr;
    DbClass();

private:
    QSqlDatabase phoneDB;

public:
    ~DbClass();
    DbClass(DbClass &other) = delete;
    void operator=(const DbClass &) = delete;

    static DbClass *getInstance();
    static bool readyConnection();

private:
    static bool openDBConnection();
    static void closeDBConnection();

};
#endif // DBCLASS_H
