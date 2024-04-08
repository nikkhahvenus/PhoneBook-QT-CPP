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
    QString getId();
    QString getPhone();
    QString getFullName();
    bool setPhoneNumber(QString);
    bool setFullName(QString);
};

#endif // PHONEOWNER_H
