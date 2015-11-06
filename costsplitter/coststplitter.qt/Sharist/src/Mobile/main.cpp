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
}

int main(int argc, char *argv[])
{
    init();
    QGuiApplication app(argc, argv);
    QQuickView view;
    // core
    NavigatorMap navMap;
    SharedEvent oregon("Oregon");
    SharedEvent idaho("Idaho");
    Member slava("Slava");
    Member marat("Marat");
    Member alex("Alex");
    vector<const Member*> paid;
    paid.push_back(&slava);
    paid.push_back(&alex);
    ExpenseItem item(40, &marat, 0, &paid);
    oregon.AddExpenseItem(&item);
    //models
    SharedEventListModel model;
    SharedEventModel oregonEventModel(&oregon);
    SharedEventModel idahoEventModel(&idaho);
    model.addSharedEvent(&oregonEventModel);
    model.addSharedEvent(&idahoEventModel);
    QQmlContext *cntx = view.rootContext();
    cntx->setContextProperty("eventsModel",&model);
    cntx->setContextProperty("navMap",&navMap);
    view.setSource(QUrl(QStringLiteral("qrc:/Base.qml")));
    view.show();
    return app.exec();
}

