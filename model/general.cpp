#include "general.h"

General::General(): Contact()
{
    Logger::log("No argument constructor of General executed");
}

General::General(QString id, QString fullName, QString address, QString postalcode,
                 QString email, QString phoneNumber, QString comment, bool marked)
    :Contact( id, fullName, address, postalcode, email, phoneNumber, comment, marked)
{
    Logger::log("With argument constructor of General executed");
}

QString General::typeInfo()
{
    return "General";
}
