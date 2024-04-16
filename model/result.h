#ifndef RESULT_H
#define RESULT_H
#include "contact.h"

class Result
{
private:
    int indexInContactList;

public:
    Result();
    Result(int);
    QString toString();

    int getIndex();
    void decreaseIndex();

};

#endif // RESULT_H
