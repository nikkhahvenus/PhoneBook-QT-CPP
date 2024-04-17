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
    static QString dbPath;
    static QString sqlCommandsFileToCreateDB ;
    static QString connectionName ;

public:
    ~DbConnector();
    DbConnector(DbConnector &other) = delete;
    void operator=(const DbConnector &) = delete;

    static DbConnector *getInstance();
    static bool readyConnection();
    static void setDbFilePath(QString);
    static void setSQLFilePath(QString);
    static QString getConnectionName();

    int ParseSqlScriptFile();

private:
    static bool openDBConnection();
    static void closeDBConnection();

};
#endif // DBCONNECTOR_H
