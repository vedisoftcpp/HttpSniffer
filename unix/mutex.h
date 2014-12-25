#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

class Mutex
{
public:
    Mutex();
    ~Mutex();

    void acquire();
    void release();
    void create();
    void close();

private:
    pthread_mutex_t _mutex;
};

#endif // MUTEX_H
