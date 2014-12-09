#ifndef ISOCKET_H
#define ISOCKET_H

class ISocket
{
public:
    virtual void bind(int port) = 0;
    virtual void listen() = 0;
    //virtual void accept() = 0;
};

#endif // ISOCKET_H
