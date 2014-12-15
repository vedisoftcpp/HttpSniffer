TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += no_lflags_merge

win32 {
INCLUDEPATH += $$PWD/../../Local/Include
LIBS += -L$$PWD/../../Local/Lib/ -lwpcap
}
INCLUDEPATH += C:\Users\denism\Local\Include

SOURCES += main.cpp \
    httpsnifferserver.cpp \
    win32/mutex.cpp \
    httpsnifferproc.cpp \
    clientbrokerproc.cpp \
    win32/socket.cpp \
    connectedclientproc.cpp \
    removethreadfunc.cpp \
    httpstatistics.cpp \
    utils.cpp \
    ippackethandler.cpp \
    ippacket.cpp

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
    HttpStataEntry.h \
    ippackethandler.h \
    ippacket.h


