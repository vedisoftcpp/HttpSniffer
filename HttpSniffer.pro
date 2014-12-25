TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

#win32 {
#INCLUDEPATH += $$PWD/../../Local/Include
#LIBS += -L$$PWD/../../Local/Lib/ -lwpcap
#}
#INCLUDEPATH += C:\Users\denism\Local\Include

SOURCES += main.cpp \
    httpsnifferserver.cpp \
    httpsnifferproc.cpp \
    clientbrokerproc.cpp \
    connectedclientproc.cpp \
    removethreadfunc.cpp \
    httpstatistics.cpp \
    utils.cpp \
    Logging/logger.cpp \
    Logging/filelogger.cpp \
    Logging/displaylogger.cpp \
    Logging/loggermanager.cpp \
    urllogger.cpp \
    unix/mutex.cpp \
    unix/socket.cpp

HEADERS += \
    Application.h \
    httpsnifferserver.h \
    headers.h \
    httpsnifferproc.h \
    clientbrokerproc.h \
    connectedclientproc.h \
    removethreadfunc.h \
    httpstatistics.h \
    connected_client_data_t.h \
    threadbase.hpp \
    utils.h \
    HttpStataEntry.h \
    Logging/logger.h \
    Logging/headers.h \
    Logging/filelogger.h \
    Logging/displaylogger.h \
    Logging/loggermanager.h \
    urllogger.h \
    unix/mutex.h \
    unix/socket.h \
    unix/thread.hpp


#LIBS += -lpcap

#LIBS += -L$$PWD/../build-HttpSniffer5-Desktop-Debug/ -lHttpSniffer5

#INCLUDEPATH += $$PWD/../build-HttpSniffer5-Desktop-Debug
#DEPENDPATH += $$PWD/../build-HttpSniffer5-Desktop-Debug

#unix:!macx: PRE_TARGETDEPS += $$PWD/../build-HttpSniffer5-Desktop-Debug/libHttpSniffer5.a

unix:!macx: LIBS += -L$$PWD/../build-HttpSniffer5-Desktop-Debug/ -lHttpSniffer5

INCLUDEPATH += $$PWD/../build-HttpSniffer5-Desktop-Debug
DEPENDPATH += $$PWD/../build-HttpSniffer5-Desktop-Debug

unix:!macx: PRE_TARGETDEPS += $$PWD/../build-HttpSniffer5-Desktop-Debug/libHttpSniffer5.a

LIBS += -lpcap

