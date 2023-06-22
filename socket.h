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
    QString encoding_message(const QStringList* data);
    static void  decoding_message(QStringList* data_list, const QString& message);
public slots:
    //void newConnection();
    void readData();
    void sendData(QStringList* data);
    //void on_new_data_received();
signals: void new_data_received(QStringList*);
};

#endif // SOCKET_H
