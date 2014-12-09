#ifndef ITHREAD_H
#define ITHREAD_H

class IThread
{
public:
    virtual void start() = 0;

protected:
    virtual void close() = 0;
};

#endif // ITHREAD_H
