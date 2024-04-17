#include "repository.h"
#include "dbinterface.h"
#include <QSqlError>

Repository* Repository::repositoryPtr= nullptr;;

Repository::Repository()
{
}

Repository::~Repository()
{
}

Repository *Repository::getInstance()
{
    if(repositoryPtr==nullptr){
        repositoryPtr = new Repository();
    }
    return repositoryPtr;
}

PhoneOwner Repository::fetchOwnerInformation(QString phone)
{
    QSqlDatabase  db = QSqlDatabase::database(DbConnector::getConnectionName());
    QSqlQuery qry(db);
    QSqlQueryModel *model = new QSqlQueryModel();
    PhoneOwner owner;

    qry.prepare("select * from owner where Phone = (:phone)" );
    qry.bindValue(":phone", phone);

    if(qry.exec()){
        model->setQuery(qry);
        if(model->rowCount() == 1){
            if(qry.first())
            {
                owner.setOwner(qry.value(0).toString(), qry.value(1).toString(), qry.value(2).toString());
            }
            else
                Logger::log("empty value returned from DB.");
        }
        else if(model->rowCount() > 1)
            Logger::log("more than one owner for a phone number in the DB" );
    }
    else{
        Logger::log("query execution error" );
    }
    delete model;
    return owner;
}


bool Repository::loadGroups(QString ownerId)
{
    bool returnValue = true;
    QSqlDatabase  db = QSqlDatabase::database(DbConnector::getConnectionName());
    QSqlQuery qry(db);
    qry.prepare("select id, name, description from groups where ownerid = :ownerId");

    qry.bindValue(":ownerId", ownerId);

    if(qry.exec()){
            while(qry.next()){

                Group *group = new Group(
                            qry.value(0).toString(), //id
                            qry.value(1).toString(), //name
                            qry.value(2).toString()  //description
                            );
                (DbInterface::getInstance())->appendGroup(group);
            }
    }
    else{
        Logger::log("query execution error for fetching groups" );
        returnValue = false;
    }

    return returnValue;
}

bool Repository::loadCommercialGroupMembers(QString ownerId, QString groupId)
{
    bool returnValue = true;
    QSqlDatabase  db = QSqlDatabase::database(DbConnector::getConnectionName());
    QSqlQuery qry(db);
    qry.prepare("select CommercialId from GroupMembersOfCommercialContacts "
                "where ownerid = :ownerId and groupId = :groupId"
                );

    qry.bindValue(":ownerId", ownerId);
    qry.bindValue(":groupId", groupId);

    if(qry.exec()){
        while(qry.next()){
            QString commercialId = qry.value(0).toString();
            int index = (DbInterface::getInstance())->indexOfContactInContactList(commercialId, COMMERCIAL);
            if( index >= 0 )
            {
                (DbInterface::getInstance())->appendNewMemberForGroup(index, groupId);
            }
            else
            {
                Logger::log("Can not find commercialId = "+ QVariant(commercialId).toString() + " s index in the contactList");
                returnValue = false;
            }
        }

    }
    else{
        Logger::log("query execution error for loading commercial group members" );
        returnValue = false;
    }

    return returnValue;

}

bool Repository::loadGeneralGroupMembers(QString ownerId, QString groupId)
{
    bool returnValue = true;
    QSqlDatabase  db = QSqlDatabase::database(DbConnector::getConnectionName());
    QSqlQuery qry(db);
    qry.prepare("select GeneralId from GroupMembersOfGeneralContacts "
                "where ownerid = :ownerId and groupId = :groupId"
                );

    qry.bindValue(":ownerId", ownerId);
    qry.bindValue(":groupId", groupId);
    if(qry.exec()){
        while(qry.next()){
            QString generalId = qry.value(0).toString();
            int index = (DbInterface::getInstance())->indexOfContactInContactList(generalId, GENERAL);
            if( index >= 0 )
            {
                (DbInterface::getInstance())->appendNewMemberForGroup(index, groupId);
            }
            else
            {
                Logger::log("Can not find generalId = "+ QVariant(generalId).toString() + " s index in the contactList");

                returnValue = false;
            }
        }
    }
    else{
        Logger::log("query execution error for loading general group members" );
        returnValue = false;
    }

    return returnValue;
}

bool Repository::loadContacts(QString ownerId)
{
    return loadGeneralContacts(ownerId) && loadCommercialContacts(ownerId);
}

bool Repository::loadGeneralContacts(QString ownerId)
{
    bool returnValue = true;
    QSqlDatabase  db = QSqlDatabase::database(DbConnector::getConnectionName());
    QSqlQuery qry(db);
    qry.prepare("select id, fullname, phone, address, postalcode, email,marked, comment from general "
                "where ownerid = :ownerId");

    qry.bindValue(":ownerId", ownerId);

    if(qry.exec()){
            while(qry.next()){

                General * general = new General(
                            qry.value(0).toString(), //id
                            qry.value(1).toString(), //fullname
                            qry.value(2).toString(), //phone
                            qry.value(3).toString(), //address
                            qry.value(4).toString(), //postalcode
                            qry.value(5).toString(), //email
                            qry.value(6).toBool(),   //marked
                            qry.value(7).toString()  //comment
                            );
                (DbInterface::getInstance())->appendContact(general);
            }

    }
    else{
        Logger::log("query execution error for fetching general contacts" );
        returnValue = false;
    }

    return returnValue;
}

