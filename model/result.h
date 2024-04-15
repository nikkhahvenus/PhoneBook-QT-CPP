#ifndef RESULT_H
#define RESULT_H
#include "contact.h"

class Result
{
public:
    int indexInContactList;
    Contact* contactPtr;

public:
    Result();
    Result(int,Contact*);
    QString toString();

};

#endif // RESULT_H
