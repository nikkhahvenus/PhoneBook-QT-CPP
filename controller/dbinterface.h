#ifndef DBINTERFACE_H
#define DBINTERFACE_H
#include "../model/phoneowner.h"


class DBInterface
{
private:
    static PhoneOwner phoneOwner;
public:
    DBInterface();

    static PhoneOwner getPhoneOwner();
    bool findOwnerInformation();
};

#endif // DBINTERFACE_H
