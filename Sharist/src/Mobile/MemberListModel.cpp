#include <QVariant>
#include "MemberListModel.h"

MemberListModel::MemberListModel(QObject *parent) :
    QAbstractListModel(parent){
}

MemberListModel::MemberListModel(QObject *parent, vector<MemberPtr>* members):
    QAbstractListModel(parent),
    rawMembers(members){
    this->Sync();
}

MemberListModel::~MemberListModel(){
}

void MemberListModel::Sync(){
    for(vector<MemberPtr>::iterator it=this->rawMembers->begin(); it!=this->rawMembers->end(); it++){
        MemberPtr rawMember = *it;
        bool isFound = false;
        for(QList<MemberModel*>::iterator itM=this->memberModels.begin(); itM!=this->memberModels.end() && !isFound; itM++){
            MemberModel* memberModel = *itM;
            if (rawMember==memberModel->getRawMember()){
                isFound = true;
            }
        }

        if (!isFound){
            //TODO:memory management
            MemberModel* newModel = new MemberModel(this,*it);
            this->beginInsertRows(QModelIndex(),rowCount(),rowCount());
            this->memberModels.append(newModel);
            this->endInsertRows();
        }
    }
}

int MemberListModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return this->memberModels.size();
}

void MemberListModel::deselect(){
    for(QList<MemberModel*>::Iterator it = this->memberModels.begin();it!=this->memberModels.end(); it++){
        MemberModel* member = *it;
        member->setSelected(false);
    }

    QModelIndex start = this->createIndex(0,0);
    QModelIndex end = this->createIndex(rowCount()-1,0);
    emit dataChanged(start, end);
}

MemberModel* MemberListModel::firstSelected(){
    //TODO:: memoryManagement
    MemberModel* toReturn;
    for(QList<MemberModel*>::Iterator it = this->memberModels.begin();it!=this->memberModels.end(); it++){
        MemberModel* member = *it;
        if (member->selected()){
            toReturn = member;
        }
    }

    return toReturn;
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
