TEMPLATE = app

QT += qml quick

SOURCES += main.cpp \
    Model/SharedEventListModel.cpp \
    Model/SharedEventModel.cpp \
    Model/ExpenseItemListModel.cpp \
    Model/ExpenseItemModel.cpp \
    Model/MemberModel.cpp \
    Model/MemberListModel.cpp \
    AppBaseFacade.cpp \
    ViewModel/SharedEventListView.cpp \
    ViewModel/ViewModel.cpp \
    GuiManager.cpp \
    ViewModel/SharedEventDetailsView.cpp \
    ViewModel/ParameterizedViewModel.cpp \
    ViewModel/SharedEventNewView.cpp \
    ViewModel/MemberNewView.cpp \
    ViewModel/ExpenseNewView.cpp \
    Model/SelectableListViewModel.cpp

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
    Model/SharedEventListModel.h \
    Model/SharedEventModel.h \
    Model/ExpenseItemListModel.h \
    Model/MemberModel.h \
    Model/ExpenseItemModel.h \
    ISyncListModel.h \
    Model/MemberListModel.h \
    AppBaseFacade.h \
    ViewModel/SharedEventListView.h \
    ViewModel/ViewModel.h \
    GuiManager.h \
    ViewModel/SharedEventDetailsView.h \
    ViewModel/ParameterizedViewModel.h \
    ViewModel/SharedEventNewView.h \
    ViewModel/MemberNewView.h \
    ViewModel/ExpenseNewView.h \
    Model/SelectableListViewModel.h

CONFIG += c++11

mac {
    QMAKE_MAC_SDK = macosx10.12
}

ios {
    QMAKE_MAC_SDK = iphoneos9.2
    QMAKE_INFO_PLIST = Info.plist
}

DISTFILES += \
    Info.plist
