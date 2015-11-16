#include "SharedEventModel.h"

SharedEventModel::SharedEventModel(QObject *parent)
    :QObject(parent){}

SharedEventModel::SharedEventModel(SharedEvent* rawSharedEvent){
    this->rawSharedEvent = rawSharedEvent;
    //TODO: manage memory allocation
    // add expenses
    this->expensesListModel = new ExpenseItemListModel;
    this->expensesListModel->AddExpenseItems(&(rawSharedEvent->expenseItems));
    // TODO: add members
    vector<const Member*>* members = this->rawSharedEvent->GetMembers();
    this->memberListModel = new MemberListModel;
    if (members->size()>0){
        this->memberListModel->addMembers(members);
    }
}

QString SharedEventModel::name() const{
    return QString::fromStdString(this->rawSharedEvent->GetEventName());
}

ExpenseItemListModel* SharedEventModel::expenseList(){
    return this->expensesListModel;
}

MemberListModel* SharedEventModel::memberList(){
    return this->memberListModel;
}
