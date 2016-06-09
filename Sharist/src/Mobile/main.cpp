#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include "GuiManager.h"
#include <QQmlContext>
#include <QQuickItem>
#include "ViewModel/SharedEventListView.h"
#include "ViewModel/SharedEventNewView.h"
#include "ViewModel/SharedEventDetailsView.h"
#include "ViewModel/ExpenseNewView.h"
#include "ViewModel/MemberNewView.h"
#include "Model/SelectableListViewModel.h"


void init(){
    qmlRegisterType<SharedEventListView>("Sharist.Models",1,0,"SharedEventListView");
    qmlRegisterType<SharedEventNewView>("Sharist.Models",1,0,"SharedEventNewView");
    qmlRegisterType<SharedEventDetailsView>("Sharist.Models",1,0,"SharedEventDetailsView");
    qmlRegisterType<ExpenseNewView>("Sharist.Models",1,0,"ExpenseNewView");
    qmlRegisterType<MemberNewView>("Sharist.Models",1,0,"MemberNewView");
    qmlRegisterType<SharedEventListModel>("Sharist.Models",1,0,"SharedEventListModel");
    qmlRegisterType<SharedEventModel>("Sharist.Models",1,0,"SharedEventModel");
    qmlRegisterType<MemberModel>("Sharist.Models",1,0,"MemberModel");
    qmlRegisterType<ExpenseItemModel>("Sharist.Models",1,0,"ExpenseItemModel");
    qmlRegisterType<ExpenseItemListModel>("Sharist.Models",1,0,"ExpenseItemListModel");
    qmlRegisterType<MemberListModel>("Sharist.Models",1,0,"MemberListModel");
    qmlRegisterType<SelectableListViewModel>("Sharist.Models",1,0,"SelectableListViewModel");
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

