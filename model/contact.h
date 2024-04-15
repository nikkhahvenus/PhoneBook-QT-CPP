#ifndef CONTACT_H
#define CONTACT_H

#include <QString>
#include "../controller/logger.h"
#include "ContactInfo.h"

class Contact
{
protected:
    QString id;
    QString fullName;
    QString address;
    QString postalcode;
    QString email;
    QString phoneNumber;
    QString comment;
    bool marked;

    Contact();
    Contact(QString ,QString ,QString ,QString ,QString , QString, QString ,bool );
    bool setId(QString);
    bool setFullName(QString);
    bool setAddress(QString);
    bool setPostalcode(QString);
    bool setEmail(QString);
    bool setPhoneNumber(QString);
    bool setComment(QString);
    bool setMarked();
    bool resetMarked();

public:
    QString toString();
    QString getId();
    QString getFullName();
    QString getAddress();
    QString getPostalcode();
    QString getEmail();
    QString getPhoneNumber();
    QString getComment();
    virtual ~Contact();
    virtual QString typeInfo() = 0;
};

#endif // CONTACT_H
