#include "mainwindow.h"
#include"start_page.h"
#include"app_page.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setFixedSize(500,350);
    Start_page start_page(&w);
    //Socket socket_to_db(&w);
    QObject::connect(&start_page, SIGNAL(logged_in(QString)), &w, SLOT(set_username(QString)));
    //QObject::connect(&start_page, &Start_page::logged_in, &w, &MainWindow::set_username);
    App_page app_page(&w);
    return a.exec();
}
