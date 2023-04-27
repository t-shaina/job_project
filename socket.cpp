#include "socket.h"
#include<QByteArray>
Socket::Socket(QObject* parent):
    QObject(parent)
{
    client_socket= new QTcpSocket();
    connect(client_socket, SIGNAL(readyRead()), client_socket, SLOT(readTcpData()));
    client_socket->connectToHost("127.0.0.1", 9000);


}

void Socket::readTcpData(){
    QByteArray data=client_socket->readAll();//обертка или

}
void Socket::sendQuery(QString message){
    if (client_socket->waitForConnected(1000)){
        client_socket->write(message.toUtf8());
    }
}
