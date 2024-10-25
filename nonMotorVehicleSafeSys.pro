QT += core
QT += gui widgets network serialport

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        gps.cpp \
        main.cpp \
        myhttpserver.cpp \
        myhttpserverworker.cpp \
        mymain.cpp \
        novacontroller.cpp \
        novacontrollerworker.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    NovaHeader.h \
    gps.h \
    myhttpserver.h \
    myhttpserverworker.h \
    mymain.h \
    novacontroller.h \
    novacontrollerworker.h

unix:!macx: LIBS += -L$$PWD/libs/ -lhv

INCLUDEPATH += $$PWD/include/libhv
DEPENDPATH += $$PWD/include/libhv

unix:!macx: LIBS += -L$$PWD/libs/ -lNovaTraffic

INCLUDEPATH += $$PWD/include/Nova
DEPENDPATH += $$PWD/include/Nova