bool Repository::loadCommercialContacts(QString ownerId)
{
    bool returnValue = true;
    QSqlDatabase  db = QSqlDatabase::database(DbConnector::getConnectionName());
    QSqlQuery qry(db);
    qry.prepare("select id, fullname, phone, address, postalcode, email,marked, comment from commercial "
                "where ownerid = :ownerId");

    qry.bindValue(":ownerId", ownerId);

    if(qry.exec()){
            while(qry.next()){

                Commercial * commercial = new Commercial(
                            qry.value(0).toString(), //id
                            qry.value(1).toString(), //fullname
                            qry.value(2).toString(), //phone
                            qry.value(3).toString(), //address
                            qry.value(4).toString(), //postalcode
                            qry.value(5).toString(), //email
                            qry.value(6).toBool(),   //marked
                            qry.value(7).toString()  //comment
                            );
                (DbInterface::getInstance())->appendContact(commercial);
            }

    }
    else{
        Logger::log("query execution error for fetching commercial contacts" );
        returnValue = false;
    }

    return returnValue;
}

bool Repository::inserContactIntoCommertialTable(QString ownerId, ContactInfo *contactInfo)
{
    bool returnValue = true;
    QSqlDatabase  db = QSqlDatabase::database(DbConnector::getConnectionName());
    QSqlQuery qry(db);
    if(contactInfo->getTypeInfo() != COMMERCIAL)
        return false;
    qry.prepare("insert into commercial (OwnerId, FullName, Phone, Address, PostalCode, Email,Comment) values (:OwnerId, :FullName, :Phone, :Address, :PostalCode, :Email, :Comment)");

    qry.bindValue(":OwnerId", ownerId);
    qry.bindValue(":FullName", contactInfo->getFullName());
    qry.bindValue(":Phone", contactInfo->getPhoneNumber());
    qry.bindValue(":Address", contactInfo->getAddress());
    qry.bindValue(":PostalCode", contactInfo->getPostalcode());
    qry.bindValue(":Email", contactInfo->getEmail());
    qry.bindValue(":Comment", contactInfo->getComment());

    if(qry.exec()){
        QString id = qry.lastInsertId().toString();

        Commercial * commercial = new Commercial(
                    id,                             //id
                    contactInfo->getFullName(),     //fullname
                    contactInfo->getPhoneNumber(),  //phone
                    contactInfo->getAddress(),      //address
                    contactInfo->getPostalcode(),   //postalcode
                    contactInfo->getEmail(),        //email
                    false,                          //marked
                    contactInfo->getComment()       //comment
                    );
        (DbInterface::getInstance())->appendContact(commercial);

    }
    else{
        Logger::log("Saving commercial contact error: "+ qry.lastError().text() );
        returnValue = false;
    }

    return returnValue;
}

bool Repository::inserContactIntoGeneralTable(QString ownerId, ContactInfo *contactInfo)
{
    bool returnValue = true;
    QSqlDatabase  db = QSqlDatabase::database(DbConnector::getConnectionName());
    QSqlQuery qry(db);
    if(contactInfo->getTypeInfo() != GENERAL)
        return false;
    qry.prepare("insert into general (OwnerId, FullName, Phone, Address, PostalCode, Email,Comment) values (:OwnerId, :FullName, :Phone, :Address, :PostalCode, :Email, :Comment)");

    qry.bindValue(":OwnerId", ownerId);
    qry.bindValue(":FullName", contactInfo->getFullName());
    qry.bindValue(":Phone", contactInfo->getPhoneNumber());
    qry.bindValue(":Address", contactInfo->getAddress());
    qry.bindValue(":PostalCode", contactInfo->getPostalcode());
    qry.bindValue(":Email", contactInfo->getEmail());
    qry.bindValue(":Comment", contactInfo->getComment());

    if(qry.exec()){
        QString id = qry.lastInsertId().toString();

        General * general = new General(
                    id,                             //id
                    contactInfo->getFullName(),     //fullname
                    contactInfo->getPhoneNumber(),  //phone
                    contactInfo->getAddress(),      //address
                    contactInfo->getPostalcode(),   //postalcode
                    contactInfo->getEmail(),        //email
                    false,                          //marked
                    contactInfo->getComment()       //comment
                    );
        (DbInterface::getInstance())->appendContact(general);

    }
    else{
        Logger::log("Saving general contact error: "+ qry.lastError().text() );
        returnValue = false;
    }

    return returnValue;
}

