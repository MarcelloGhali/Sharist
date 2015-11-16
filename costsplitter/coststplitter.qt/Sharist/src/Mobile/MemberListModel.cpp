#include <cstddef>
#include "MemberListModel.h"

MemberListModel::MemberListModel(QObject *parent) :
    QAbstractListModel(parent){
    this->members=NULL;
}

int MemberListModel::rowCount(const QModelIndex &parent) const{
    if (this->members==NULL){
        return 0;
    }

    return this->members->size();
}

QVariant MemberListModel::data(const QModelIndex &index, int role) const{
    if (index.row()<0 || index.row()>=this->members->size()){
        return QVariant(QString::null);
    }

    if (role==Qt::DisplayRole && this->members->size()>0){
        const Member* member = this->members->at(index.row());
        return QVariant(QString::fromStdString(member->Name));
    }

    return QVariant();
}

void MemberListModel::addMembers(vector<const Member *> *membersVector){
    this->beginInsertRows(QModelIndex(),1,1);
    this->members = membersVector;
    this->endInsertRows();
}
