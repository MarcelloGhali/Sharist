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
    Member slava("Slava");
    Member marat("Marat");
    Member alex("Alex");
    Member ruslan("Ruslan");
    //Oregon set up
    SharedEvent oregon("Oregon");
    vector<const Member*> paid;
    paid.push_back(&slava);
    paid.push_back(&alex);
    ExpenseItem item(40, &marat, 0, &paid);
    oregon.AddMember(&slava);
    oregon.AddMember(&alex);
    oregon.AddMember(&marat);
    oregon.AddExpenseItem(&item);
    //Idaho set up
    SharedEvent idaho("Idaho");
    idaho.AddMember(&alex);
    idaho.AddMember(&marat);
    idaho.AddMember(&ruslan);
//    vector<const Member*> maratMembers;
//    maratMembers.push_back(&alex);
//    maratMembers.push_back(&ruslan);
//    vector<const Member*> ruslanMembers;
//    ruslanMembers.push_back(&alex);
//    ruslanMembers.push_back(&marat);
//    ExpenseItem item1(143.44,&marat,0,&maratMembers);
//    ExpenseItem item2(321,&ruslan,0,&ruslanMembers);
//    idaho.AddExpenseItem(&item1);
//    idaho.AddExpenseItem(&item2);
    //models
    SharedEventListModel model;
    SharedEventModel oregonEventModel(&oregon);
    SharedEventModel idahoEventModel(&idaho);
    model.addSharedEvent(&oregonEventModel);
    model.addSharedEvent(&idahoEventModel);
    idaho.Optimize();
    string s = idaho.Print();
    QQmlContext *cntx = view.rootContext();
    cntx->setContextProperty("eventsModel",&model);
    cntx->setContextProperty("navMap",&navMap);
    view.setSource(QUrl(QStringLiteral("qrc:/Base.qml")));
    view.show();
    return app.exec();
}

