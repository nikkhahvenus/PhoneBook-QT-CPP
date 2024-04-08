#include "logger.h"
bool Logger::logFlag = true;
Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::dLog(QString str)
{
    if(logFlag)
        qDebug() << str;
}
void Logger::cLog(QString str)
{
    if(logFlag)
        qInfo() << str;
}
