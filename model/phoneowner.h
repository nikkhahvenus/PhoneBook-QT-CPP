#ifndef PHONEOWNER_H
#define PHONEOWNER_H

#include <QString>

class PhoneOwner
{
private:
    QString id;
    QString phone;
    QString fullName;

public:
    PhoneOwner();
    PhoneOwner(QString id,QString phone,QString fullName);
    QString getId();
    QString getPhone();
    QString getFullName();
    bool setOwner(PhoneOwner*);
    bool setOwner(PhoneOwner&);
    bool setOwner(QString id,QString phone,QString fullName);
    bool setId(QString);
    bool setPhone(QString);
    bool setFullName(QString);

    QString toString();
};

#endif // PHONEOWNER_H
