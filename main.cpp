#include "mainwindow.h"
#include"start_page.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setFixedSize(500,350);
    Start_page start_page(&w);

    return a.exec();
}
