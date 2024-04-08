#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../controller/dbclass.h"
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

void MainWindow::deleteDbClassInstance()
{
    DbClass * db = DbClass::getInstance();
    if(db){
        delete db;
    }
}

void MainWindow::on_btnSearch_clicked()
{

}

void MainWindow::on_actionCreate_Initialize_DB_triggered()
{
    QString((DbClass::getInstance())->ParseSqlScriptFile());
}

void MainWindow::on_actionLicense_triggered()
{
     QMessageBox::about(this,"License","All rights reserved for Mr. Nikkhah.");
}

