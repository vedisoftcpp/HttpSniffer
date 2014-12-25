#include "mutex.h"
#include <iostream>

Mutex::Mutex()
{
}

Mutex::~Mutex()
{
    close();
}

void Mutex::acquire()
{
    pthread_mutex_lock(&_mutex);
}

void Mutex::release()
{
    pthread_mutex_unlock(&_mutex);
}

void Mutex::create()
{
    pthread_mutex_init(&_mutex, NULL);
}

void Mutex::close()
{
    pthread_mutex_destroy(&_mutex);
}
