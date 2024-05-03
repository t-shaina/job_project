#include "creator.h"

#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("~/Qt/my/untitled2/icon.png"));
    Creator c(&a);
    if(argc > 0){
        QCommandLineParser parser;
        parser.process(a);
        c.set_host_port(parser.positionalArguments());
    }

    return a.exec();
}
