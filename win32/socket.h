#ifndef SOCKET_H
#define SOCKET_H

#include "../ISocket.h"
#include "../headers.h"

#include <string>

class Socket : public ISocket
{
public:
    Socket();
    Socket(SOCKET socket);
    ~Socket();

    void bind(int port);
    void listen();
    Socket accept();
    void send(const std::string& msg);

private:
    SOCKET _socket;

public:
    static void initialize();
    static void clean_up();
};

#endif // SOCKET_H
