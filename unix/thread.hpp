#ifndef THREAD_H
#define THREAD_H

#include "../threadbase.hpp"
#include "pthread.h"

#include <iostream>

template <typename T>
class Thread : public ThreadBase<T>
{
public:
    Thread();
    Thread(void* data);
    ~Thread();

protected:
    void _create_thread(void* data);
    void close();

private:
    static void* thread_routine(void* param);
    pthread_t _thread;

private:
    Thread(const Thread<T>&);
};

//---------------------------------------------

template <typename T>
Thread<T>::Thread() :
    ThreadBase<T>::ThreadBase()
{
}

template <typename T>
Thread<T>::Thread(void* data) :
    ThreadBase<T>::ThreadBase(data)
{
}

template <typename T>
Thread<T>::~Thread()
{
}

template <typename T>
void* Thread<T>::thread_routine(void* param)
{
    //std::cout << "create_thread\n" << std::endl;
    ThreadBase<T>::_thread_wrap_proc((void*)param);
    return 0;
}

template <typename T>
void Thread<T>::_create_thread(void* data)
{
    pthread_create(&_thread, NULL, thread_routine, data);
}

template <typename T>
void Thread<T>::close()
{

}

#endif // THREAD_H
