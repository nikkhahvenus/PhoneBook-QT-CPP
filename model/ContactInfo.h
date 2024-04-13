#ifndef CONTACTINFO_H
#define CONTACTINFO_H

#include <QString>

class ContactInfo
{
private:
    QString id;
    QString fullName;
    QString address;
    QString postalcode;
    QString email;
    QString phoneNumber;
    QString comment;
    QString typeInfo;

public:
    ContactInfo();

    ~ContactInfo();
    ContactInfo(QString fullName, QString address, QString postalcode, QString email,
                QString phoneNumber, QString comment,  QString typeInfo, QString id = "");
    void setId(QString id);
    QString getId();
    QString getFullName();
    QString getAddress();
    QString getPostalcode();
    QString getEmail();
    QString getPhoneNumber();
    QString getComment();
    QString getTypeInfo();

};

#endif // CONTACTINFO_H
