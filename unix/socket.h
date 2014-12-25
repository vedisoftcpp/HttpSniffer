#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <unistd.h>
#include <string>

class Socket
{
public:
    Socket();
    Socket(int socket);
    ~Socket();

    void bind(int port);
    void listen();
    bool is_closed();
    void close();

    Socket accept();
    void send(const std::string& msg);
    std::string recv();

private:
    int _socket;

public:
    static void initialize();
    static void clean_up();
};

#endif // SOCKET_H
