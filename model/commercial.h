#ifndef COMMERCIAL_H
#define COMMERCIAL_H

#include "contact.h"

//mokhatab haye Tejari
class Commercial : public Contact
{
public:
    Commercial();
    Commercial(QString ,QString ,QString ,QString ,QString , QString, QString ,bool);
    QString typeInfo();
};

#endif // COMMERCIAL_H
