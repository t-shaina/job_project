#ifndef CREATOR_H
#define CREATOR_H

#include "socket.h"
#include "mainwindow.h"
#include "template_behavour.h"
#include <QObject>
#include<QStringList>

class Creator:public QObject
{
    Q_OBJECT
private:
    MainWindow* main_window;
    Socket* socket;
    Template_behavour* behavour;
public:
    Creator();
    ~Creator();
public slots:
    void create_query(QStringList* data);
    void on_data_received(QStringList*);
};

#endif // CREATOR_H
