#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H


#include <QtSql>
#include "logger.h"

class DbConnector
{
protected:
    static DbConnector* dbConnectorPtr;
    DbConnector();

private:
    QSqlDatabase phoneDB;
    static QString dbPath;
    const QString tableCreationCommandsFileName = "/Users/mohammadnikkhah/QT/phoneBookProject/phoneBookApp/controller/sql.sql";

public:
    ~DbConnector();
    DbConnector(DbConnector &other) = delete;
    void operator=(const DbConnector &) = delete;

    static DbConnector *getInstance();
    static bool readyConnection();
    int ParseSqlScriptFile();

private:
    static bool openDBConnection();
    static void closeDBConnection();

};
#endif // DBCONNECTOR_H
