#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <QString>
#include "logger.h"
#include "../model/phoneowner.h"
#include "../model/commercial.h"
#include "../model/general.h"
#include "../model/result.h"

class SearchEngine
{
protected:
    bool searchInFullName(QString txtSearch, QList<Contact*> &contactList, QList<Result> &resultList);

public:
    SearchEngine();


};

#endif // SEARCHENGINE_H
