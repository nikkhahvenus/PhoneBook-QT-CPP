#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../controller/dbconnector.h"
#include <QMessageBox>
#include "../controller/dbinterface.h"
#include "../model/ContactInfo.h"

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


    ui->frameUser->setHidden(true);
    ui->menuBar->setHidden(true);

    ui->lineEditErrorLogin->setText("");
    ui->lineEditLogin->clear();

    ui->frameLogin->setVisible(true);
    ui->lineEditErrorLogin->setVisible(false);

    ui->frameLogin->show();
}

void MainWindow::setItemsVisibilityAfterLogin()
{
    ui->frameLogin->setHidden(true);

    ui->frameUser->setVisible(true);
    ui->menuBar->setVisible(true);

    ui->radioButtonGeneral->setAutoExclusive(false);
    ui->radioButtonGeneral->setChecked(true);
    ui->radioButtonGeneral->setAutoExclusive(true);

    ui->radioButtonCommercial->setAutoExclusive(false);
    ui->radioButtonCommercial->setChecked(false);
    ui->radioButtonCommercial->setAutoExclusive(true);

    ui->frameUser->show();
}


void MainWindow::on_btnLogin_clicked()
{
    QString phone = ui->lineEditLogin->text();
    if(phone.length() == 0)
        return;
    else if((DbInterface::getInstance())->fetchOwnerInformation(phone))
    {
        if((DbInterface::getInstance())->InitializeForCurrentLogin())
        {
            setItemsVisibilityAfterLogin();
        }
        else
        {
            ui->lineEditLogin->clear();
            ui->lineEditErrorLogin->setText("Initialization Failed");
            ui->lineEditErrorLogin->setVisible(true);
        }
    }
    else {
        ui->lineEditLogin->clear();
        ui->lineEditErrorLogin->setText("Invalid login information");
        ui->lineEditErrorLogin->setVisible(true);
    }
}

void MainWindow::on_btnLogout_clicked()
{
    setItemsVisibilityBeforeLogin();
    (DbInterface::getInstance())->reset();
}

void MainWindow::on_btnAddContact_clicked()
{
    QString fullName = ui->lineEditFullName->text();
    QString address = ui->lineEditAddress->text();
    QString postalcode = ui->lineEditPostalCode->text();
    QString email = ui->lineEditEmail->text();
    QString phoneNumber = ui->lineEditPhone->text();
    QString comment = ui->lineEditComment->text();
    QString typeInfo ;
    if(ui->radioButtonGeneral->isChecked())
        typeInfo = "General";
    else
        typeInfo = "Commercial";

    //Validate input values before save, like:
    if(phoneNumber == "" || fullName == "")
        return;

    ContactInfo* contactInfo = new ContactInfo(
                fullName, address, postalcode, email, phoneNumber, comment, typeInfo);
    if((DbInterface::getInstance())->addContact(contactInfo))
        QMessageBox::information(this,"Success","New contact added successfully");
    else
        QMessageBox::critical(this,"Failure","Fail to add New contact");
    delete contactInfo;
}

void MainWindow::on_btnSearch_clicked()
{
    QString txtSearch = ui->lineEditSearch->text();
    if (txtSearch.length()==0) return;

    bool returnValue = (DbInterface::getInstance())->searchText(txtSearch);
    if(returnValue)
    {
        setSearchButtons();
    }
}

void MainWindow::setSearchButtons()
{

}

void MainWindow::resetSearchButtons()
{

}














