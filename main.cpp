//#include "mainwindow.h"
//#include"start_page.h"
//#include"app_page.h"
#include"creator.h"
#include <QApplication>
#include"symbols_inspector.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("~/Qt/my/untitled2/icon.png"));
    Creator c(&a);


    Symbols_inspector symbols_inspector=Symbols_inspector();
    QString test="name   ";
    qDebug()<<"name with spaces is"<<test;
    QString name_without_spaces=symbols_inspector.removing_last_spaces(test);
    qDebug()<<"name without spaces is"<<name_without_spaces;
    return a.exec();
}
