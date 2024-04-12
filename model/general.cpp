#include "general.h"

General::General(): Contact()
{
    Logger::log("No argument constructor of General executed");
}

General::General(QString id, QString fullName, QString phoneNumber, QString address,
                 QString postalcode, QString email, bool marked, QString comment)
    :Contact( id, fullName, address, postalcode, email, phoneNumber, comment, marked)
{
    Logger::log("With argument constructor of General executed");
}

QString General::typeInfo()
{
    return "General";
}
