#ifndef SOCKET_ADAPTER_H
#define SOCKET_ADAPTER_H

#include <QObject>
#include<QTcpSocket>
#include<QByteArray>
#include"buffer.h"

class ISocket_adapter:public QObject//Должен быть объявлен и определен  в отдельном файле(файлах ), но для удобства так
{
    Q_OBJECT
public:
    explicit ISocket_adapter(QObject* parent);
    virtual ~ISocket_adapter();
    virtual void sendData(const QByteArray& str)=0;
    virtual void set_host(const QString&)=0;
    virtual void set_port(const QString&)=0;

signals:
    void error_with_connection(const QString&);
protected slots:
    virtual void on_socket_error(QTcpSocket::SocketError error, const QByteArray& data)=0;
signals:
    //void no_connection(QAbstractSocket::SocketError);
    virtual void socket_error(QTcpSocket::SocketError, const QByteArray&);
    void have_new_message(QByteArray message);
    void disconnected();
protected:
    virtual void resendData()=0;//cannot emit an error signal
    virtual bool send(const QByteArray& str)=0;
};
class Socket_adapter:public ISocket_adapter
{
    Q_OBJECT
protected:
    QTcpSocket* socket_;
    qint16 block_size_in;
    Buffer* buffer;
    QString host="127.0.0.1";
    quint16 port=1234;


public:
    QStringList* received_data;
    Socket_adapter(QObject* parent, QTcpSocket* p_socket=0);
    virtual ~Socket_adapter();
    virtual  void sendData(const QByteArray& message);
    virtual void set_host(const QString& host){this->host=host;}
    virtual void set_port(const QString& port){this->port=port.toInt();}

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
    //void no_connection(QAbstractSocket::SocketError);
    void have_new_message(QByteArray message);
    void disconnected();
};

#endif // SOCKET_ADAPTER_H
