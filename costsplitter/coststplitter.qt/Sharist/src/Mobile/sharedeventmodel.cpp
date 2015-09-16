#include "sharedeventmodel.h"

SharedEventModel::SharedEventModel(QObject *parent)
    :QAbstractListModel(parent){
}

void SharedEventModel::addSharedEvent(const SharedEvent &event){
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    sharedEvents<<event;
    endInsertRows();
}

int SharedEventModel::rowCount(const QModelIndex &parent) const{
    return sharedEvents.count();
}

QVariant SharedEventModel::data(const QModelIndex &index, int role) const{
    if (index.row()<0 || index.row()>=sharedEvents.count()){
        return QVariant();
    }

    const SharedEvent &e = sharedEvents[index.row()];
    if (role==NameRole)
        return QString::fromStdString(e.GetEventName());

    return QVariant();
}

QHash<int,QByteArray> SharedEventModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}
