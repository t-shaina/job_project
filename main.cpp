//#include "mainwindow.h"
//#include"start_page.h"
//#include"app_page.h"
#include"creator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("~/Qt/my/untitled2/icon.png"));
    Creator c(&a);

    //w.setFixedSize(500,350);
    //Start_page start_page(&w);
    //Socket socket_to_db(&w);




    //QObject::connect(&start_page, SIGNAL(logged_in(QString)), &app_page, SLOT(set_app_page_visible(true)));
    //QObject::connect(&start_page, SIGNAL(logged_in(QString)), &start_page, SLOT(set_start_page_visible(true)));
    //start_page.set_start_page_visible(true);
    //app_page.set_app_page_visible(false);
    return a.exec();
}
