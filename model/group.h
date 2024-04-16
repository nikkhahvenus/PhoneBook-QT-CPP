#ifndef GROUP_H
#define GROUP_H
#include <QString>
#include "contact.h"

class Group
{
private:
    QString id;
    QString name;
    QString description;
    QList <Contact*> memberList;

private:
    void clearMemberList();

public:
    Group();
    Group(QString id, QString name, QString description);
    ~Group();
    void setId(QString);
    void setName(QString);
    void setDescription(QString);
    void setGroup(QString id, QString name, QString description);
    QString getId();
    bool appendMemberList(Contact *);

public:
    QString toString();
    void printGroupMembers();

    bool deleteContactFromMemberList(Contact *contact, QString ownerId);
    int getMemberListLength();
};

#endif // GROUP_H
