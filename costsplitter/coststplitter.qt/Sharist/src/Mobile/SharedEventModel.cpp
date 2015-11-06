#include "SharedEventModel.h"

SharedEventModel::SharedEventModel(QObject *parent)
    :QObject(parent){}

SharedEventModel::SharedEventModel(SharedEvent* rawSharedEvent){
    this->rawSharedEvent = rawSharedEvent;
    this->expensesListModel = new ExpenseItemListModel;
    this->expensesListModel->AddExpenseItems(&(rawSharedEvent->expenseItems));
}

QString SharedEventModel::name() const{
    return QString::fromStdString(this->rawSharedEvent->GetEventName());
}

ExpenseItemListModel* SharedEventModel::expenseList(){
    return this->expensesListModel;
}
