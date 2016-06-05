#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include "GuiManager.h"
#include <QQmlContext>
#include <QQuickItem>
#include "SharedEventListView.h"
#include "SharedEventNewView.h"

void init(){
    qmlRegisterType<SharedEventListView>("Sharist.Models",1,0,"SharedEventListView");
    qmlRegisterType<SharedEventNewView>("Sharist.Models",1,0,"SharedEventNewView");
    qmlRegisterType<SharedEventListModel>("Sharist.Models",1,0,"SharedEventListModel");
    qmlRegisterType<SharedEventModel>("Sharist.Models",1,0,"SharedEventModel");
    qmlRegisterType<MemberModel>("Sharist.Models",1,0,"MemberModel");
    qmlRegisterType<ExpenseItemModel>("Sharist.Models",1,0,"ExpenseItemModel");
    qmlRegisterType<ExpenseItemListModel>("Sharist.Models",1,0,"ExpenseItemListModel");
    qmlRegisterType<MemberListModel>("Sharist.Models",1,0,"MemberListModel");
}

int main(int argc, char *argv[])
{
    init();
    QGuiApplication app(argc, argv);
    //bootstraping
    GuiManager guiMngr;
    guiMngr.Start();
    return app.exec();
}

