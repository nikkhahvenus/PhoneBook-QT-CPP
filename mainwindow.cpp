#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbclass.h"
#include <QMessageBox>
#include <QSharedPointer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    if(!DbClass::readyConnection())
    {
        QMessageBox::critical(this,"DB Connection Error:","Error occured while connecting to DB");
    }
    else
        ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    deleteDbClassInstance();
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString id,family,name;
    id = "120";
    name = "hamid";
    family = "zzz";

    QSqlQuery qry;
    qry.prepare("insert into tbl (id,name,family)  values(149, 'Dennis', 'Young')");

//        qry.prepare("INSERT INTO tbl (id,name,family) VALUES (:id,:name,:family)");
//        qry.bindValue(":id", id);
//        qry.bindValue(":name", name);
//        qry.bindValue(":family", family);

//        qry.prepare("INSERT INTO tbl (name,family) VALUES (:name,:family)");
//        qry.bindValue(":name", name);
//        qry.bindValue(":family", family);

//        qry.prepare("insert into tbl (id,name,family) values ('"+id+"','"+name+"','"+family+"')" );

//        qry.prepare("insert into tbl (name,family) values ('"+name+"','"+family+"')" );
    if(qry.exec()){
        QMessageBox::critical(this,"save","saved");

    }
    else{
        QMessageBox::critical(this,"error:",qry.lastError().text());
    }
}

void MainWindow::deleteDbClassInstance()
{
    DbClass * db = DbClass::getInstance();
    if(db){
        delete db;
    }
}
