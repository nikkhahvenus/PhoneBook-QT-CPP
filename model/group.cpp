#include "group.h"
#include "../controller/repository.h"

Group::Group()
{
    setGroup("0", "", "");
}

Group::Group(QString id, QString name, QString description)
{
    setGroup(id, name, description);
}

Group::~Group()
{
    clearMemberList();
}

void Group::clearMemberList()
{
    memberList.clear();
}

void Group::setGroup(QString id, QString name, QString description)
{
    setId(id);
    setName(name);
    setDescription(description);
}

QString Group::getId()
{
    return id;
}

bool Group::appendMemberList(Contact * contactPtr)
{
    memberList.append(contactPtr);
    return true;
}

QString Group::toString()
{
    return id + " " + name + " " + description;
}

void Group::printGroupMembers()
{
    Logger::log("Group name: "+ name + " , Group description: "+ description);
    for (int i=0; i < memberList.length() ; i++)
    {
        Contact * contact = memberList[i];
        Logger::log(contact->toString());
    }
}

void Group::setId(QString id)
{
    //validate it before assignment
    this->id = id;
}

void Group::setName(QString name)
{
    //validate it before assignment
    this->name = name;
}

void Group::setDescription(QString description)
{
    //validate it before assignment
    this->description = description;
}

bool Group::deleteContactFromMemberList(Contact *contact, QString ownerId)
{
    Logger::log("deleteContactFromMemberList : "+contact->toString() + " ownerId= "+ QVariant(ownerId).toString());

    bool returnValue = true;
    int memberLength = memberList.length();
    Logger::log("MemberLength = "+ QVariant(memberLength).toString());
    bool found = false;
    for(int i=0 ; i < memberLength && !found ; i++){
        if(memberList[i] == contact)
        {
            found = true;
            Logger::log("member of list with index = "+ QVariant(i).toString());
            if (contact->getTypeInfo() == COMMERCIAL)
                returnValue = (Repository::getInstance())->deleteCommercialGroupContactRelation(ownerId, id, contact->getId());
            else
                returnValue = (Repository::getInstance())->deleteGeneralGroupContactRelation(ownerId, id, contact->getId());

            Logger::log("returnValue = "+ QVariant(returnValue).toString());
            if(returnValue)
            {
                memberList.removeAt(i);
               // i--;
               // memberLength--;
            }
        }
    }
    return returnValue;
}

int Group::getMemberListLength()
{
    return memberList.length();
}
