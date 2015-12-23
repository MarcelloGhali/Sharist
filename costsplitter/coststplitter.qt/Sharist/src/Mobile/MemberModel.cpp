#include "MemberModel.h"

MemberModel::MemberModel(QObject *parent) :
    QObject(parent){
    this->rawMember = NULL;
    this->_isSelected = false;
}

MemberModel::MemberModel(const Member *member){
    this->rawMember = member;
    this->_isSelected = false;
}

bool MemberModel::selected(){
    return this->_isSelected;
}

void MemberModel::setSelected(bool isSelected){
    this->_isSelected = isSelected;
}

QString MemberModel::name(){
    if (this->rawMember!=NULL)
        return QString::fromStdString(this->rawMember->Name);
    else
        return QString();
}

const Member* MemberModel::getRawMember(){
    return this->rawMember;
}
