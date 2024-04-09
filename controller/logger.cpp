#include "logger.h"
bool Logger::logFlag = true;
int Logger::selection = 0;
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

void Logger::log(QString str)
{
    if (selection == DEBUGLOG) dLog(str);
    else if (selection == CONSOLELOG) cLog(str);
    else cLog(str);
}
void Logger::setSelection(int selectValue)
{
    if(selectValue >= DEBUGLOG && selectValue <= FILELOG)
    {
        selection = selectValue;
    }
}
