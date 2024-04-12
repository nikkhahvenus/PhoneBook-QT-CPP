#ifndef GROUP_H
#define GROUP_H
#include <QString>

class Group
{
public:
    Group();
    Group(QString id, QString name, QString description);
    void setId(QString);
    void setName(QString);
    void setDescription(QString);
    void setGroup(QString id, QString name, QString description);
private:
    QString id;
    QString name;
    QString description;
};

#endif // GROUP_H
