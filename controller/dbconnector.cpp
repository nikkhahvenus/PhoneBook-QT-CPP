#include "dbconnector.h"
DbConnector* DbConnector::dbConnectorPtr = nullptr;

QString DbConnector::dbPath= "phonebook1.db";
QString DbConnector::sqlCommandsFileToCreateDB = "/Users/mohammadnikkhah/QT/phoneBookProject/phoneBookApp/sql.sql";
QString DbConnector::connectionName = "dbConnection" ;


DbConnector::DbConnector()
{
}
DbConnector::~DbConnector(){
    closeDBConnection();
}

bool DbConnector::readyConnection()
{
    if(getInstance() == nullptr){
        Logger::log("Space allocation for DbConnector failed");
        return false;
    }
    return openDBConnection();
}

void DbConnector::setDbFilePath(QString newDbFilePath)
{
    //validate path before assignment
    dbPath = newDbFilePath;
}

void DbConnector::setSQLFilePath(QString newSqlFilePath)
{
    //validate file path before assignment
    sqlCommandsFileToCreateDB = newSqlFilePath;
}

QString DbConnector::getConnectionName()
{
    return connectionName;
}


DbConnector* DbConnector::getInstance()
{
    if(dbConnectorPtr==nullptr){
        dbConnectorPtr = new DbConnector();
    }
    return dbConnectorPtr;
}
void DbConnector::closeDBConnection()
{
    QSqlDatabase  db = QSqlDatabase::database(connectionName);
    if(db.isValid() && db.isOpen())
    {
        db.close();
        //QSqlDatabase::removeDatabase(connectionName);
    }
}

bool DbConnector::openDBConnection()
{

    QSqlDatabase  db = QSqlDatabase::addDatabase("QSQLITE",connectionName);
    db.setDatabaseName(dbPath);

    if(!db.open())
    {
        Logger::log( "Failed to open database....");
        return false;
    }
    else
    {
        Logger::log( "Connected...!" );
        return true;
    }
}


int DbConnector::ParseSqlScriptFile()
{
    QSqlDatabase  db = QSqlDatabase::database(connectionName);
    if(!(db.isValid() && db.isOpen())){

        Logger::log("Run readyConnection to make DB connection ready to use");
        return false;
    }

    const QString & fileName = sqlCommandsFileToCreateDB;
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        Logger::log("Failed to open the input sql file");
        return  0;
    }
    QTextStream in(&file);
    QString sql = in.readAll();
    if (sql.length() == 0)
        return 0;

    QList<int> splitPoints;
    enum { IN_STR, IN_ESC, NORMAL } state = NORMAL;
    int successCount = 0;

    for (int i = 0; i < sql.length(); i++)
    {
        const int character = sql.at(i).unicode();
        switch (state)
        {
        case IN_STR:
            switch (character)
            {
            case '\'':
                state = NORMAL;
                break;
            case '\\':
                state = IN_ESC;
                break;
            }
            break;

        case IN_ESC:
            state = IN_STR;
            break;

        case NORMAL:
            switch (character)
            {
            case ';':
                splitPoints.push_back(i);
                break;

            case '\'':
                state = IN_STR;
                break;
            }
        }
    }

    splitPoints.push_back(sql.length() - 1);

    for (int i = 0, j = 0; i < splitPoints.length(); i++)
    {
        QString statement = sql.mid(j, splitPoints.at(i) - j + 1);
        j = splitPoints.at(i) + 1;

        if (statement.trimmed().length() > 0)
        {
            QSqlQuery query(db);
            if (query.exec(statement))
                successCount++;
            else
                Logger::log( "Failed:" + statement + "\nReason:" + query.lastError().text());
        }
    }
    Logger::log("Done");
    return successCount;
}
