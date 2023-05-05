#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include<QTcpSocket>
#include<QStringList>
#include <QWidget>
class Socket: public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject* parent=nullptr);
    void sendData(QString message);
private:
    QTcpSocket* client_socket;
public slots:
    //void newConnection();
    void readData();
};

#endif // SOCKET_H
