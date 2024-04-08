#include "dbclass.h"

DbClass* DbClass::dbClassPtr= nullptr;;
QString DbClass::dbPath= "/Users/mohammadnikkhah/QT/phoneBookProject/phoneBookApp/phonebook.db";



DbClass::DbClass()
{

}
DbClass::~DbClass(){
    closeDBConnection();
    Logger::dLog( "DbClass destructor executed");
}

bool DbClass::readyConnection()
{
    if(getInstance()== nullptr){
        Logger::dLog("Space allocation for DbClass failed");
        return false;
    }
    return openDBConnection();
}


DbClass* DbClass::getInstance()
{
    if(dbClassPtr==nullptr){
        dbClassPtr = new DbClass();
        Logger::dLog("new DbClass");
    }
    return dbClassPtr;
}
void DbClass::closeDBConnection()
{
    if(dbClassPtr && dbClassPtr->phoneDB.isValid() && dbClassPtr->phoneDB.isOpen())
    {
        dbClassPtr->phoneDB.close();
        Logger::dLog("Connection closed");
    }
}

bool DbClass::openDBConnection()
{
    if(!dbClassPtr){
        Logger::dLog("Run GetInstance to make an instance of DbClass then run openDBConnection");
        return false;
    }
    if(dbClassPtr->phoneDB.isValid() && dbClassPtr->phoneDB.isOpen())
    {
        Logger::dLog("DB is connected in advanced: "+ dbClassPtr->phoneDB.databaseName());
        return  true;
    }
    else if(!dbClassPtr->phoneDB.isValid())
    {
        dbClassPtr->phoneDB = QSqlDatabase::addDatabase("QSQLITE");
        dbClassPtr->phoneDB.setDatabaseName(dbPath);
    }

    if(!dbClassPtr->phoneDB.open())
    {
        Logger::dLog( "Failed to open database....");
        return false;
    }
    else
    {
        Logger::dLog( "Connected...!" );
        return true;
    }
}


int DbClass::ParseSqlScriptFile()
{
    if(!(dbClassPtr->phoneDB.isValid() && dbClassPtr->phoneDB.isOpen())){
        Logger::dLog("Run readyConnection to make DB connection ready to use");
        return false;
    }
    QSqlDatabase &db= dbClassPtr->phoneDB;
    const QString & fileName = tableCreationCommandsFileName;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        Logger::dLog("Failed to open the input sql file");
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
                Logger::dLog( "Failed:" + statement + "\nReason:" + query.lastError().text());
        }
    }

    return successCount;
}
