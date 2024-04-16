#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../controller/dbconnector.h"
#include "../controller/logger.h"
#include "../model/ContactInfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_btnSearch_clicked();

    void on_actionCreate_Initialize_DB_triggered();

    void on_actionLicense_triggered();
    void setItemsVisibilityBeforeLogin();
    void setItemsVisibilityAfterLogin();

    void setItemsVisiblityAfterSearch();
    void setItemsVisiblityBeforeSearch();
    void showContactInfoOnFrame(ContactInfo);
    void on_btnLogin_clicked();

    void on_btnLogout_clicked();

    void on_btnAddContact_clicked();

    void on_btnCancel_clicked();

    void on_btnNext_clicked();

    void on_btnPrevious_clicked();

    void on_btnDelete_clicked();

private:
    Ui::MainWindow *ui;
    void deleteDbConnectorInstance();
    void deleteDbInterfaceInstance();
    void deleteRepositoryInstance();
    void setViewCommercialTypeTo(bool flag);
    void clearFrameContactInfoItems();
    void clearFrameSearchItems();
    void checkNextAndPreviousButtons();
    void checkValidityOfContactInfoToShowOnFrame(ContactInfo &);
};
#endif // MAINWINDOW_H
