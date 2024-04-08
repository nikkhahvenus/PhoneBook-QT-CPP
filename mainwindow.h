#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbclass.h"

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

    void on_actionQuit_triggered();

    void on_actionLicense_triggered();


private:
    Ui::MainWindow *ui;
    void deleteDbClassInstance();
};
#endif // MAINWINDOW_H
