#include "SelectableListViewModel.h"

SelectableListViewModel::SelectableListViewModel(QObject *parent):
    QAbstractListModel(parent){

}

SelectableListViewModel::SelectableListViewModel(vector<MemberModelPtr> available, QObject *parent):
    _availableVector(available),
    QAbstractListModel(parent){
    for(vector<MemberModelPtr>::iterator it = _availableVector.begin(); it<_availableVector.end(); it++){
        MemberModelPtr item = *it;
        _selectedVector.insert(std::pair<MemberModelPtr, bool>(item,false));
    }
}

int SelectableListViewModel::rowCount(const QModelIndex &parent) const{
    return _availableVector.size();
}

QVariant SelectableListViewModel::data(const QModelIndex &index, int role) const{
    if (index.row()<0 || index.row()>=this->_availableVector.size()){
        return QVariant(QString::null);
    }

    MemberModelPtr model = this->_availableVector.at(index.row());
    if (role==NameRole){
        return QVariant(model->name());
    }

    if (role==SelectedRole){
        return QVariant(_selectedVector.at(model));
    }

    return QVariant();
}

bool SelectableListViewModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if (index.row()<0 || index.row()>=this->_availableVector.size()){
        return false;
    }

    MemberModelPtr model = this->_availableVector.at(index.row());
    if (role==SelectedRole){
        _selectedVector[model] = value.toBool();
        emit dataChanged(index,index);
        return true;
    }

    return false;
}

vector<MemberModelPtr> SelectableListViewModel::getSelected(){
    vector<MemberModelPtr> toReturn;

    for(vector<MemberModelPtr>::iterator it = _availableVector.begin(); it<_availableVector.end(); it++){
        if (_selectedVector[*it]==true) toReturn.push_back(*it);
    }

    return toReturn;
}

QHash<int,QByteArray> SelectableListViewModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[SelectedRole] = "Selected";
    roles[NameRole] = "Name";
    return roles;
}
