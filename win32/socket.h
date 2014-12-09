#ifndef SOCKET_H
#define SOCKET_H

#include "../ISocket.h"
#include "../headers.h"

class Socket : public ISocket
{
public:
    Socket();
    Socket(SOCKET socket);
    ~Socket();

    void bind(int port);
    void listen();
    Socket accept();

public:
    static void initialize();
    static void clean_up();

private:
    SOCKET _socket;

};

#endif // SOCKET_H
