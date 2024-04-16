#include "repository.h"
#include "dbinterface.h"
#include <QSqlError>

Repository* Repository::repositoryPtr= nullptr;;

Repository::Repository()
{

}

Repository::~Repository()
{
//    Logger::log( "Repository destructor executed");
}

Repository *Repository::getInstance()
{
    if(repositoryPtr==nullptr){
        repositoryPtr = new Repository();
//        Logger::log("new Repository");
    }
    return repositoryPtr;
}

PhoneOwner Repository::fetchOwnerInformation(QString phone)
{
    QSqlQuery qry;
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

//QSqlQueryModel* Repository::searchText(QString txtSearch, PhoneOwner owner)
//{
//    return searchInFullNameColomn(txtSearch,owner);
//}


//QSqlQueryModel* Repository::searchInFullNameColomn(QString txtSearch, PhoneOwner &owner)
//{
//    QSqlQuery qry;
//    QSqlQueryModel *model = new QSqlQueryModel();

//    qry.prepare("select id, ownerId, fullname, phone, address, postalcode, email,marked from general "
//                "where ownerid = :id and fullname = :fullname"
//                " union "
//                "select id, ownerId, fullname, phone, address, postalcode, email,marked from commercial "
//                                "where ownerid = :id and fullname = :fullname");
//    qry.bindValue(":fullname", txtSearch);
//    qry.bindValue(":id", owner.getId());

//    if(qry.exec()){
//        model->setQuery(qry);
//        if(model->rowCount() >0){
//            return model;
//        }
//        else
//            Logger::log("empty value returned from DB.");
//    }
//    else{
//        Logger::log("query execution error " );
//    }
//    return nullptr;
//}

bool Repository::loadGroups(QString ownerId)
{
    bool returnValue = true;
    QSqlQuery qry;
    qry.prepare("select id, name, description from groups where ownerid = :id");

    qry.bindValue(":id", ownerId);

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
    QSqlQuery qry;
    qry.prepare("select CommercialId from GroupMembersOfCommercialContacts "
                "where ownerid = :ownerId and groupId = :groupId"
                );

    qry.bindValue(":ownerId", ownerId);
    qry.bindValue(":groupId", groupId);

    if(qry.exec()){
        while(qry.next()){
            QString commercialId = qry.value(0).toString();
            int index = indexOfContactInContactList(commercialId, "General");
            if( index >= 0 )
                (DbInterface::getInstance())->appendNewMemberForGroup(index, groupId);
            else
            {
                returnValue = false;
            }
        }

    }
    else{
        Logger::log("query execution error for loading commercial group members" );
        returnValue = false;
    }
//    group.printGroupMembers();

    return returnValue;

}

bool Repository::loadGeneralGroupMembers(QString ownerId, QString groupId)
{
    bool returnValue = true;
    QSqlQuery qry;
    qry.prepare("select GeneralId from GroupMembersOfGeneralContacts "
                "where ownerid = :ownerId and groupId = :groupId"
                );

    qry.bindValue(":ownerId", ownerId);
    qry.bindValue(":groupId", groupId);

    if(qry.exec()){
        while(qry.next()){
            QString generalId = qry.value(0).toString();
            int index = indexOfContactInContactList(generalId, "General");
            if( index >= 0 )
                (DbInterface::getInstance())->appendNewMemberForGroup(index, groupId);
            else
            {
                returnValue = false;
            }
        }
    }
    else{
        Logger::log("query execution error for loading general group members" );
        returnValue = false;
    }
//    group.printGroupMembers();

    return returnValue;
}


int Repository::indexOfContactInContactList( QString contactId, QString ContactType)
{
    int CLlength = (DbInterface::getInstance())->getLengthOfContactList();
    for ( int i = 0 ; i < CLlength ; i++ )
    {
        QString CId = (DbInterface::getInstance())->getIdOfContactInPlaceOfIndexInContactList(i);
        QString CType = (DbInterface::getInstance())->getTypeOfContactInPlaceOfIndexInContactList(i);
        if(CId == contactId && CType == ContactType ){
            return i;
        }
    }
    Logger::log("Can not find "+contactId + " contactId with " + ContactType + " type");
    return -1;
}

bool Repository::loadContacts(QString ownerId)
{
    return loadGeneralContacts(ownerId) && loadCommercialContacts(ownerId);
}

bool Repository::loadGeneralContacts(QString ownerId)
{
    bool returnValue = true;
    QSqlQuery qry;
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
    QSqlQuery qry;
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
    QSqlQuery qry;
    if(contactInfo->getTypeInfo() != "Commercial")
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
                    id, //id
                    contactInfo->getFullName(),     //fullname
                    contactInfo->getPhoneNumber(),  //phone
                    contactInfo->getAddress(),      //address
                    contactInfo->getPostalcode(),   //postalcode
                    contactInfo->getEmail(),        //email
                    false,                          //marked
                    contactInfo->getComment()       //comment
                    );
        Logger::log(commercial->toString());
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
    QSqlQuery qry;
    if(contactInfo->getTypeInfo() != "General")
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
                    id, //id
                    contactInfo->getFullName(),     //fullname
                    contactInfo->getPhoneNumber(),  //phone
                    contactInfo->getAddress(),      //address
                    contactInfo->getPostalcode(),   //postalcode
                    contactInfo->getEmail(),        //email
                    false,                          //marked
                    contactInfo->getComment()       //comment
                    );
        Logger::log(general->toString());
        (DbInterface::getInstance())->appendContact(general);

    }
    else{
        Logger::log("Saving general contact error: "+ qry.lastError().text() );
        returnValue = false;
    }

    return returnValue;
}

