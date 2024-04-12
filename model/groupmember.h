#ifndef GROUPMEMBER_H
#define GROUPMEMBER_H

#include <QString>

class GroupMember
{
public:
    GroupMember();

protected:
    QString id;
    QString groupId;
    QString cantactId;
public:
    virtual ~GroupMember();

    virtual QString typeInfo() = 0;

};

#endif // GROUPMEMBER_H
