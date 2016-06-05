#include <QVariant>
#include "ExpenseItemModel.h"

ExpenseItemModel::ExpenseItemModel(QObject *parent) :
    QObject(parent){
    ExpenseItemPtr newItemP(new ExpenseItem);
    this->rawExpenseItem = newItemP;
}

ExpenseItemModel::ExpenseItemModel(QObject* parent, ExpenseItemPtr expense):
    QObject(parent),
    rawExpenseItem(expense),
    ownerPtr(new MemberModel(this, expense->owner)),
    paidPtr(new MemberListModel(this, expense->paid)){
}

MemberListModel* ExpenseItemModel::paid(){
    return paidPtr.get();
}

//void ExpenseItemModel::setPaid(MemberListModel* members){
//    //clear all there was before
//    this->rawExpenseItem->paid.clear();
//    QList<MemberModelPtr> models = members->getSelected();
//    for(QList<MemberModelPtr>::iterator it=models.begin(); it!=models.end(); it++){
//        MemberModelPtr model = *it;
//        if(model->selected()){
//            this->rawExpenseItem->paid.push_back(model->getRawMember());
//        }
//    }

//    paidPtr.reset(new MemberListModel(this, rawExpenseItem->paid));
//    paidChanged();
//}

MemberModel* ExpenseItemModel::owner(){
    return ownerPtr.get();
}

void ExpenseItemModel::setOwner(MemberModel* member){
    this->rawExpenseItem->owner = member->getRawMember();
    ownerPtr.reset(new MemberModel(this, rawExpenseItem->owner));
    ownerChanged();
}

double ExpenseItemModel::cost(){
    return this->rawExpenseItem->cost;
}

void ExpenseItemModel::setCost(double value){
    if (value!=this->rawExpenseItem->cost){
        this->rawExpenseItem->cost = value;
        costChanged();
    }
}

ExpenseItemPtr ExpenseItemModel::getRawExpenseItem(){
    return this->rawExpenseItem;
}
