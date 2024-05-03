#include "socket_adapter.h"
#include<QDataStream>

const QString repeat_error_string          = "Ошибка сети, повторите действие еще раз";
const QString host_not_found_error_string  = "Адрес хоста не найден, перезапустите приложение с другими данными";
const QString network_error_string         = "Ошибка сети, проверьете сетевой кабель и перезапустите приложение";
const QString default_network_error_string = "Ошибка сети";


ISocket_adapter::ISocket_adapter(QObject* parent){

}

ISocket_adapter:: ~ISocket_adapter(){

}

Socket_adapter::Socket_adapter(QObject* parent, QTcpSocket* p_socket)
    :ISocket_adapter(parent)
    , block_size_in(0){
    if (p_socket == 0){
        socket_ = new QTcpSocket(this);
    }
    else socket_ = p_socket;
    buffer = new Buffer();
    connect(socket_, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket_, SIGNAL(disconnected()), this, SLOT(on_disconnected()));
}

Socket_adapter::~Socket_adapter(){
    delete buffer;
    delete socket_;
}
void Socket_adapter::readyRead(){
    QByteArray buf;
    QDataStream in(socket_);
    while (true){
        if (block_size_in == 0){
            if (socket_->bytesAvailable() < sizeof(int))
                return;
            in >> block_size_in;
        }
        else {
            if (socket_->bytesAvailable() < block_size_in)
            return;
            in >> buf;
            block_size_in = 0; // тут добавить прорверку, что все блоки пришли
            emit have_new_message(buf);
        }
    }
}

void Socket_adapter::on_disconnected(){
    emit disconnected();
}

bool Socket_adapter::send(const QByteArray& message){
    if (socket_->state() == QAbstractSocket::ConnectingState){
        socket_->waitForConnected(1000);
    }
    bool error = 1;
    if (socket_->isValid() && socket_->state() == QAbstractSocket::ConnectedState){
        QByteArray block;
        QDataStream sendStream(&block, QIODevice::ReadWrite);
        sendStream << quint16(0) << message;
        sendStream.device()->seek(0);
        sendStream << (quint16)(block.size() - sizeof(quint16));
        if (socket_->write(block) == -1){
            error = 0;
            on_socket_error(socket_->error(), message);
        }
    }
    else {
        error = 0;
        on_socket_error(socket_->error(), message);
    }
    return error;
}

void Socket_adapter::sendData(const QByteArray& message){
    if (!buffer->is_empty()){
        buffer->push(message);
        resendData();
    }
    else send(message);
}

void Socket_adapter::resendData(){
    socket_->connectToHost(host, port);
    while (!buffer->is_empty()) {
        if (!send(buffer->head()))
            return;
        else buffer->pop();
    }
}

void Socket_adapter::on_socket_error(QTcpSocket::SocketError error, const QByteArray& data){
    switch (error) {
    case QAbstractSocket::ConnectionRefusedError:
        buffer->push(data);
        emit error_with_connection(repeat_error_string);
        break;
    case QAbstractSocket::RemoteHostClosedError:
        buffer->push(data);
        emit error_with_connection(repeat_error_string);
        break;
    case QAbstractSocket::SocketResourceError:
        buffer->push(data);
        emit error_with_connection(repeat_error_string);
        break;
    case QAbstractSocket::SocketTimeoutError:
        buffer->push(data);
        emit error_with_connection(repeat_error_string);
        break;
    case QAbstractSocket::UnknownSocketError:
        emit error_with_connection(repeat_error_string);
        break;
    case QAbstractSocket::HostNotFoundError:
        emit error_with_connection(host_not_found_error_string);
        break;
    case QAbstractSocket::NetworkError:
        emit error_with_connection(network_error_string);
        break;
    default:
        emit error_with_connection(default_network_error_string);
        break;
    }
}
