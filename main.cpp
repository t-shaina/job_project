#include "mainwindow.h"
#include"start_page.h"
#include"app_page.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //w.setFixedSize(500,350);
    Start_page start_page(&w);
    //Socket socket_to_db(&w);
    QObject::connect(&start_page, SIGNAL(logged_in(QString)), &w, SLOT(set_username(QString)));
    QObject::connect(&start_page, SIGNAL(logged_in(QString)), &w, SLOT(resize_window()));
    //QObject::connect(&start_page, &Start_page::logged_in, &w, &MainWindow::set_username);
    App_page app_page(&w);
    //QObject::connect(&start_page, SIGNAL(logged_in(QString)), &app_page, SLOT(set_app_page_visible(true)));
    //QObject::connect(&start_page, SIGNAL(logged_in(QString)), &start_page, SLOT(set_start_page_visible(true)));
    //start_page.set_start_page_visible(true);
    //app_page.set_app_page_visible(false);
    return a.exec();
}
