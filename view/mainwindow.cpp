#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../controller/dbconnector.h"
#include <QMessageBox>
#include <QSharedPointer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    if(!DbConnector::readyConnection())
    {
        QMessageBox::critical(this,"DB Connection Error:","Error occured while connecting to DB");
    }
    else
    {
        ui->setupUi(this);
        setItemsVisibilityBeforeLogin(); 
    }
}

MainWindow::~MainWindow()
{
    deleteDbConnectorInstance();
    delete ui;
}

void MainWindow::deleteDbConnectorInstance()
{
    DbConnector * db = DbConnector::getInstance();
    if(db){
        delete db;
    }
}

void MainWindow::on_btnSearch_clicked()
{

}

void MainWindow::on_actionCreate_Initialize_DB_triggered()
{
    QString((DbConnector::getInstance())->ParseSqlScriptFile());
}

void MainWindow::on_actionLicense_triggered()
{
    QMessageBox::about(this,"License","All rights reserved for Mr. Nikkhah.");
}

void MainWindow::setItemsVisibilityBeforeLogin()
{
//    ui->lineEditLogin->setVisible(true);
//    ui->btnLogin->setVisible(true);
//    ui->lblLogin->setVisible(true);
    ui->frameLogin->setVisible(true);

    ui->frameUser->setHidden(true);
    ui->menuBar->setHidden(true);
//    ui->btnSearch->setHidden(true);
//    ui->lineEditSearch->setHidden(true);
}

void MainWindow::setItemsVisibilityAfterLogin()
{
//    ui->lineEditLogin->setHidden(true);
//    ui->btnLogin->setHidden(true);
//    ui->lblLogin->setHidden(true);
    ui->frameLogin->setHidden(true);

    ui->frameUser->setVisible(true);
    ui->menuBar->setVisible(true);
//    ui->btnSearch->setVisible(true);
//    ui->lineEditSearch->setVisible(true);
}


void MainWindow::on_btnLogin_clicked()
{
    QString phone = ui->lineEditLogin->text();
    Logger::dLog(phone);
    setItemsVisibilityAfterLogin();
}
