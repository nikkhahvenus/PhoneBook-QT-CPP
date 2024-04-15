#include "result.h"

Result::Result()
{

}

Result::Result(int index, Contact * contactPtr)
{
    this->indexInContactList = index;
    this->contactPtr = contactPtr;
}

QString Result::toString()
{
    return QString(indexInContactList) + " : " + contactPtr->toString();
}
