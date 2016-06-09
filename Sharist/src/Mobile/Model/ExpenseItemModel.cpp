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

ExpenseItemModel::ExpenseItemModel(const double &total, MemberModelPtr owner, vector<MemberModelPtr> paid, QObject *parent):
    QObject(parent){
    vector<MemberPtr> paidVector;
    vector<MemberPtr> covered;
    for(vector<MemberModelPtr>::iterator it = paid.begin(); it<paid.end(); it++){
        MemberPtr modelPtr = it->get()->getRawMember();
        paidVector.push_back(modelPtr);
    }

    ExpenseItem* expenseItem = new ExpenseItem(total, owner->getRawMember(), covered, paidVector);
    ExpenseItemPtr ptr(expenseItem);
    this->rawExpenseItem = ptr;
}

MemberListModel* ExpenseItemModel::paid(){
    return paidPtr.get();
}

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
