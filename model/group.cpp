#include "group.h"

Group::Group()
{
    setGroup("0", "", "");
}

Group::Group(QString id, QString name, QString description)
{
    setGroup(id, name, description);
}

void Group::setGroup(QString id, QString name, QString description)
{
    setId(id);
    setName(name);
    setDescription(description);
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
