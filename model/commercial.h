#ifndef COMMERCIAL_H
#define COMMERCIAL_H

#include "contact.h"

//mokhatab haye Tejari
class Commercial : public Contact
{
public:
    Commercial();
    Commercial(Commercial*);
    Commercial(QString id, QString fullName, QString phoneNumber, QString address,
               QString postalcode, QString email, bool marked, QString comment);
    QString getTypeInfo();

};

#endif // COMMERCIAL_H
