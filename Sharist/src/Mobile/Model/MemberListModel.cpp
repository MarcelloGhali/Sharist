#include <QVariant>
#include "MemberListModel.h"

MemberListModel::MemberListModel(QObject *parent) :
    QAbstractListModel(parent){
}

MemberListModel::MemberListModel(QObject *parent, const vector<MemberPtr> &members):
    QAbstractListModel(parent),
    rawMembers(members){
    this->Sync(members);
}

MemberListModel::~MemberListModel(){
}

void MemberListModel::Sync(const vector<MemberPtr> &members){
    for(vector<MemberPtr>::const_iterator it=members.begin(); it!=members.end(); it++){
        MemberPtr rawMember = *it;
        bool isFound = false;
        for(QList<MemberModelPtr>::iterator itM=this->memberModels.begin(); itM!=this->memberModels.end() && !isFound; itM++){
            MemberModelPtr memberModel = *itM;
            if (rawMember==memberModel->getRawMember()){
                isFound = true;
            }
        }

        if (!isFound){
            MemberModelPtr newModelPtr(new MemberModel(this,*it));
            this->beginInsertRows(QModelIndex(),rowCount(),rowCount());
            this->memberModels.append(newModelPtr);
            this->endInsertRows();
        }
    }
}

int MemberListModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return this->memberModels.size();
}

QVariant MemberListModel::data(const QModelIndex &index, int role) const{
    if (index.row()<0 || index.row()>=this->memberModels.size()){
        return QVariant(QString::null);
    }

    MemberModelPtr memberModel = this->memberModels.at(index.row());
    if (role==NameRole){
        return QVariant(memberModel->name());
    }

    return QVariant();
}

QHash<int,QByteArray> MemberListModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "Name";
    return roles;
}

vector<MemberModelPtr> MemberListModel::getMembers(){
    return memberModels.toVector().toStdVector();
}
