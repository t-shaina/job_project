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
#include<QQueue>

class Creator:public QObject
{
    Q_OBJECT
private:
    void creating_connect(Behavour_id behavour_id);

    //void try_sending();
protected:
    ISocket_adapter* i_adapter;
    Template_behavour* behavour;
public:
    MainWindow* main_window;
    Creator(QApplication *parent = nullptr);
    ~Creator();

    void set_host_port(QStringList);

public slots:
    void create_query(QStringList* data);
    void data_received(QByteArray data);
    void main_window_was_destroyed();
private slots:
    //void on_socket_error(QTcpSocket::SocketError, const QByteArray&);
};

#endif // CREATOR_H
