#include "SharedEventModel.h"

SharedEventModel::SharedEventModel(QObject *parent)
    :QObject(parent){}

SharedEventModel::SharedEventModel(SharedEvent* rawSharedEvent){
    this->rawSharedEvent = rawSharedEvent;
    //TODO: manage memory allocation
    this->expensesListModel = new ExpenseItemListModel;
    this->expensesListModel->AddExpenseItems(&(rawSharedEvent->expenseItems));
    // TODO: manage memory properly
    vector<const Member*>* members = this->rawSharedEvent->GetMembers();
    this->memberListModel = new MemberListModel;
    if (members->size()>0){
        for(vector<const Member*>::iterator it=members->begin(); it!=members->end(); it++){
            this->memberListModel->addMember(new MemberModel(*it));
        }
    }
}

void SharedEventModel::addExpenseItem(ExpenseItemModel *model){
    ExpenseItem* item = model->getRawExpenseItem();
    this->rawSharedEvent->AddExpenseItem(item);
    resultChanged();
    expenseListChanged();
}

QString SharedEventModel::result(){
    this->rawSharedEvent->Optimize();
    QString results = QString::fromStdString(this->rawSharedEvent->Print());
    return results;
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
