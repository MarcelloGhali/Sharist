#include "SharedEventModel.h"

SharedEventModel::SharedEventModel(QObject *parent)
    :QObject(parent){}

SharedEventModel::SharedEventModel(const QString &name, QObject *parent):
    QObject(parent),
    rawSharedEventPtr(new SharedEvent(name.toStdString())){
}

SharedEventModel::SharedEventModel(QObject* parent, const SharedEventPtr &rawSharedEvent):
    QObject(parent),
    rawSharedEventPtr(rawSharedEvent),
    expensesListModelPtr(ExpenseItemListModelPtr(new ExpenseItemListModel(this, rawSharedEvent))),
    memberListModelPtr(MemberListModelPtr(new MemberListModel(this, rawSharedEvent->GetMembers()))){
}

void SharedEventModel::AddExpenseItem(ExpenseItemModel* model){
    ExpenseItemPtr item = model->getRawExpenseItem();
    this->rawSharedEventPtr->AddExpenseItem(item);
    expensesListModelPtr->Sync();
    expenseListChanged();
    resultChanged();
}

void SharedEventModel::AddMember(QString name){
    MemberPtr memberPtr(new Member(name.toStdString()));
    this->rawSharedEventPtr->AddMember(memberPtr);
    memberListModelPtr->Sync(this->rawSharedEventPtr->GetMembers());
}

QString SharedEventModel::result(){
    this->rawSharedEventPtr->Optimize();
    QString results = QString::fromStdString(this->rawSharedEventPtr->Print());
    return results;
}

QString SharedEventModel::name() const{
    return QString::fromStdString(this->rawSharedEventPtr->GetEventName());
}

ExpenseItemListModel* SharedEventModel::expenseList(){
    return this->expensesListModelPtr.get();
}

MemberListModel* SharedEventModel::memberList(){
    return this->memberListModelPtr.get();
}

