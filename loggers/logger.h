#ifndef LOGGER_H
#define LOGGER_H
#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>

class Logger
{
protected:
    static Logger* loggerPtr;
//    static QString fileName;
    Logger();
//    static QFile outFile;
//    static QTextStream out;

private:
    static void makeLogger();

public:
    ~Logger();
    static Logger *getInstance();

    //debug Logger
    static void dLog(QString str);
    //console Logger
    static void cLog(QString str);
    //file Logger
//    static void fLog(QString str);
};


#endif // LOGGER_H
