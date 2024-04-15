#ifndef RESULT_H
#define RESULT_H
#include "contact.h"

class Result
{
public:
    int indexInContactList;

public:
    Result();
    Result(int);
    QString toString();

};

#endif // RESULT_H
