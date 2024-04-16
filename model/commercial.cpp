#include "commercial.h"

Commercial::Commercial()
{
}



Commercial::Commercial(Commercial *commercial)
    :Contact( commercial->id, commercial->fullName, commercial->address, commercial->postalcode, commercial->email, commercial->phoneNumber, commercial->comment, commercial->marked)
{

}

Commercial::Commercial(QString id, QString fullName, QString phoneNumber, QString address,
                       QString postalcode, QString email, bool marked, QString comment)
    :Contact( id, fullName, address, postalcode, email, phoneNumber, comment, marked)
{
}

QString Commercial::getTypeInfo()
{
    return COMMERCIAL;
}




