QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        server.cpp \
        main.cpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    server.h \
    wrapper.h \
    inputmonitor.h \

OBJECTIVE_SOURCES += inputmonitor.mm \
                     wrapper.mm

QMAKE_LFLAGS += -F /System/Library/Frameworks/Security.framework/
LIBS += -framework AppKit
LIBS += -framework Security

QT += widgets network

