#include "commercial.h"

Commercial::Commercial()
{
    //    Logger::log("No argument constructor of Commercial executed");
}

//Commercial::Commercial(Commercial &commercial)
//    :Contact( commercial.id, commercial.fullName, commercial.address, commercial.postalcode, commercial.email, commercial.phoneNumber, commercial.comment, commercial.marked)
//{

//}

Commercial::Commercial(Commercial *commercial)
    :Contact( commercial->id, commercial->fullName, commercial->address, commercial->postalcode, commercial->email, commercial->phoneNumber, commercial->comment, commercial->marked)
{

}

Commercial::Commercial(QString id, QString fullName, QString phoneNumber, QString address,
                       QString postalcode, QString email, bool marked, QString comment)
    :Contact( id, fullName, address, postalcode, email, phoneNumber, comment, marked)
{
//    Logger::log("With argument constructor of Commercial executed");
}

QString Commercial::getTypeInfo()
{
    return "Commercial";
}

//Commercial::Commercial(ContactInfo *contactInfo):
//    Contact(contactInfo->getId(), contactInfo->getFullName(), contactInfo->getAddress(),
//            contactInfo->getPostalcode(), contactInfo->getEmail(), contactInfo->getPhoneNumber(), contactInfo->getComment(), false)
//{

//}

//Commercial& Commercial::operator=(Commercial commercial)
//{
//    setValues(commercial.id, commercial.fullName, commercial.address, commercial.postalcode,
//              commercial.email, commercial.phoneNumber, commercial.comment, commercial.marked);
//    return *this;
//}
