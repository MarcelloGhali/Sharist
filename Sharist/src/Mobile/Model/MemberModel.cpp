#include "MemberModel.h"

MemberModel::MemberModel(QObject *parent){
    Q_UNUSED(parent);
}

MemberModel::MemberModel(const QString &name, QObject *parent):
    rawMember(new Member(name.toStdString())){

}

MemberModel::MemberModel(QObject *parent, MemberPtr member):
    QObject(parent),
    rawMember(member){
//    _isSelected(false){
}

MemberModel::~MemberModel(){
}

//bool MemberModel::selected(){
//    return this->_isSelected;
//}

//void MemberModel::setSelected(bool isSelected){
//    this->_isSelected = isSelected;
//}

QString MemberModel::name(){
    if (this->rawMember!=NULL)
        return QString::fromStdString(this->rawMember->Name);
    else
        return QString();
}

MemberPtr MemberModel::getRawMember(){
    return this->rawMember;
}

