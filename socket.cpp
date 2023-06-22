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
    QByteArray message_array=client_socket->readAll();
    QString message=QString::fromStdString(message_array.data());
    QStringList* data=new QStringList();
    Socket::decoding_message(data, message);
    emit new_data_received(data);

}
void Socket::sendData(QStringList* data){
    QString message=Socket::encoding_message(data);
    if (client_socket->waitForConnected(1000)){
        client_socket->write(message.toUtf8());
    }
}
QString Socket::encoding_message(const QStringList* data){
    QString encoded_message;
    for (int i=0;i<data->size();i++){
        encoded_message.push_back(static_cast<char>(data->at(i).size()));
        encoded_message.push_back(data->at(i));
    }
    return encoded_message;
}
void  Socket::decoding_message(QStringList* data_list, const QString& message){
    int length=0;
    for (int i=1; i<message.size()-length-1;i+=length){//мб тут с условием выхода из for
        length=message.at(i).digitValue();
        data_list->push_back(message.sliced(i+1, length));
    }
}
