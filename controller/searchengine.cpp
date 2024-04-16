#include "searchengine.h"
#include "dbinterface.h"

SearchEngine* SearchEngine::searchEnginePtr= nullptr;;

SearchEngine::SearchEngine()
{

}

SearchEngine::~SearchEngine()
{
    clearResultList();
}

SearchEngine *SearchEngine::getInstance()
{
    if(searchEnginePtr== nullptr){
        searchEnginePtr = new SearchEngine();
//        Logger::log("new SearchEngine");
    }
    return searchEnginePtr;
}

bool SearchEngine::searchInSensitive(QString txtSearch, QList<Contact *> &contactList)
{
    QString txtSearchLower = txtSearch.toLower();
    bool returnValue = false;

    for(int i = 0 ; i < contactList.length() ; i++)
    {
        Contact * contact = contactList[i];

        if(     (contact->getFullName()).toLower().contains(txtSearchLower)
                || (contact->getAddress()).toLower().contains(txtSearchLower)
                || (contact->getPostalcode()).toLower().contains(txtSearchLower)
                || (contact->getEmail()).toLower().contains(txtSearchLower)
                || (contact->getPhoneNumber()).toLower().contains(txtSearchLower)
                || (contact->getComment()).toLower().contains(txtSearchLower)
          )
        {
//            Logger::log("in "+ QString(i)+ " "+contact->toString());
            Result * result = new Result(i);
//            Logger::log(result->toString());
            resultList.append(result);
            returnValue = true;
        }
    }
//    Logger::log("************");
//    printResults();
//    Logger::log("************");
    currentShowIndexOfResultList = 0;
    return returnValue;
}

void SearchEngine::clearResultList()
{
    if(resultList.isEmpty())
        return;
    for(int i = 0; i < resultList.length() ; i++)
            delete resultList[i];

    resultList.clear();
}

void SearchEngine::printResults()
{
    for(int i =0; i < resultList.length() ; i++)
    {
        Logger::log(resultList[i]->toString());
    }
}

ContactInfo SearchEngine::getCurrentResultItem()
{
    ContactInfo contactInfo;
    if(resultList.length() > 0)
    {
        return (DbInterface::getInstance())->getContactInfoOf(resultList[ currentShowIndexOfResultList]->getIndex());
    }
    return contactInfo;
}

bool SearchEngine::deleteCurrentResultItem()
{
    bool returnValue = false;
    if(resultList.length() <= 0)
    {
        Logger::log("Empty result list. Can not delete from it.");
        return returnValue;
    }

    returnValue = (DbInterface::getInstance())->deleteContactFromMemory(resultList[ currentShowIndexOfResultList]->getIndex());

    if(returnValue)
    {
        resultList.removeAt(currentShowIndexOfResultList);
        if(currentShowIndexOfResultList == resultList.length() && resultList.length() > 0)
            currentShowIndexOfResultList--;

        if(currentShowIndexOfResultList == -1)
        {
           Logger::log("******** Unpredicted situation");
        }
    }
    return returnValue;
}

//ContactInfo SearchEngine::deleteCurrentResultItem()
//{
//    ContactInfo contactInfo;
//    if(resultList.length() <= 0)
//    {
//        Logger::log("Empty result list. Can not delete from it.");
//        return contactInfo; //Invalid contact info is returned
//    }

//    (DbInterface::getInstance())->deleteContactFromMemory(resultList[ currentShowIndexOfResultList]->getIndex());

//    resultList.removeAt(currentShowIndexOfResultList);
//    if(currentShowIndexOfResultList == resultList.length() && resultList.length() > 0)
//        currentShowIndexOfResultList--;
//    else if(currentShowIndexOfResultList == 0)
//        return contactInfo; //Invalid contact info is returned

//    if(currentShowIndexOfResultList == -1)
//    {
//       Logger::log("******** Unpredicted situation");
//    }

//    contactInfo = (DbInterface::getInstance())->getContactInfoOf(resultList[ currentShowIndexOfResultList]->getIndex());
//    return contactInfo;
//}

void SearchEngine::increaseResultIndex()
{
    if(currentShowIndexOfResultList < resultList.length()-1)
    {
        ++currentShowIndexOfResultList;
    }
}

void SearchEngine::decreaseResultIndex()
{
    if(currentShowIndexOfResultList > 0)
    {
        --currentShowIndexOfResultList;
    }
}

bool SearchEngine::lastIndex()
{
    if(currentShowIndexOfResultList == resultList.length()-1)
        return true;
    return false;
}

bool SearchEngine::firstIndex()
{
    if(currentShowIndexOfResultList == 0)
        return true;
    return false;
}
