#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "../controller/logger.h"
#include "../controller/dbconnector.h"
#include "../controller/dbinterface.h"
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

    void on_lineEditSearch_returnPressed();

    void on_btnEdit_clicked();

    void on_actionLogout_triggered();

    void on_actionSelect_SQL_file_triggered();

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
    void showNumberOfSearchResults();
};
#endif // MAINWINDOW_H
