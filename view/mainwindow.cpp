#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../controller/dbconnector.h"
#include <QMessageBox>
#include "../controller/dbinterface.h"

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
        if(!DbInterface::getInstance()){
            QMessageBox::critical(this,"DB Interface Error:","main controller error");
        }
        else{
            ui->setupUi(this);
            setItemsVisibilityBeforeLogin();
        }
    }
}

MainWindow::~MainWindow()
{
    deleteDbConnectorInstance();
    deleteDbInterfaceInstance();
    delete ui;
}

void MainWindow::deleteDbConnectorInstance()
{
    DbConnector * db = DbConnector::getInstance();
    if(db){
        delete db;
    }
}

void MainWindow::deleteDbInterfaceInstance()
{
    DbInterface * dbInterfacePtr = DbInterface::getInstance();
    if(dbInterfacePtr){
        delete dbInterfacePtr;
    }
}

void MainWindow::deleteRepositoryInstance()
{
    Repository * repositoryPtr = Repository::getInstance();
    if(repositoryPtr){
        delete repositoryPtr;
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
    ui->frameLogin->setVisible(true);
    ui->lineEditErrorLogin->setVisible(false);

    ui->frameUser->setHidden(true);
    ui->menuBar->setHidden(true);
}

void MainWindow::setItemsVisibilityAfterLogin()
{
    ui->frameLogin->setHidden(true);

    ui->frameUser->setVisible(true);
    ui->menuBar->setVisible(true);
}


void MainWindow::on_btnLogin_clicked()
{
    QString phone = ui->lineEditLogin->text();
    if(phone.length() == 0)
        return;
    else if(DbInterface::getInstance()->fetchOwnerInformation(phone))
        setItemsVisibilityAfterLogin();
    else {
        ui->lineEditLogin->clear();
        ui->lineEditErrorLogin->setText("Invalid login information");
        ui->lineEditErrorLogin->setVisible(true);

    }


}
