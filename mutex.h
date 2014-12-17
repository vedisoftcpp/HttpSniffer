#ifndef MUTEX_H
#define MUTEX_H

#ifdef __unix__
    #include "posix/mutex.h"
#elif defined(_WIN32) || defined(WIN32)
    #include "win32/mutex.h"
#endif

#endif // MUTEX_H
