#include <QVariant>
#include "ExpenseItemModel.h"

ExpenseItemModel::ExpenseItemModel(QObject *parent) :
    QObject(parent){
    ExpenseItemPtr newItemP(new ExpenseItem);
    this->rawExpenseItem = newItemP;
}

ExpenseItemModel::ExpenseItemModel(QObject* parent, const ExpenseItemPtr &expense):
    QObject(parent),
    rawExpenseItem(expense){
}

MemberListModel* ExpenseItemModel::paid(){
    MemberListModel* listModels = new MemberListModel(this, &(this->rawExpenseItem->paid));
    return listModels;
}

void ExpenseItemModel::setPaid(MemberListModel* members){
    //clear all there was before
    this->rawExpenseItem->paid.clear();
    QList<MemberModel*>* models = members->getSelected();
    for(QList<MemberModel*>::iterator it=models->begin(); it!=models->end(); it++){
        MemberModel* model = *it;
        if(model->selected()){
            this->rawExpenseItem->paid.push_back(model->getRawMember());
        }
    }

    paidChanged();
}

MemberModel* ExpenseItemModel::owner(){
    MemberModel* model = new MemberModel(this, this->rawExpenseItem->owner);
    return model;
}

void ExpenseItemModel::setOwner(MemberModel* member){
    this->rawExpenseItem->owner = member->getRawMember();
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
