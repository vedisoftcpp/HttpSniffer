#include "socket.h"
#include "../utils.h"

#include <iostream>

Socket::Socket()
{
}

Socket::Socket(int socket) :
    _socket(socket)
{
}

Socket::~Socket()
{
    //::close(_socket);
}

void Socket::bind(int port)
{
    sockaddr_in addr;
    _socket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1) {
        std::cout << "socket failed with error\n";
        return;
    }
    ::memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    if (::bind(_socket, (sockaddr *) &addr, sizeof(struct sockaddr_in)) == -1)
        std::cout << "bind error\n";
}

void Socket::listen()
{
    if (::listen(_socket, SOMAXCONN) == -1)
    {
        std::cout << "listen failed with error\n";
    }
}

bool Socket::is_closed()
{
    int nSendBytes = ::send(_socket, "\0", 1, MSG_NOSIGNAL);
    if (nSendBytes == -1)
    {
         return true;
    }
    return false;
}

void Socket::close()
{
    ::close(_socket);
}

Socket Socket::accept()
{
    int client_socket = ::accept(_socket, NULL, NULL);
    if (client_socket == -1)
    {
        std::cout << "accept failed with error\n";
        //::close(_socket);
    }
    return Socket(client_socket);
}

void Socket::send(const std::string& msg)
{
    int iSendResult = ::send( _socket, msg.c_str(), msg.length(), MSG_NOSIGNAL );
    if (iSendResult == -1)
    {
        std::cout << "send failed with error\n";
    }
}

std::string Socket::recv()
{
    char recvbuf[512];
    int recvbuflen = 512;
    int iResult = ::recv(_socket, recvbuf, recvbuflen, 0);
    if (iResult > 0)
    {
//        std::cout << "Bytes received: " << recvbuf << "\n";
//        std::cout << "Bytes length: " << iResult << "\n\n";
        return std::string(recvbuf, iResult);
    }
    return std::string("");
}

void Socket::initialize()
{
}

void Socket::clean_up()
{
}
