#ifndef DBCLASS_H
#define DBCLASS_H


#include <QtSql>
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
    static QString dbPath;
    const QString tableCreationCommandsFileName = "/Users/mohammadnikkhah/QT/phoneBookProject/phoneBookApp/controller/sql.sql";

public:
    ~DbClass();
    DbClass(DbClass &other) = delete;
    void operator=(const DbClass &) = delete;

    static DbClass *getInstance();
    static bool readyConnection();
    int ParseSqlScriptFile();

private:
    static bool openDBConnection();
    static void closeDBConnection();

};
#endif // DBCLASS_H
