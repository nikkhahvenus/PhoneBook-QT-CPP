#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <QString>
#include "logger.h"
#include "../model/commercial.h"
#include "../model/general.h"
#include "../model/result.h"

class SearchEngine
{
protected:
    static SearchEngine* searchEnginePtr;
    SearchEngine();


protected:
    QList<Result*> resultList;
    int currentShowIndexOfResultList = 0;


public:
    bool searchInSensitive(QString txtSearch, QList<Contact*> &contactList);
    ~SearchEngine();
    SearchEngine(SearchEngine &other) = delete;
    void operator=(const SearchEngine &) = delete;
    static SearchEngine *getInstance();


    void clearResultList();
    void printResults();


    ContactInfo getCurrentResultItem();
    void increaseResultIndex();
    void decreaseResultIndex();
    bool lastIndex();
    bool firstIndex();
    bool deleteCurrentResultItem();
    int getNumberOfResuls();
    int getContactIndexInContactList();
};

#endif // SEARCHENGINE_H
