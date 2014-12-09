#include "mutex.h"
#include <iostream>

Mutex::Mutex()
{
}

void Mutex::acquire()
{
    WaitForSingleObject(_mutex, INFINITE);
}

void Mutex::release()
{
    ReleaseMutex(_mutex);
}

void Mutex::create()
{
    _mutex =  CreateMutex(NULL, FALSE, NULL);

    if (_mutex == NULL)
    {
        std::cout << "CreateMutex error" << std::endl;
    }
}

void Mutex::close()
{
    CloseHandle(_mutex);
}
