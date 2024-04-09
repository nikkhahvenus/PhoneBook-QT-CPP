#include "repository.h"
Repository* Repository::repositoryPtr= nullptr;;

Repository::Repository()
{

}

Repository::~Repository()
{
    Logger::dLog( "Repository destructor executed");
}

Repository *Repository::getInstance()
{
    if(repositoryPtr==nullptr){
        repositoryPtr = new Repository();
        Logger::dLog("new Repository");
    }
    return repositoryPtr;
}

PhoneOwner Repository::fetchOwnerInformation(QString phone)
{
    QSqlQuery qry;
    QSqlQueryModel *model = new QSqlQueryModel();
    PhoneOwner owner;
    qry.prepare("select * from owner where Phone = (:phone)" );
    qry.bindValue(":phone",phone);

    if(qry.exec()){
        model->setQuery(qry);
        Logger::dLog("Selected " + QString(model->rowCount()) + " rows");
    }
    else{
        Logger::dLog("qry execution error" );
        owner.setId("0");
    }
    return owner;
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

