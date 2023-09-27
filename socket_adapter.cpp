#include "socket_adapter.h"
#include<QDataStream>

const QString repeat_error_string="Ошибка сети, повторите действие еще раз";
const QString host_not_found_error_string="Адрес хоста не найден, перезапустите приложение с другими данными";
const QString network_error_string="Ошибка сети, проверьете сетевой кабель и перезапустите приложение";
const QString default_network_error_string="Ошибка сети";


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
    buffer=new Buffer();
    connect(socket_, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket_, SIGNAL(disconnected()), this, SLOT(on_disconnected()));
    //connect(socket_, SIGNAL(socket_error(QTcpSocket::SocketError, const QByteArray&)), this, SLOT(on_socket_error(QTcpSocket::SocketError, const QByteArray&)));

}
/*void Socket_adapter::connect_to_host(QString&&  host, quint16 port){
    socket_->connectToHost(host, port);
    if(!socket_->waitForConnected(10000)){
        //emit no_connection(socket_->error());
        qDebug()<<"in client_socket_adapter error is"<<socket_->errorString();
    }
}*/

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
            //qDebug() <<buf;
            emit have_new_message(buf);
        }
    }
}
void Socket_adapter::on_disconnected(){
    //socket_->deleteLater();
    emit disconnected();
}
bool Socket_adapter::send(const QByteArray& message){
    qDebug()<<"in send";
    //socket_->connectToHost(host, port);
    //qDebug()<<"error is"<<socket_->error();
    //qDebug()<<socket_->state();
    if(socket_->state()==QAbstractSocket::ConnectingState){
        socket_->waitForConnected(1000);
    }
    bool error=1;
    if(socket_->isValid()&&socket_->state()==QAbstractSocket::ConnectedState){
        QByteArray block;
        QDataStream sendStream(&block, QIODevice::ReadWrite);
        sendStream << quint16(0) << message;
        sendStream.device()->seek(0);
        sendStream << (quint16)(block.size() - sizeof(quint16));
        qDebug()<<"in sendData block_size " << (quint16)(block.size() - sizeof(quint16));
        if(socket_->write(block)==-1){
            error=0;
            on_socket_error(socket_->error(), message);
        }
    }
    else {
        error=0;
        on_socket_error(socket_->error(), message);
    }
    return error;
}
void Socket_adapter::sendData(const QByteArray& message){
    qDebug()<<"in sendData";

    //if(!buffer->is_empty()) qDebug()<<"buffer head"<<buffer->head().toStdString();
    if(!buffer->is_empty()){
        qDebug()<<"in sendData buffer is not empty";
        buffer->push(message);
        resendData();
    }
    else send(message);
    qDebug()<<"in sendData also socket is"<<socket_;

}
void Socket_adapter::resendData(){
    qDebug()<<"in resendData";
    socket_->connectToHost(host, port);
    while (!buffer->is_empty()) {
        if(!send(buffer->head()))
            return;
        else buffer->pop();
    }
}
void Socket_adapter::on_socket_error(QTcpSocket::SocketError error, const QByteArray& data){
    qDebug()<<socket_->state();
    qDebug()<<error;
    switch (error) {
    case QAbstractSocket::ConnectionRefusedError:
        buffer->push(data);
        emit error_with_connection(repeat_error_string);
        break;
    case QAbstractSocket::RemoteHostClosedError:
        buffer->push(data);
        emit error_with_connection(repeat_error_string);
        break;
    case QAbstractSocket::SocketResourceError:                                           //разобрать что делать
        buffer->push(data);
        emit error_with_connection(repeat_error_string);
        break;
    case QAbstractSocket::SocketTimeoutError:
        buffer->push(data);
        emit error_with_connection(repeat_error_string);
        break;
    case QAbstractSocket::UnknownSocketError:
        //buffer->push(data);
        emit error_with_connection(repeat_error_string);
        break;
    case QAbstractSocket::HostNotFoundError:
        emit error_with_connection(host_not_found_error_string);
        break;
    case QAbstractSocket::NetworkError:
        emit error_with_connection(network_error_string);
        break;
    default:
        //buffer->push(data);
        emit error_with_connection(default_network_error_string);
        break;
    }
}
