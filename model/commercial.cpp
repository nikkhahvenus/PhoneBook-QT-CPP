#include "commercial.h"

Commercial::Commercial()
{
//    Logger::log("No argument constructor of Commercial executed");
}

Commercial::Commercial(QString id, QString fullName, QString phoneNumber, QString address,
                       QString postalcode, QString email, bool marked, QString comment)
    :Contact( id, fullName, address, postalcode, email, phoneNumber, comment, marked)
{
//    Logger::log("With argument constructor of Commercial executed");
}

QString Commercial::typeInfo()
{
    return "Commercial";
}
