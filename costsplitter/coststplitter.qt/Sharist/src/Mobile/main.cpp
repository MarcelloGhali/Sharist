#include "SharedEventListModel.h"
#include "SharedEventModel.h"
#include "NavigatorMap.h"
#include <QGuiApplication>
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview>


void init(){
    qmlRegisterType<SharedEventModel>("Sharist.Models",1,0,"SharedEventModel");
}

int main(int argc, char *argv[])
{
    init();
    QGuiApplication app(argc, argv);
    SharedEventListModel model;
    NavigatorMap navMap;
    SharedEvent oregon("Oregon");
    SharedEvent idaho("Idaho");
    SharedEventModel oregonEventModel(&oregon);
    SharedEventModel idahoEventModel(&idaho);
    model.addSharedEvent(&oregonEventModel);
    model.addSharedEvent(&idahoEventModel);
    QQuickView view;
    QQmlContext *cntx = view.rootContext();
    cntx->setContextProperty("eventsModel",&model);
    cntx->setContextProperty("navMap",&navMap);
    view.setSource(QUrl(QStringLiteral("qrc:/Base.qml")));
    view.show();
//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

