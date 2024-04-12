#include "repository.h"
Repository* Repository::repositoryPtr= nullptr;;

Repository::Repository()
{

}

Repository::~Repository()
{
    Logger::log( "Repository destructor executed");
}

Repository *Repository::getInstance()
{
    if(repositoryPtr==nullptr){
        repositoryPtr = new Repository();
        Logger::log("new Repository");
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

QSqlQueryModel* Repository::searchText(QString txtSearch, PhoneOwner owner)
{
    return searchInFullNameColomn(txtSearch,owner);
}


QSqlQueryModel* Repository::searchInFullNameColomn(QString txtSearch, PhoneOwner &owner)
{
    QSqlQuery qry;
    QSqlQueryModel *model = new QSqlQueryModel();

    qry.prepare("select id, ownerId, fullname, phone, address, postalcode, email,marked from general "
                "where ownerid = :id and fullname = :fullname"
                " union "
                "select id, ownerId, fullname, phone, address, postalcode, email,marked from commercial "
                                "where ownerid = :id and fullname = :fullname");
    qry.bindValue(":fullname", txtSearch);
    qry.bindValue(":id", owner.getId());

    if(qry.exec()){
        model->setQuery(qry);
        if(model->rowCount() >0){
            return model;
        }
        else
            Logger::log("empty value returned from DB.");
    }
    else{
        Logger::log("query execution error" );
    }
    return nullptr;
}

bool Repository::loadContacts(QString ownerId, QList<Contact*> &contactList)
{
    return loadGeneralContacts(ownerId, contactList) && loadCommercialContacts(ownerId, contactList);
}

bool Repository::loadGeneralContacts(QString ownerId, QList<Contact*> &contactList)
{
    bool returnValue = false;
    QSqlQuery qry;
    qry.prepare("select id, fullname, phone, address, postalcode, email,marked, comment from general "
                "where ownerid = :id");

    qry.bindValue(":id", ownerId);

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
                contactList.append(general);
            }
        returnValue = true;
    }
    else{
        Logger::log("query execution error for fetching general contacts" );
    }

    return returnValue;
}

bool Repository::loadCommercialContacts(QString ownerId, QList<Contact*> &contactList)
{
    bool returnValue = false;
    QSqlQuery qry;
    qry.prepare("select id, fullname, phone, address, postalcode, email,marked, comment from commercial "
                "where ownerid = :id");

    qry.bindValue(":id", ownerId);

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
                contactList.append(commercial);
            }
        returnValue = true;
    }
    else{
        Logger::log("query execution error for fetching commercial contacts" );
    }

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

