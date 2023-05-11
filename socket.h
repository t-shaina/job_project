#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include<QTcpSocket>
#include<QStringList>
#include<QString>
#include <QWidget>
class Socket: public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject* parent=nullptr);


private:
    QTcpSocket* client_socket;
public slots:
    //void newConnection();
    void readData();
    void sendData(QString message);
};

#endif // SOCKET_H
