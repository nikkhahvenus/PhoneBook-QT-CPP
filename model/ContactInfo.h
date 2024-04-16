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
    bool valid = false;

public:
    ContactInfo();

    ~ContactInfo();
    ContactInfo(QString fullName, QString address, QString postalcode, QString email,
                QString phoneNumber, QString comment,  QString typeInfo, QString id = "", bool valid = true);
    void setId(QString id);
    QString getId();
    QString getFullName();
    QString getAddress();
    QString getPostalcode();
    QString getEmail();
    QString getPhoneNumber();
    QString getComment();
    QString getTypeInfo();
    void setValues(QString fullName, QString address, QString postalcode, QString email,
                   QString phoneNumber, QString comment,  QString typeInfo, QString id , bool valid);
    bool isValid();
};

#endif // CONTACTINFO_H
