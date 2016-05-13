#-------------------------------------------------
#
# Project created by QtCreator 2015-08-13T23:21:51
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_core_testtest
CONFIG  +=c++11
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_core_testtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

INCLUDEPATH += $$PWD/../../src/core
DEPENDPATH += $$PWD/../../src/core

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../src/core/release/ -lcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../src/core/debug/ -lcore
else:unix: LIBS += -L$$OUT_PWD/../../src/core/ -lcore

INCLUDEPATH += $$PWD/../../src/core
DEPENDPATH += $$PWD/../../src/core

mac {
    QMAKE_MAC_SDK = macosx10.11
}

ios {
    QMAKE_MAC_SDK = iphoneos9.2
    QMAKE_INFO_PLIST = Info.plist
}

DISTFILES += \
    Info.plist
