#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include<QTcpSocket>
#include<QStringList>
class Socket:public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject* parent=nullptr);
    void sendQuery(QString message);
private:
    QTcpSocket* client_socket;
public slots:
    //void newConnection();
    void readTcpData();
};

#endif // SOCKET_H
