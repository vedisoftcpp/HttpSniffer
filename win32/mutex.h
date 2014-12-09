#ifndef MUTEX_H
#define MUTEX_H

#include "../IMutex.h"

class Mutex : public IMutex
{
public:
    Mutex();

    void acquire();
    void release();
};

#endif // MUTEX_H
