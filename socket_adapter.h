#ifndef SOCKET_ADAPTER_H
#define SOCKET_ADAPTER_H

#include "buffer.h"

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>

const QString host_name = "127.0.0.1";
const quint16 port_name = 1234;

//Должен быть объявлен и определен
//в отдельном файле(файлах ), но для удобства так

class ISocket_adapter : public QObject{
    Q_OBJECT

public:

    explicit ISocket_adapter(QObject* parent);
    virtual ~ISocket_adapter();
    virtual void sendData(const QByteArray& str)=0;
    virtual void set_host(const QString&)=0;
    virtual void set_port(const QString&)=0;

protected slots:

    virtual void on_socket_error(QTcpSocket::SocketError error, const QByteArray& data)=0;

protected:

    virtual void resendData()=0;
    virtual bool send(const QByteArray& str)=0;
};

class Socket_adapter : public ISocket_adapter{
    Q_OBJECT

protected:

    QTcpSocket* socket_;
    qint16 block_size_in;
    Buffer* buffer;
    QString host = host_name;
    quint16 port = port_name;

public:

    QStringList* received_data;
    Socket_adapter(QObject* parent, QTcpSocket* p_socket = 0);
    virtual ~Socket_adapter();
    virtual  void sendData(const QByteArray& message);
    virtual void set_host(const QString& host){this->host = host;}
    virtual void set_port(const QString& port){this->port = port.toInt();}

protected:

    virtual void resendData();
    virtual bool send(const QByteArray& str);

protected  slots:

    void on_socket_error(QTcpSocket::SocketError error, const QByteArray& data);

protected slots:

    void readyRead();   
    void on_disconnected();

signals:

    void error_with_connection(const QString&);
    void socket_error(QTcpSocket::SocketError, const QByteArray&);
    void have_new_message(QByteArray message);
    void disconnected();
};

#endif // SOCKET_ADAPTER_H
