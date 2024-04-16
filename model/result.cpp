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

void Result::decreaseIndex()
{
    if(indexInContactList>0)
        indexInContactList--;
    else
        Logger::log("Unpredicted situation, indexInContactList = "+ QVariant(indexInContactList).toString());
}
