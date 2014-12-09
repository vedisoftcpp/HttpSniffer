#include "socket.h"
#include "../utils.h"

#include <iostream>

Socket::Socket()
{
}

Socket::Socket(SOCKET socket) :
    _socket(socket)
{
}

Socket::~Socket()
{

}

void Socket::bind(int port)
{
    int iResult;
    addrinfo *result = NULL;
    addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, t_to_string(port).c_str(), &hints, &result);
    if ( iResult != 0 )
    {
        std::cout << "getaddrinfo failed with error\n";
        WSACleanup();
    }

    _socket = ::socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (_socket == INVALID_SOCKET) {
        std::cout << "socket failed with error\n";
        freeaddrinfo(result);
        WSACleanup();
    }

    iResult = ::bind( _socket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        std::cout << "bind failed with error\n";
        freeaddrinfo(result);
        closesocket(_socket);
        WSACleanup();
    }

    freeaddrinfo(result);
}

void Socket::listen()
{
    int iResult;
    iResult = ::listen(_socket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
    {
        std::cout << "listen failed with error\n";
        closesocket(_socket);
        WSACleanup();
    }
}

Socket Socket::accept()
{
    SOCKET client_socket = ::accept(_socket, NULL, NULL);
    if (client_socket == INVALID_SOCKET)
    {
        std::cout << "accept failed with error\n";
        closesocket(_socket);
        WSACleanup();
    }
    return Socket(client_socket);
}

void Socket::send(const std::string& msg)
{
    int iSendResult = ::send( _socket, msg.c_str(), msg.length(), 0 );
    if (iSendResult == SOCKET_ERROR)
    {
        std::cout << "send failed with error\n";
        WSACleanup();
    }
}

void Socket::initialize()
{
    WSADATA wsaData;
    int iResult;
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0)
    {
        std::cout << "WSAStartup failed with error\n";
    }
}

void Socket::clean_up()
{
    WSACleanup();
}
