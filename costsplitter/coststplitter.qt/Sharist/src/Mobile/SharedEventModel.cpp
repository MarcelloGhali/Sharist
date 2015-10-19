#include "SharedEventModel.h"

SharedEventModel::SharedEventModel(QObject *parent)
    :QObject(parent){}

SharedEventModel::SharedEventModel(SharedEvent* rawSharedEvent){
    this->rawSharedEvent = rawSharedEvent;
}

QString SharedEventModel::name() const{
    return QString::fromStdString(this->rawSharedEvent->GetEventName());
}
