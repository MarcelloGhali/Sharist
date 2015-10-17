#include "SharedEventListModel.h"

SharedEventListModel::SharedEventListModel(QObject *parent)
    :QAbstractListModel(parent){
}

void SharedEventListModel::addSharedEvent(SharedEventModel *event){
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    sharedEvents<<event;
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

//SharedEventModel* SharedEventListModel::getSelected(const int index){
//    if (index<0 || index>=sharedEvents.count()){
//        return 0;
//    }

//    return sharedEvents[index];
//}
