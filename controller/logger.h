#ifndef LOGGER_H
#define LOGGER_H
#include <QString>
#include <QDebug>
enum logTypeS{DEBUGLOG,CONSOLELOG,FILELOG};

class Logger
{
protected:
    Logger();
    static bool logFlag;
private:
    static void makeLogger();
    static int selection ;
    //debug Logger
    static void dLog(QString str);
    //console Logger
    static void cLog(QString str);

public:
    ~Logger();

    //selective logger
    static void log(QString str);
    static void setSelection(int selectValue);


};


#endif // LOGGER_H
