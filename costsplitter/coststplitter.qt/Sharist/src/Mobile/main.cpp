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
    SharedEventListModel model;
    NavigatorMap navMap;
    SharedEvent oregon("Oregon");
    SharedEvent idaho("Idaho");
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

