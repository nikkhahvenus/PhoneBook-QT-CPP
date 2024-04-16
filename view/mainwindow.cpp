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
    deleteDbInterfaceInstance();
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

    //ui->frameLogin->show();
}

void MainWindow::setItemsVisibilityAfterLogin()
{
    ui->frameLogin->setHidden(true);

    ui->frameUser->setVisible(true);
    ui->menuBar->setVisible(true);

    setViewCommercialTypeTo(false);

    setItemsVisiblityBeforeSearch();

//    ui->frameUser->show();
}

void MainWindow::setViewCommercialTypeTo(bool flag)
{
    ui->radioButtonGeneral->setAutoExclusive(false);
    ui->radioButtonGeneral->setChecked(!flag);
    ui->radioButtonGeneral->setAutoExclusive(true);

    ui->radioButtonCommercial->setAutoExclusive(false);
    ui->radioButtonCommercial->setChecked(flag);
    ui->radioButtonCommercial->setAutoExclusive(true);
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
    //(SearchEngine::getInstance)->clearResultList();

    clearFrameSearchItems();
    clearFrameContactInfoItems();
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
        setItemsVisiblityAfterSearch();
        ContactInfo contactInfo = (SearchEngine::getInstance())->getCurrentResultItem();
        checkValidityOfContactInfoToShowOnFrame(contactInfo);
        checkNextAndPreviousButtons();
        showNumberOfSearchResults();
    }
}

void MainWindow::showNumberOfSearchResults()
{
    int numberOfResults = (SearchEngine::getInstance())->getNumberOfResuls();
    ui->lblResultNumber->setText(QStringLiteral("Result#: %1 ").arg(numberOfResults));
}

void MainWindow::setItemsVisiblityAfterSearch()
{
    ui->frameSearchButtons->setVisible(true);
    ui->btnAddContact->setHidden(true);
    ui->widget->setEnabled(false);
    ui->lblResultNumber->setVisible(true);
}

void MainWindow::setItemsVisiblityBeforeSearch()
{
    ui->frameSearchButtons->setHidden(true);
    ui->btnAddContact->setVisible(true);
    ui->widget->setEnabled(true);
    ui->lblResultNumber->setVisible(false);
}

void MainWindow::on_btnCancel_clicked()
{
    setItemsVisiblityBeforeSearch();
    (SearchEngine::getInstance())->clearResultList();

    clearFrameSearchItems();
    clearFrameContactInfoItems();
}

void MainWindow::showContactInfoOnFrame(ContactInfo contactInfo)
{
    ui->lineEditFullName->setText( contactInfo.getFullName());
    ui->lineEditAddress->setText( contactInfo.getAddress());
    ui->lineEditPostalCode->setText( contactInfo.getPostalcode());
    ui->lineEditEmail->setText( contactInfo.getEmail());
    ui->lineEditPhone->setText( contactInfo.getPhoneNumber());
    ui->lineEditComment->setText( contactInfo.getComment());
    setViewCommercialTypeTo(contactInfo.getTypeInfo() == "Commercial");
}

void MainWindow::clearFrameContactInfoItems()
{
    ui->lineEditFullName->clear();
    ui->lineEditAddress->clear();
    ui->lineEditPostalCode->clear();
    ui->lineEditEmail->clear();
    ui->lineEditPhone->clear();
    ui->lineEditComment->clear();
    setViewCommercialTypeTo(false);

}

void MainWindow::clearFrameSearchItems()
{
    ui->lineEditSearch->clear();
}

void MainWindow::on_btnNext_clicked()
{
    (SearchEngine::getInstance())->increaseResultIndex();
    ContactInfo contactInfo = (SearchEngine::getInstance())->getCurrentResultItem();
    checkValidityOfContactInfoToShowOnFrame(contactInfo);
    checkNextAndPreviousButtons();
}

void MainWindow::checkNextAndPreviousButtons()
{
    if((SearchEngine::getInstance())->firstIndex())
        ui->btnPrevious->setEnabled(false);
    else
        ui->btnPrevious->setEnabled(true);

    if((SearchEngine::getInstance())->lastIndex())
        ui->btnNext->setEnabled(false);
    else
        ui->btnNext->setEnabled(true);
}

void MainWindow::on_btnPrevious_clicked()
{
    (SearchEngine::getInstance())->decreaseResultIndex();
    ContactInfo contactInfo = (SearchEngine::getInstance())->getCurrentResultItem();
    checkValidityOfContactInfoToShowOnFrame(contactInfo);
    checkNextAndPreviousButtons();
}

void MainWindow::on_btnDelete_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Delete");
    msgBox.setText("Are you sure that you want to delete the contact?");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::No)
        return;
    if(! (SearchEngine::getInstance())->deleteCurrentResultItem())
    {
        QMessageBox::critical(this,"Contact Deletion Error:","Error occured while deleting the selected contact");
    }
    ContactInfo contactInfo = (SearchEngine::getInstance())->getCurrentResultItem();
    checkValidityOfContactInfoToShowOnFrame(contactInfo);
    checkNextAndPreviousButtons();
    showNumberOfSearchResults();
}

void MainWindow::checkValidityOfContactInfoToShowOnFrame(ContactInfo &contactInfo)
{
//    if(contactInfo.isValid())
//    {
        Logger::log("*****   Show ContactInfo on the frame");
        showContactInfoOnFrame(contactInfo);
//    }
}

void MainWindow::on_lineEditSearch_returnPressed()
{
    on_btnSearch_clicked();
}

void MainWindow::on_btnEdit_clicked()
{
    QString fullName = ui->lineEditFullName->text();
    QString address = ui->lineEditAddress->text();
    QString postalcode = ui->lineEditPostalCode->text();
    QString email = ui->lineEditEmail->text();
    QString phoneNumber = ui->lineEditPhone->text();
    QString comment = ui->lineEditComment->text();
    //typeInfo of a contact is not editable yet
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
//    if((DbInterface::getInstance())->addContact(contactInfo))
//        QMessageBox::information(this,"Success","Contact edited successfully");
//    else
//        QMessageBox::critical(this,"Failure","Fail to edit the contact");
    delete contactInfo;
}
