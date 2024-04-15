#include "result.h"

Result::Result()
{

}

Result::Result(int index)
{
    this->indexInContactList = index;
}

QString Result::toString()
{
    return QString(indexInContactList);
}

int Result::getIndex()
{
    return indexInContactList;
}
