#ifndef CREATOR_H
#define CREATOR_H

#include "mainwindow.h"
#include "template_behavour.h"
#include "socket_adapter.h"

#include <QObject>
#include <QStringList>
#include <QApplication>
#include <QQueue>

class Creator : public QObject{
    Q_OBJECT

private:

    Creator(Creator const& other)            = delete;
    Creator& operator=(Creator const& other) = delete;
    Creator(Creator && other)                = delete;
    Creator& operator=(Creator && other)     = delete;
    void creating_connect(Behavour_id behavour_id);

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
};

#endif // CREATOR_H
