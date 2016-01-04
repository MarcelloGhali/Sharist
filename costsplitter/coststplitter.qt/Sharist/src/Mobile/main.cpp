#include "SharedEventListModel.h"
#include "SharedEventModel.h"
#include "NavigatorMap.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>

void init(){
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
    QQuickView view;
    // core
    NavigatorMap navMap;
    MemberPtr slavaP(new Member("Slava"));
    MemberPtr maratP(new Member("Marat"));
    MemberPtr alexP(new Member("Alex"));
    MemberPtr ruslanP(new Member("Ruslan"));
    //Oregon set up
    SharedEvent oregon("Oregon");
    vector<MemberPtr> paid;
    paid.push_back(slavaP);
    paid.push_back(alexP);
    ExpenseItemPtr itemP(new ExpenseItem(40, maratP, vector<MemberPtr>(), paid));
    oregon.AddMember(slavaP);
    oregon.AddMember(alexP);
    oregon.AddMember(maratP);
    oregon.AddExpenseItem(itemP);
    //Idaho set up
    SharedEvent idaho("Idaho");
    idaho.AddMember(alexP);
    idaho.AddMember(maratP);
    idaho.AddMember(ruslanP);
    //models
    SharedEventListModel listModel;
    SharedEventModel oregonEventModel(&listModel, &oregon);
    SharedEventModel idahoEventModel(&listModel, &idaho);
    listModel.addSharedEvent(&oregonEventModel);
    listModel.addSharedEvent(&idahoEventModel);
    QQmlContext *cntx = view.rootContext();
    cntx->setContextProperty("eventsModel",&listModel);
    cntx->setContextProperty("navMap",&navMap);
    view.setSource(QUrl(QStringLiteral("qrc:/Base.qml")));
    view.show();
    return app.exec();
}

