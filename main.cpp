#include "view/mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QSplashScreen *splash = new QSplashScreen;
    //    splash->setPixmap(QPixmap("../phoneBookApp/image/phoneBook.jpg"));
    //    splash->show();
    //    QTimer::singleShot(2500,splash,SLOT(close()));
    //    QTimer::singleShot(2500,&w,SLOT(show()));

    w.show();
    return a.exec();
}
