#include "NavigatorMap.h"

NavigatorMap::NavigatorMap(QObject *parent){
    map.insert("ListSharedEvent.Details","DetailsSharedEvent.qml");
    map.insert("ListSharedEvent.New","NewSharedEvent.qml");
}

QString NavigatorMap::GetTargetPage(QString pageName, QString targetFunction){
    QString target = pageName+'.'+targetFunction;
    if (map.contains(target)){
        return map[target];
    }

    return 0;
}
