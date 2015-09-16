#include "sharedeventmodel.h"

#include <QGuiApplication>
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    SharedEventModel model;
    model.addSharedEvent(SharedEvent("Oregon"));
    model.addSharedEvent(SharedEvent("Idaho"));
    QQuickView view;
    QQmlContext *cntx = view.rootContext();
    cntx->setContextProperty("eventsModel",&model);
    view.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
            view.show();
//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
