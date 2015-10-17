#include "SharedEventModel.h"

SharedEventModel::SharedEventModel(QObject *parent)
    :QObject(parent){}

SharedEventModel::SharedEventModel(SharedEvent* rawSharedEvent){
    this->rawSharedEvent = rawSharedEvent;
}

void SharedEventModel::setName(const QString &name){
    string tmpName = name.toStdString();
    this->rawSharedEvent->SetEventName(tmpName);
}

QString SharedEventModel::name() const{
    return QString::fromStdString(this->rawSharedEvent->GetEventName());
}
