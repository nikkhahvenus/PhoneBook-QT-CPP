#include "dbinterface.h"

DBInterface::DBInterface()
{

}

PhoneOwner DBInterface::getPhoneOwner()
{
    return phoneOwner;
}

bool DBInterface::findOwnerInformation()
{
    return false;
}
