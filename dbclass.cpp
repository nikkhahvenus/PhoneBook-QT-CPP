#include "dbclass.h"

DbClass* DbClass::dbClassPtr= nullptr;;

DbClass::DbClass()
{

}
DbClass::~DbClass(){
    closeDBConnection();
    Logger::dLog( "DbClass destructor executed");
}

bool DbClass::readyConnection()
{
    if(getInstance()== nullptr){
        Logger::dLog("Space allocation for DbClass failed");
        return false;
    }
    return openDBConnection();
}


DbClass* DbClass::getInstance()
{
    if(dbClassPtr==nullptr){
        dbClassPtr = new DbClass();
        Logger::dLog("new DbClass");
    }
    return dbClassPtr;
}
void DbClass::closeDBConnection()
{
    if(dbClassPtr && dbClassPtr->phoneDB.isValid() && dbClassPtr->phoneDB.isOpen())
    {
        dbClassPtr->phoneDB.close();
        Logger::dLog("Connection closed");
    }
}

bool DbClass::openDBConnection()
{
    if(!dbClassPtr){
        Logger::dLog("Run GetInstance to make an instance of DbClass then run openDBConnection");
        return false;
    }
    if(dbClassPtr->phoneDB.isValid() && dbClassPtr->phoneDB.isOpen())
    {
        Logger::dLog("DB is connected in advanced: "+ dbClassPtr->phoneDB.databaseName());
        return  true;
    }
    else if(!dbClassPtr->phoneDB.isValid())
    {
        dbClassPtr->phoneDB = QSqlDatabase::addDatabase("QSQLITE");
        //complete path to DB is required
        dbClassPtr->phoneDB.setDatabaseName("/Users/mohammadnikkhah/QT/phoneBookProject/phoneBookApp/phonebook.db");
    }

    if(!dbClassPtr->phoneDB.open())
    {
        Logger::dLog( "Failed to open database....");
        return false;
    }
    else
    {
        Logger::dLog( "Connected...!" );
        return true;
    }
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