bool Repository::deleteCommercialGroupContactRelation(QString ownerId, QString groupId, QString comercialId)
{
    bool returnValue = true;

    return returnValue;
}

bool Repository::deleteGeneralGroupContactRelation(QString ownerId, QString groupId, QString generalId)
{
    bool returnValue = true;

    return returnValue;
}

bool Repository::deleteGroupFromDB(QString ownerId, QString groupId)
{
    bool returnValue = true;

    return returnValue;
}

//void MainWindow::on_pushButton_2_clicked()
//{
//    QString id,family,name;
//    id = ui->txt_id->text();
//    name = ui->txt_name->text();
//    family = ui->txt_family->text();
//    if(!conopen()){
//        qDebug() << "Failed to open database";
//        return;
//    }
//    else {
//        QSqlQuery qry;
//        qry.prepare("update tbl set name= '"+name+"',family= '"+family+"' where id = '"+id+"' " );
//        if(qry.exec()){
//            QMessageBox::critical(this,"update","updated");
//            conclose();
//        }
//        else{
//            QMessageBox::critical(this,"error:",qry.lastError().text());
//            conclose();
//        }
//    }
//}

//void MainWindow::on_pushButton_3_clicked()
//{
//    QString id,family,name;
//    id = ui->txt_id->text();
//    name = ui->txt_name->text();
//    family = ui->txt_family->text();
//    if(!conopen()){
//        qDebug() << "Failed to open database";
//        return;
//    }
//    else {
//        QSqlQuery qry;
//        qry.prepare("delete from tbl  where id = '"+id+"' " );
//        if(qry.exec()){
//            QMessageBox::critical(this,"delete","deleted");
//            conclose();
//        }
//        else{
//            QMessageBox::critical(this,"error:",qry.lastError().text());
//            conclose();
//        }
//    }
//}

//void MainWindow::on_pushButton_4_clicked()
//{
//    QSqlQueryModel *model = new QSqlQueryModel();
//    QString id,family,name;
//    id = ui->txt_id->text();
//    name = ui->txt_name->text();
//    family = ui->txt_family->text();
//    if(!conopen()){
//        qDebug() << "Failed to open database";
//        return;
//    }
//    else {
//        QSqlQuery qry;
//        qry.prepare("select * from tbl" );

//        if(qry.exec()){
//            model->setQuery(qry);
//            ui->tableView->setModel(model);
//            qDebug() << model->rowCount();
//            QMessageBox::critical(this,"select","selected");
//            conclose();
//        }
//        else{
//            QMessageBox::critical(this,"error:",qry.lastError().text());
//            conclose();
//        }
//    }
//}

