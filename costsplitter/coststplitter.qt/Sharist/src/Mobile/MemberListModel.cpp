#include <QVariant>
#include "MemberListModel.h"

MemberListModel::MemberListModel(QObject *parent) :
    QAbstractListModel(parent){
}

int MemberListModel::rowCount(const QModelIndex &parent) const{
    return this->memberModels.size();
}

void MemberListModel::deselect(){
    for(QList<MemberModel*>::Iterator it = this->memberModels.begin();it!=this->memberModels.end(); it++){
        MemberModel* member = *it;
        member->setSelected(false);
    }
}

QList<MemberModel*>* MemberListModel::getSelected(){
    //TODO:: memoryManagement
    QList<MemberModel*>* toReturn = new QList<MemberModel*>;
    for(QList<MemberModel*>::Iterator it = this->memberModels.begin();it!=this->memberModels.end(); it++){
        MemberModel* member = *it;
        if (member->selected()){
            toReturn->push_back(member);
        }
    }

    return toReturn;
}

QVariant MemberListModel::data(const QModelIndex &index, int role) const{
    if (index.row()<0 || index.row()>=this->memberModels.size()){
        return QVariant(QString::null);
    }

    MemberModel* memberModel = this->memberModels.at(index.row());
    if (role==NameRole){
        return QVariant(memberModel->name());
    }

    if (role==SelectedRole){
        return QVariant(memberModel->selected());
    }

    return QVariant();
}

void MemberListModel::addMember(MemberModel *model){
    this->beginInsertRows(QModelIndex(),1,1);
    this->memberModels.push_back(model);
    this->endInsertRows();
}

bool MemberListModel::setData(const QModelIndex &index, const QVariant &value, int role){
    MemberModel* model = this->memberModels.at(index.row());
    if (role==SelectedRole){
        model->setSelected(value.toBool());
        emit dataChanged(index,index);
        return true;
    }

    return false;
}

QHash<int,QByteArray> MemberListModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[SelectedRole] = "Selected";
    roles[NameRole] = "Name";
    return roles;
}
