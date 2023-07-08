#ifndef SOCKET_ADAPTER_H
#define SOCKET_ADAPTER_H

#include <QObject>
#include<QTcpSocket>
class ISocket_adapter:public QObject//Должен быть объявлен и определен  в отдельном файле(файлах ), но для удобства так
{
    Q_OBJECT
public:
    explicit ISocket_adapter(QObject* parent);
    virtual ~ISocket_adapter();
    virtual void sendData(const QString &str)=0;
signals:
    void have_new_message(QString message);
    void disconnected();
};
class Socket_adapter:public ISocket_adapter
{
    Q_OBJECT
protected:
    QTcpSocket* socket_;
    qint16 block_size_in;

public:
    QStringList* received_data;
    Socket_adapter(QObject* parent, QTcpSocket* p_socket=0);
    virtual ~Socket_adapter();
    virtual void sendData(const QString& message);
protected slots:
    void readyRead();   
    void on_disconnected();
signals:
    void have_new_message(QString message);
    void disconnected();
};

#endif // SOCKET_ADAPTER_H
