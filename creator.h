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
    //QString encoding_message(const QStringList* data);
    //QStringList decoding_message(QJsonObject* object);
    void creating_connect(Behavour_id behavour_id);
protected:
    ISocket_adapter* i_adapter;
    Template_behavour* behavour;
public:
    MainWindow* main_window;
    Creator(QApplication *parent = nullptr);
    ~Creator();
public slots:
    void create_query(QStringList* data);
    void data_received(QByteArray data);
};

#endif // CREATOR_H