bool Repository::deleteCommercialGroupContactRelation(QString ownerId, QString groupId, QString commercialId)
{
    bool returnValue = true;
    QSqlDatabase  db = QSqlDatabase::database(DbConnector::getConnectionName());
    QSqlQuery qry(db);

    qry.prepare("delete from GroupMembersOfCommercialContacts"
                " where ownerid = :ownerId and groupId = :groupId and commercialId = :commercialId");

    qry.bindValue(":ownerId", ownerId);
    qry.bindValue(":groupId", groupId );
    qry.bindValue(":commercialId", commercialId);


    if(!qry.exec()){
        Logger::log("deleting commercial contact error: "+ qry.lastError().text() );
        returnValue = false;
    }

    return returnValue;
}

bool Repository::deleteGeneralGroupContactRelation(QString ownerId, QString groupId, QString generalId)
{
    bool returnValue = true;
    QSqlDatabase  db = QSqlDatabase::database(DbConnector::getConnectionName());
    QSqlQuery qry(db);

    qry.prepare("delete from GroupMembersOfGeneralContacts"
                " where ownerid = :ownerId and groupId = :groupId and generalId = :generalId");

    qry.bindValue(":ownerId", ownerId);
    qry.bindValue(":groupId", groupId );
    qry.bindValue(":generalId", generalId);

    if(!qry.exec()){
        Logger::log("deleting general contact error: "+ qry.lastError().text() );
        returnValue = false;
    }
    return returnValue;
}

bool Repository::deleteGroupFromDB(QString ownerId, QString groupId)
{
    bool returnValue = true;
    QSqlDatabase  db = QSqlDatabase::database(DbConnector::getConnectionName());
    QSqlQuery qry(db);

    qry.prepare("delete from Groups where ownerId = :ownerId and id = :groupId");

    qry.bindValue(":ownerId", ownerId);
    qry.bindValue(":groupId", groupId );

    if(!qry.exec()){
        Logger::log("deleting group error: "+ qry.lastError().text() );
        returnValue = false;
    }
    return returnValue;
}

bool Repository::deleteCommercialContact(QString ownerId,QString commercialId)
{
    bool returnValue = true;
    QSqlDatabase  db = QSqlDatabase::database(DbConnector::getConnectionName());
    QSqlQuery qry(db);

    qry.prepare("delete from commercial where ownerid = :ownerId and id = :commercialId");

    qry.bindValue(":ownerId", ownerId);
    qry.bindValue(":commercialId", commercialId );

    if(!qry.exec()){
        Logger::log("deleting commercial contact error: "+ qry.lastError().text() );
        returnValue = false;
    }
    return returnValue;
}

bool Repository::deleteGeneralContact(QString ownerId,QString generalId)
{
    bool returnValue = true;
    QSqlDatabase  db = QSqlDatabase::database(DbConnector::getConnectionName());
    QSqlQuery qry(db);

    qry.prepare("delete from general where ownerId= :ownerId and id= :generalId");

    qry.bindValue(":ownerId", ownerId);
    qry.bindValue(":generalId", generalId );

    if(!qry.exec()){
        Logger::log("deleting general contact error: "+ qry.lastError().text() );
        returnValue = false;
    }
    return returnValue;
}

bool Repository::updateCommertialContact( ContactInfo *contactInfo)
{
    bool returnValue = true;
    QSqlDatabase  db = QSqlDatabase::database(DbConnector::getConnectionName());
    QSqlQuery qry(db);

    qry.prepare("update commercial set FullName = :FullName , Phone=:Phone, Address=:Address, PostalCode=:PostalCode, Email=:Email, Comment=:Comment "
                " where id= :commercialId");

    qry.bindValue(":commercialId", contactInfo->getId() );
    qry.bindValue(":FullName", contactInfo->getFullName());
    qry.bindValue(":Phone", contactInfo->getPhoneNumber());
    qry.bindValue(":Address", contactInfo->getAddress());
    qry.bindValue(":PostalCode", contactInfo->getPostalcode());
    qry.bindValue(":Email", contactInfo->getEmail());
    qry.bindValue(":Comment", contactInfo->getComment());

    if(!qry.exec()){
        Logger::log("update commercial contact error: "+ qry.lastError().text() );
        returnValue = false;
    }
    return returnValue;
}

bool Repository::updateGeneralContact( ContactInfo *contactInfo)
{
    bool returnValue = true;
    QSqlDatabase  db = QSqlDatabase::database(DbConnector::getConnectionName());
    QSqlQuery qry(db);

    qry.prepare("update general set FullName = :FullName , Phone=:Phone, Address=:Address, PostalCode=:PostalCode, Email=:Email, Comment=:Comment "
                " where id= :generalId");

    qry.bindValue(":generalId", contactInfo->getId() );
    qry.bindValue(":FullName", contactInfo->getFullName());
    qry.bindValue(":Phone", contactInfo->getPhoneNumber());
    qry.bindValue(":Address", contactInfo->getAddress());
    qry.bindValue(":PostalCode", contactInfo->getPostalcode());
    qry.bindValue(":Email", contactInfo->getEmail());
    qry.bindValue(":Comment", contactInfo->getComment());

    if(!qry.exec()){
        Logger::log("update general contact error: "+ qry.lastError().text() );
        returnValue = false;
    }
    return returnValue;
}
