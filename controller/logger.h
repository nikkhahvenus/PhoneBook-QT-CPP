#ifndef LOGGER_H
#define LOGGER_H
#include <QString>
#include <QDebug>

class Logger
{
protected:
    Logger();
    static bool logFlag;
private:
    static void makeLogger();

public:
    ~Logger();

    //debug Logger
    static void dLog(QString str);
    //console Logger
    static void cLog(QString str);

};


#endif // LOGGER_H
