#ifndef GENERAL_H
#define GENERAL_H

#include "contact.h"

//mokhatab haye omoomi
class General : public Contact
{
public:
    General();
    General(QString ,QString ,QString ,QString ,QString , QString, QString ,bool );
    QString typeInfo();
};

#endif // GENERAL_H
