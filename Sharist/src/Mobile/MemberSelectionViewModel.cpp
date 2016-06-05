#include "MemberSelectionViewModel.h"

//MemberSelectionViewModel::MemberSelectionViewModel():
//    QAbstractListModel(parent){

//}

//QVariant MemberSelectionViewModel::data(const QModelIndex &index, int role) const{
//    if (index.row()<0 || index.row()>=this->memberModels.size()){
//        return QVariant(QString::null);
//    }

//    MemberModelPtr memberModel = this->memberModels.at(index.row());
//    if (role==NameRole){
//        return QVariant(memberModel->name());
//    }

//    if (role==SelectedRole){
//        return QVariant(memberModel->selected());
//    }

//    return QVariant();
//}

//bool MemberSelectionViewModel::setData(const QModelIndex &index, const QVariant &value, int role){
//    MemberModelPtr model = this->memberModels.at(index.row());
//    if (role==SelectedRole){
//        model->setSelected(value.toBool());
//        emit dataChanged(index,index);
//        return true;
//    }

//    return false;
//}

//QHash<int,QByteArray> MemberSelectionViewModel::roleNames() const{
//    QHash<int, QByteArray> roles;
//    roles[SelectedRole] = "Selected";
//    roles[NameRole] = "Name";
//    return roles;
//}
