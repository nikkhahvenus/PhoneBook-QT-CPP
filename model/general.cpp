#include "general.h"

General::General(): Contact()
{
}

General::General(QString id, QString fullName, QString phoneNumber, QString address,
                 QString postalcode, QString email, bool marked, QString comment)
    :Contact( id, fullName, address, postalcode, email, phoneNumber, comment, marked)
{
}

QString General::getTypeInfo()
{
    return GENERAL;
}
