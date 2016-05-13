#include "SharedEventModel.h"

SharedEventModel::SharedEventModel(QObject *parent)
    :QObject(parent){}

SharedEventModel::SharedEventModel(QObject* parent, SharedEvent* rawSharedEvent):
    QObject(parent),
    rawSharedEvent(rawSharedEvent),
    //TODO: make API consistent
    expensesListModel(this, &(rawSharedEvent->expenseItems)),
    memberListModel(this, rawSharedEvent->GetMembers()){
}

void SharedEventModel::AddExpenseItem(ExpenseItemModel *model){
    ExpenseItemPtr item = model->getRawExpenseItem();
    this->rawSharedEvent->AddExpenseItem(item);
    expensesListModel.Sync();
    expenseListChanged();
    resultChanged();
}

void SharedEventModel::AddMember(QString name){
    MemberPtr memberPtr(new Member(name.toStdString()));
    this->rawSharedEvent->AddMember(memberPtr);
    memberListModel.Sync();
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
    return &(this->expensesListModel);
}

MemberListModel* SharedEventModel::memberList(){
    return &(this->memberListModel);
}

