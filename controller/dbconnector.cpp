#include "dbconnector.h"

DbConnector* DbConnector::dbConnectorPtr= nullptr;;
QString DbConnector::dbPath= "/Users/mohammadnikkhah/QT/phoneBookProject/phoneBookApp/phonebook.db";



DbConnector::DbConnector()
{


}
DbConnector::~DbConnector(){
    closeDBConnection();
    Logger::log( "DbConnector destructor executed");
}

bool DbConnector::readyConnection()
{
    if(getInstance()== nullptr){
        Logger::log("Space allocation for DbConnector failed");
        return false;
    }
    return openDBConnection();
}


DbConnector* DbConnector::getInstance()
{
    if(dbConnectorPtr==nullptr){
        dbConnectorPtr = new DbConnector();
        Logger::log("new DbConnector");
    }
    return dbConnectorPtr;
}
void DbConnector::closeDBConnection()
{
    if(dbConnectorPtr && dbConnectorPtr->phoneDB.isValid() && dbConnectorPtr->phoneDB.isOpen())
    {
        dbConnectorPtr->phoneDB.close();
        Logger::log("Connection closed");
    }
}

bool DbConnector::openDBConnection()
{
    if(!dbConnectorPtr){
        Logger::log("Run GetInstance to make an instance of DbConnector then run openDBConnection");
        return false;
    }
    if(dbConnectorPtr->phoneDB.isValid() && dbConnectorPtr->phoneDB.isOpen())
    {
        Logger::log("DB is connected in advanced: "+ dbConnectorPtr->phoneDB.databaseName());
        return  true;
    }
    else if(!dbConnectorPtr->phoneDB.isValid())
    {
        dbConnectorPtr->phoneDB = QSqlDatabase::addDatabase("QSQLITE");
        dbConnectorPtr->phoneDB.setDatabaseName(dbPath);
    }

    if(!dbConnectorPtr->phoneDB.open())
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
    if(!(dbConnectorPtr->phoneDB.isValid() && dbConnectorPtr->phoneDB.isOpen())){
        Logger::log("Run readyConnection to make DB connection ready to use");
        return false;
    }
    QSqlDatabase &db= dbConnectorPtr->phoneDB;
    const QString & fileName = tableCreationCommandsFileName;
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

    return successCount;
}
