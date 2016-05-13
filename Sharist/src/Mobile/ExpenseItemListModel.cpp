#include <string>
#include "ExpenseItemListModel.h"

ExpenseItemListModel::ExpenseItemListModel(QObject *parent):
    QAbstractListModel(parent){
}

ExpenseItemListModel::ExpenseItemListModel(QObject *parent, vector<ExpenseItemPtr>* rawExpenses):
    QAbstractListModel(parent),
    rawExpenseItems(rawExpenses){
    this->Sync();
}

ExpenseItemListModel::~ExpenseItemListModel(){
}

void ExpenseItemListModel::Sync(){
    for(vector<ExpenseItemPtr>::iterator it=this->rawExpenseItems->begin(); it!=this->rawExpenseItems->end(); it++){
        ExpenseItemPtr rawExpenseItem = *it;
        bool isFound = false;
        for(QList<ExpenseItemModel*>::iterator itM=this->expenseModels.begin(); itM!=this->expenseModels.end() && !isFound; itM++){
            ExpenseItemModel* expenseItemModel = *itM;
            if (rawExpenseItem==expenseItemModel->getRawExpenseItem()){
                isFound = true;
            }
        }

        if (!isFound){
            ExpenseItemModel* newModel = new ExpenseItemModel(this, rawExpenseItem);
            this->beginInsertRows(QModelIndex(),rowCount(),rowCount());
            this->expenseModels.append(newModel);
            this->endInsertRows();
        }
    }
}

void ExpenseItemListModel::createTempExpense(){
    //TODO: memory management, move to viewmodel
    this->currentExpense = new ExpenseItemModel(this);
}

int ExpenseItemListModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return expenseModels.size();
}

QVariant ExpenseItemListModel::data(const QModelIndex &index, int role) const{
    if (index.row()<0 || index.row()>=this->rawExpenseItems->size()){
        return QVariant(QString::null);
    }

    if (role==Qt::DisplayRole && this->rawExpenseItems->size()>0){
        ExpenseItemPtr item = this->rawExpenseItems->at(index.row());
        MemberPtr memberPtr = item->owner;
        QString outStr = QString::fromStdString(memberPtr->Name) + ": " + QString::number(item->cost);
        return QVariant(outStr);
    }

    return QVariant();
}

ExpenseItemModel* ExpenseItemListModel::currentExpenseItem(){
    return this->currentExpense;
}
