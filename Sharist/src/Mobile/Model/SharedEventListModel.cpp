#include "SharedEventListModel.h"

SharedEventListModel::SharedEventListModel(QObject *parent)
    :QAbstractListModel(parent){

}

SharedEventListModel::SharedEventListModel(QObject *parent, const vector<SharedEventPtr> &data)
    :QAbstractListModel(parent){
    for(vector<SharedEventPtr>::const_iterator it = data.begin(); it<data.end(); it++){
        SharedEventModelPtr newModelPtr(new SharedEventModel(this, *it));
        sharedEvents.append(newModelPtr);
    }
}

void SharedEventListModel::addSharedEvent(const QString& eventName){
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    SharedEventPtr rawSharedEventPtr(new SharedEvent(eventName.toStdString()));
    SharedEventModelPtr newModelPtr(new SharedEventModel(this, rawSharedEventPtr));
    sharedEvents.append(newModelPtr);
    endInsertRows();
}

void SharedEventListModel::addSharedEvent(const SharedEventModelPtr newModel){
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    sharedEvents<<newModel;
    endInsertRows();
}

int SharedEventListModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return sharedEvents.count();
}

QVariant SharedEventListModel::data(const QModelIndex &index, int role) const{
    if (index.row()<0 || index.row()>=sharedEvents.count()){
        return QVariant();
    }

    SharedEventModelPtr model = sharedEvents[index.row()];
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
    SharedEventModelPtr m = this->sharedEvents[this->_selectedIndex];
    return m.get();
}

SharedEventModelPtr SharedEventListModel::getModel(const int &index){
    return sharedEvents[index];
}
