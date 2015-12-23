#include <QVariant>
#include "ExpenseItemModel.h"

ExpenseItemModel::ExpenseItemModel(QObject *parent) :
    QObject(parent){
    //TODO:: memory management
    this->rawExpenseItem = new ExpenseItem;
}

ExpenseItemModel::ExpenseItemModel(ExpenseItem *expense){
    this->rawExpenseItem = expense;
}

MemberListModel* ExpenseItemModel::paid(){
    MemberListModel* listModels = new MemberListModel;
    for(vector<const Member*>::iterator it = this->rawExpenseItem->paid->begin(); it!=this->rawExpenseItem->paid->end(); it++){
        MemberModel* model = new MemberModel(*it);
        listModels->addMember(model);
    }

    return listModels;
}

void ExpenseItemModel::setPaid(MemberListModel* members){
    //clear all there was before
    delete this->rawExpenseItem->paid;
    this->rawExpenseItem->paid = new vector<const Member*>;

    QList<MemberModel*>* models = members->getSelected();
    for(QList<MemberModel*>::iterator it=models->begin(); it!=models->end(); it++){
        MemberModel* model = *it;
        if(model->selected()){
            this->rawExpenseItem->paid->push_back(model->getRawMember());
        }
    }

    paidChanged();
}

MemberModel* ExpenseItemModel::owner(){
    MemberModel* model = new MemberModel(this->rawExpenseItem->owner);
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

ExpenseItem* ExpenseItemModel::getRawExpenseItem(){
    return this->rawExpenseItem;
}
