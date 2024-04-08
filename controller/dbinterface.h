#ifndef DBINTERFACE_H
#define DBINTERFACE_H
#include "../model/phoneowner.h"
#include "logger.h"

class DbInterface
{
protected:
    static DbInterface* dbInterfacePtr;
    DbInterface();

private:
    PhoneOwner phoneOwner;

public:
    ~DbInterface();
    DbInterface(DbInterface &other) = delete;
    void operator=(const DbInterface &) = delete;

    static DbInterface *getInstance();
    QString getPhoneOwner_s_Phone();
    QString getPhoneOwner_s_FullName();

    bool fetchOwnerInformation(QString phoneNumber);
};

#endif // DBINTERFACE_H
