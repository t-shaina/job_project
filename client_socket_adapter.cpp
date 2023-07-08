#include "client_socket_adapter.h"

Client_socket_adapter::Client_socket_adapter(QObject* parent)
    :Socket_adapter(parent)
{
    socket_->connectToHost("127.0.0.1", 1234);
}
