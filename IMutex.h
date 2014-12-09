#ifndef IMUTEX_H
#define IMUTEX_H

class IMutex
{
public:
    virtual void acquire() = 0;
    virtual void release() = 0;
    virtual void create() = 0;
    virtual void close() = 0;
};

#endif // IMUTEX_H
