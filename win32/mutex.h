#ifndef MUTEX_H
#define MUTEX_H

#include "../IMutex.h"
#include "../headers.h"

class Mutex : public IMutex
{
public:
    Mutex();

    void acquire();
    void release();
    void create();
    void close();

private:
    HANDLE _mutex;
};

#endif // MUTEX_H
