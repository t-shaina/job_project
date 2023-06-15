#include "socket.h"
#include<QByteArray>
Socket::Socket(QObject* parent):
    QObject(parent)
{
    client_socket= new QTcpSocket();
    connect(client_socket, SIGNAL(readyRead()), client_socket, SLOT(readData()));

    client_socket->connectToHost("127.0.0.1", 9000);


}
void Socket::readData(){
    QByteArray data_array=client_socket->readAll();
    QString data=QString::fromStdString(data_array.data());
    //emit new_data_received(data);

}
void Socket::sendData(QString message){
    if (client_socket->waitForConnected(1000)){
        client_socket->write(message.toUtf8());
    }
}


