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
    SharedEvent.cpp \
    stdafx.cpp

HEADERS +=\
    ExpenseItem.h \
    Member.h \
    SharedEvent.h \
    stdafx.h \
    targetver.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
