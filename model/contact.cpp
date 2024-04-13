#include "contact.h"

Contact::~Contact()
{

}
Contact::Contact()
{
    setFullName("") ;
    setAddress("") ;
    setPostalcode("") ;
    setEmail("") ;
    setPhoneNumber("") ;
    setComment("") ;
    resetMarked();
//    Logger::log("No argument constructor of Contact executed");
}

Contact::Contact(QString id, QString fullName, QString address, QString postalcode,
                 QString email, QString phoneNumber, QString comment, bool marked)
{
    setId(id);
    setFullName(fullName) ;
    setAddress(address) ;
    setPostalcode(postalcode) ;
    setEmail(email) ;
    setPhoneNumber(phoneNumber) ;
    setComment(comment) ;
    if(marked) setMarked();
    else resetMarked();
//    Logger::log("With argument constructor of Contact executed");
}

bool Contact::setId(QString id)
{
    //validate id before assignment
    this->id = id;
    return true;
}
bool Contact::setFullName(QString fullName)
{
    //validate fullname before assignment
    this->fullName = fullName;
    return true;
}

bool Contact::setAddress(QString address)
{
    //validate address before assignment
    this->address = address;
    return true;
}

bool Contact::setPostalcode(QString postalcode)
{
    //validate postalcode before assignment
    this->postalcode = postalcode;
    return true;
}

bool Contact::setEmail(QString email)
{
    //validate email before assignment
    this->email = email;
    return true;
}

bool Contact::setPhoneNumber(QString phoneNumber)
{
    //validate phoneNumber before assignment
    this->phoneNumber = phoneNumber;
    return true;
}

bool Contact::setComment(QString comment)
{
    //validate comment before assignment
    this->comment = comment;
    return true;
}

bool Contact::setMarked()
{
    //validate marked before assignment
    this->marked = true;
    return true;
}

bool Contact::resetMarked()
{
    //validate marked before assignment
    this->marked = false;
    return true;
}

QString Contact::toString()
{
    return id + " " + fullName + " " + phoneNumber + " " + address + " " + postalcode + " " + email + " " + (marked == 1 ? "Marked" : "Unmarked") + " " + comment + " " + typeInfo();
}

QString Contact::getId()
{
    return id;
}




