#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include<QTcpSocket>
#include<QStringList>
#include<QString>
#include <QDataStream>

class Socket: public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject* parent=nullptr);
    ~Socket();
    QStringList* received_data;
private:
    quint16 block_size;
    QTcpSocket* client_socket;
    QString encoding_message(const QStringList* data);
    void  decoding_message(const QString& message);
public slots:
    void read_data();
    void sendData(QStringList* data);
signals: void new_data_received();
};

#endif // SOCKET_H
