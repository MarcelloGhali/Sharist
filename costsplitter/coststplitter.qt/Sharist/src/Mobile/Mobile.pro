TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    NavigatorMap.cpp \
    SharedEventListModel.cpp \
    SharedEventModel.cpp \
    ExpenseItemListModel.cpp \
    MemberModel.cpp \
    ExpenseItemModel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../core/release/ -lcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../core/debug/ -lcore
else:unix: LIBS += -L$$OUT_PWD/../core/ -lcore

INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core

HEADERS += \
    NavigatorMap.h \
    SharedEventListModel.h \
    SharedEventModel.h \
    ExpenseItemListModel.h \
    MemberModel.h \
    ExpenseItemModel.h

QMAKE_MAC_SDK = macosx10.11
