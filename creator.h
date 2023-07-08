#ifndef CREATOR_H
#define CREATOR_H

//#include "socket.h"
#include "mainwindow.h"
#include "template_behavour.h"
#include"socket_adapter.h"
#include"client_socket_adapter.h"
#include <QObject>
#include<QStringList>
#include<QApplication>

class Creator:public QObject
{
    Q_OBJECT
private:
    MainWindow* main_window;
    //Socket* socket;
    QString encoding_message(const QStringList* data);
    QStringList decoding_message(const QString& message);
protected:
    ISocket_adapter* i_adapter;
    Template_behavour* behavour;
public:
    Creator(QApplication *parent = nullptr);
    ~Creator();
public slots:
    void create_query(QStringList* data);
    void data_received(QString data);
};

#endif // CREATOR_H
