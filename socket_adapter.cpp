#include "socket_adapter.h"
#include<QDataStream>
ISocket_adapter::ISocket_adapter(QObject* parent){}
ISocket_adapter:: ~ISocket_adapter(){}

Socket_adapter::Socket_adapter(QObject* parent, QTcpSocket* p_socket)
    :ISocket_adapter(parent), block_size_in(0)
{
    qDebug()<< "new Socket_adapter";
    if(p_socket==0){
        socket_=new QTcpSocket(this);
    }
    else socket_=p_socket;
    connect(socket_, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket_, SIGNAL(disconnected()), this, SLOT(on_disconnected()));

}
Socket_adapter::~Socket_adapter(){}
void Socket_adapter::readyRead(){
    qDebug()<< "in readyRead";
    QByteArray buf;
    QDataStream in(socket_);

    while(true){
        qDebug()<<"block_size_in="<< block_size_in;
        if (block_size_in==0){
            if(socket_->bytesAvailable()<sizeof(int))
                return;
            in>>block_size_in;
        }
        else{
            if(socket_->bytesAvailable()<block_size_in)
            return;

            in>>buf;
            block_size_in=0; // тут добавить прорверку, что все блоки пришли
            qDebug() <<buf;
            emit have_new_message(buf);
        }
    }
}
void Socket_adapter::on_disconnected(){
    socket_->deleteLater();
    emit disconnected();
}

void Socket_adapter::sendData(const QByteArray& message){
    QByteArray block;
    QDataStream sendStream(&block, QIODevice::ReadWrite);
    sendStream << quint16(0) << message;
    sendStream.device()->seek(0);
    sendStream << (quint16)(block.size() - sizeof(quint16));
    qDebug()<<"in sendData block_size " << (quint16)(block.size() - sizeof(quint16));
;
    qDebug()<<"in sendData block "<< block.toStdString();
    socket_->write(block);
}

