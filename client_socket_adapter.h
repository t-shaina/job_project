#ifndef CLIENT_SOCKET_ADAPTER_H
#define CLIENT_SOCKET_ADAPTER_H

#include"socket_adapter.h"

class Client_socket_adapter:public Socket_adapter{
    Q_OBJECT

public:

    explicit Client_socket_adapter(QObject* parent);
};

#endif // CLIENT_SOCKET_ADAPTER_H
