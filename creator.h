#ifndef CREATOR_H
#define CREATOR_H

//#include "socket.h"
#include "mainwindow.h"
#include "template_behavour.h"
#include"socket_adapter.h"
#include"client_socket_adapter.h"
#include"buffer.h"
#include <QObject>
#include<QStringList>
#include<QApplication>
#include<QQueue>

class Creator:public QObject
{
    Q_OBJECT
private:
    Buffer* buffer;
    void creating_connect(Behavour_id behavour_id);
    void try_sending();
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
private slots:
    void on_socket_error(QTcpSocket::SocketError, const QByteArray&);
};

#endif // CREATOR_H
