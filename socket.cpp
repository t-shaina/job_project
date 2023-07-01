#include "socket.h"
#include<QByteArray>
Socket::Socket(QObject* parent):
    QObject(parent)
{
    client_socket= new QTcpSocket();
    received_data=new QStringList();
    received_data->reserve(600);
    connect(client_socket, SIGNAL(readyRead()), this, SLOT(read_data()));
    client_socket->connectToHost("127.0.0.1", 9000);
}
Socket::~Socket(){
    delete client_socket;
    delete received_data;
}
void Socket::read_data(){
    QDataStream stream(client_socket);
    stream.setVersion(QDataStream::Qt_4_0);
    //QByteArray block_size_array=client_socket->read(sizeof(int));//считывание
    //quint16 block_size;
        //=block_size_array.toInt();
    if (block_size==0){
        if(client_socket->bytesAvailable()<(int)sizeof(quint16))
            return;
        stream>>block_size;
    }
    if(client_socket->bytesAvailable()<block_size)
        return;

    QString message;
    stream>>message;
    block_size=0;
    //received_data=new QStringList();
    Socket::decoding_message(message);
    emit new_data_received();

}
void Socket::sendData(QStringList* data){
    QString message=Socket::encoding_message(data);
    QByteArray block;
    QDataStream stream(&block, QIODevice::ReadWrite);
    if (client_socket->waitForConnected(1000)){
        stream<<quint16(0)<<message;
        stream.device()->seek(0);
        stream<<(quint16)(block.size()-sizeof(quint16));
        client_socket->write(block);
    }
}
QString Socket::encoding_message(const QStringList* data){
    QString* encoded_message=new QString(data->at(0));
    for (int i=1;i<data->size();i++){
        encoded_message->push_back(static_cast<char>(data->at(i).size()));
        encoded_message->push_back(data->at(i));
    }
    return *encoded_message;
}
void  Socket::decoding_message(const QString& message){
    received_data->clear();
    int length=0;
    received_data->push_back(message.at(0));
    for (int i=1; i<message.size()-length-1;i+=length){//мб тут с условием выхода из for
        length=message.at(i).digitValue();
        received_data->push_back(message.sliced(i+1, length));
    }
}
