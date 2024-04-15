#include "searchengine.h"

bool SearchEngine::searchInSensitive(QString txtSearch, QList<Contact *> &contactList, QList<Result*> &resultList)
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
            Logger::log("done");
            Result * result = new Result(i,contact);
            resultList.append(result);
            returnValue = true;
        }
    }

    return returnValue;
}


SearchEngine::SearchEngine()
{

}


