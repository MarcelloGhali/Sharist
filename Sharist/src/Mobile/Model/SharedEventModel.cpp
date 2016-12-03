#include "SharedEventModel.h"

SharedEventModel::SharedEventModel(QObject *parent)
    :QObject(parent){}
//TODO: convert to overloaded constructors
SharedEventModel::SharedEventModel(const QString &name, QObject *parent):
    QObject(parent),
    rawSharedEventPtr(new SharedEvent(name.toStdString())){
    expensesListModelPtr = ExpenseItemListModelPtr(new ExpenseItemListModel(this, rawSharedEventPtr));
    memberListModelPtr = MemberListModelPtr(new MemberListModel(this, rawSharedEventPtr->GetMembers()));
}

SharedEventModel::SharedEventModel(QObject* parent, const SharedEventPtr &rawSharedEvent):
    QObject(parent),
    rawSharedEventPtr(rawSharedEvent),
    expensesListModelPtr(ExpenseItemListModelPtr(new ExpenseItemListModel(this, rawSharedEvent))),
    memberListModelPtr(MemberListModelPtr(new MemberListModel(this, rawSharedEvent->GetMembers()))){
}

void SharedEventModel::AddExpenseItem(const ExpenseItemModelPtr &expense){
   rawSharedEventPtr.get()->AddExpenseItem(expense.get()->getRawExpenseItem());
   expensesListModelPtr.get()->Sync();
   emit expenseListChanged();
   emit resultChanged();
}

void SharedEventModel::AddMember(QString name){
    MemberPtr memberPtr(new Member(name.toStdString()));
    this->rawSharedEventPtr->AddMember(memberPtr);
    memberListModelPtr->Sync(this->rawSharedEventPtr->GetMembers());
    emit memberListChanged();
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

