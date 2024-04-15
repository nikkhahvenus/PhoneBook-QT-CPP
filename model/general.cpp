#include "general.h"

General::General(): Contact()
{
//    Logger::log("No argument constructor of General executed");
}


//General::General(General *general)
//    :Contact( general->id, general->fullName, general->address, general->postalcode, general->email, general->phoneNumber, general->comment, general->marked)
//{

//}

General::General(QString id, QString fullName, QString phoneNumber, QString address,
                 QString postalcode, QString email, bool marked, QString comment)
    :Contact( id, fullName, address, postalcode, email, phoneNumber, comment, marked)
{
//    Logger::log("With argument constructor of General executed");
}

QString General::getTypeInfo()
{
    return "General";
}

//General::General(ContactInfo *contactInfo):
//    Contact(contactInfo->getId(), contactInfo->getFullName(), contactInfo->getAddress(),
//            contactInfo->getPostalcode(), contactInfo->getEmail(), contactInfo->getPhoneNumber(), contactInfo->getComment(), false)
//{

//}

//General& General::operator=(General general)
//{
//    setValues(general.id, general.fullName, general.address, general.postalcode,
//              general.email, general.phoneNumber, general.comment, general.marked);
//    return *this;
//}
