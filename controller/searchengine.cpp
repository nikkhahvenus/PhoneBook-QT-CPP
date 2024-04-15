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
            Result * result = new Result(i);
            resultList.append(result);
            returnValue = true;
        }
    }
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
        Logger::log(resultList[i]->toString());
}

ContactInfo SearchEngine::getCurrentResultItem()
{
    ContactInfo contactInfo;
    if(resultList.length() > 0)
    {
        return (DbInterface::getInstance())->getContactInfoOf(currentShowIndexOfResultList);
    }
    return contactInfo;
}

//ContactInfo SearchEngine::getCurrentResultItem()
//{
//    ContactInfo contactInfo;
//    if(resultList.length() > 0)
//    {
//        Contact* contact = (DbInterface::getInstance())->getContactOfContactListIn(currentShowIndexOfResultList);
//        contactInfo.setValues(contact->getFullName(),  contact->getAddress, contact->getPostalcode, email,
//                          phoneNumber, comment,  typeInfo, id, valid);
//    }
//    delete contact;
//    return contactInfo;
//}
