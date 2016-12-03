#-------------------------------------------------
#
# Project created by QtCreator 2015-08-13T23:20:19
#
#-------------------------------------------------

QT       -= gui

TARGET = core
TEMPLATE = lib

DEFINES += CORE_LIBRARY

SOURCES += \
    ExpenseItem.cpp \
    Member.cpp \
    SharedEvent.cpp

HEADERS +=\
    ExpenseItem.h \
    Member.h \
    SharedEvent.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

mac {
    QMAKE_MAC_SDK = macosx10.12
}

ios {
    QMAKE_MAC_SDK = iphoneos9.2
}

CONFIG += c++11
