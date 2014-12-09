#ifndef THREADBASE_H
#define THREADBASE_H

#include "IThread.h"

template <typename T>
class ThreadBase : public IThread
{
public:
    ThreadBase();
    ThreadBase(void* data);
    ~ThreadBase();

    void start();

protected:
    T _thread_proc;

    virtual void _create_thread(void* data) = 0;

protected:
    static int _thread_wrap_proc(void *data);
};

//---------------------------------------------

template <typename T>
ThreadBase<T>::ThreadBase() :
    _thread_proc(0)
{
}

template <typename T>
ThreadBase<T>::ThreadBase(void* data) :
    _thread_proc(data)
{
}

template <typename T>
ThreadBase<T>::~ThreadBase()
{
}

template <typename T>
void ThreadBase<T>::start()
{
    _create_thread((void*)this);
}

template <typename T>
int ThreadBase<T>::_thread_wrap_proc(void* data)
{
    ThreadBase* thread = static_cast<ThreadBase*>(data);
    thread->_thread_proc();
    return 0;
}

#endif // THREADBASE_H
