#ifndef THREAD_H
#define THREAD_H

#include "../threadbase.hpp"

#include <Windows.h>

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
    static DWORD WINAPI winapi_thread_toutine(LPVOID param);

private:
    Thread(const Thread<T>&);
};

//---------------------------------------------

template <typename T>
Thread<T>::Thread() :
    ThreadBase()
{
}

template <typename T>
Thread<T>::Thread(void* data) :
    ThreadBase(data)
{
}

template <typename T>
Thread<T>::~Thread()
{
}

template <typename T>
DWORD WINAPI Thread<T>::winapi_thread_toutine(LPVOID param)
{
    //std::cout << "create_thread\n" << std::endl;
    ThreadBase<T>::_thread_wrap_proc((void*)param);
    return 0;
}

template <typename T>
void Thread<T>::_create_thread(void* data)
{
    CreateThread(NULL, 0, winapi_thread_toutine, data, 0, NULL);
}

template <typename T>
void Thread<T>::close()
{

}

#endif // THREAD_H
