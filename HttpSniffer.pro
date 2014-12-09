TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp \
    httpsnifferserver.cpp \
    win32/mutex.cpp \
    httpsnifferproc.cpp \
    clientbrokerproc.cpp \
    win32/socket.cpp \
    connectedclientproc.cpp \
    removethreadfunc.cpp \
    httpstatistics.cpp \
    utils.cpp

HEADERS += \
    IMutex.h \
    IThread.h \
    Application.h \
    httpsnifferserver.h \
    headers.h \
    win32/mutex.h \
    httpsnifferproc.h \
    clientbrokerproc.h \
    ISocket.h \
    win32/socket.h \
    connectedclientproc.h \
    removethreadfunc.h \
    httpstatistics.h \
    connected_client_data_t.h \
    threadbase.hpp \
    win32/thread.hpp \
    utils.h \
    HttpStataEntry.h


