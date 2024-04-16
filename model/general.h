#ifndef GENERAL_H
#define GENERAL_H

#include "contact.h"

//mokhatab haye omoomi
class General : public Contact
{
public:
    General();
    General(QString id, QString fullName, QString phoneNumber, QString address,
            QString postalcode, QString email, bool marked, QString comment);
    QString getTypeInfo();

};

#endif // GENERAL_H
