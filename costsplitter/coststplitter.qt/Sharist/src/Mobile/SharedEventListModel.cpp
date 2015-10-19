#include "SharedEventListModel.h"

SharedEventListModel::SharedEventListModel(QObject *parent)
    :QAbstractListModel(parent){
}

void SharedEventListModel::addSharedEvent(const QString& eventName){
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    //todo: create new object in factory, so that they all garbage collected
    SharedEvent *rawSharedEvent = new SharedEvent(eventName.toStdString());
    SharedEventModel *newModel = new SharedEventModel(rawSharedEvent);
    sharedEvents.append(newModel);
    endInsertRows();
}

void SharedEventListModel::addSharedEvent(SharedEventModel* newModel){
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    sharedEvents<<newModel;
    endInsertRows();
}

int SharedEventListModel::rowCount(const QModelIndex &parent) const{
    return sharedEvents.count();
}

QVariant SharedEventListModel::data(const QModelIndex &index, int role) const{
    if (index.row()<0 || index.row()>=sharedEvents.count()){
        return QVariant();
    }

    SharedEventModel* model = sharedEvents[index.row()];
    if (role==NameRole)
        return model->name();
    return QVariant();
}

QHash<int,QByteArray> SharedEventListModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    return roles;
}

void SharedEventListModel::setSelectedIndex(int index){
    this->_selectedIndex = index;
}

int SharedEventListModel::selectedIndex(){
    return this->_selectedIndex;
}

SharedEventModel* SharedEventListModel::selectedSharedEvent(){
    return this->sharedEvents[this->_selectedIndex];
}

