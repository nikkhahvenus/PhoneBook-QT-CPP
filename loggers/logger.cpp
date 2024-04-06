#include "logger.h"

Logger* Logger::loggerPtr= nullptr;
//QString Logger::fileName("logFile.txt");
//QFile Logger::outFile(fileName);

Logger::Logger()
{
//    if(!outFile.open(QFile::Text | QFile::Append)){ //QFile::WriteOnly
//        qDebug() << "Could not open the file in write mode!";
//        return;
//    }
//    out.setDevice(&outFile);
}

Logger::~Logger()
{
//    if(outFile.isOpen()){
//        qDebug() << "Log file closed";
//        outFile.close();
//    }

}

void Logger::makeLogger()
{
    if(loggerPtr==nullptr){
        loggerPtr = new Logger();
    }
}
Logger* Logger::getInstance()
{
    makeLogger();
    return loggerPtr;
}
void Logger::dLog(QString str)
{
    qDebug() << str;
}
void Logger::cLog(QString str)
{
    qInfo() << str;
}
//void Logger::fLog(QString str)
//{
//    if(loggerPtr==nullptr){
//        makeLogger();
//    }
//    if(!outFile.open(QFile::Text | QFile::Append)){ //QFile::WriteOnly
//        qDebug() << "Could not open the file in write mode!";
//        return;
//    }
//    out.setDevice(&outFile);
//    out<< str;
//    outFile.flush();
//}
