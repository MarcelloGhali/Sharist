#include <string>
#include "ExpenseItemListModel.h"

ExpenseItemListModel::ExpenseItemListModel(QObject *parent):
    QAbstractListModel(parent){
}

ExpenseItemListModel::ExpenseItemListModel(QObject *parent, const SharedEventPtr &sharedEvt):
    QAbstractListModel(parent),
    rawSharedEvent(sharedEvt){
    this->Sync();
}

ExpenseItemListModel::~ExpenseItemListModel(){
}

void ExpenseItemListModel::Sync(){
    vector<ExpenseItemPtr> ptrs = this->rawSharedEvent->GetExpenseItems();
    for(vector<ExpenseItemPtr>::iterator it=ptrs.begin(); it!=ptrs.end(); it++){
        ExpenseItemPtr rawExpenseItem = *it;
        bool isFound = false;
        for(QList<ExpenseItemModelPtr>::iterator itM=this->expenseModels.begin(); itM!=this->expenseModels.end() && !isFound; itM++){
            ExpenseItemModelPtr expenseItemModel = *itM;
            if (rawExpenseItem==expenseItemModel->getRawExpenseItem()){
                isFound = true;
            }
        }

        if (!isFound){
            ExpenseItemModelPtr newModel(new ExpenseItemModel(this, rawExpenseItem));
            this->beginInsertRows(QModelIndex(),rowCount(),rowCount());
            this->expenseModels.append(newModel);
            this->endInsertRows();
        }
    }
}

void ExpenseItemListModel::createTempExpense(){
    ExpenseItemModelPtr newPtr(new ExpenseItemModel(this));
    this->currentExpensePtr = newPtr;
}

int ExpenseItemListModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return expenseModels.size();
}

QVariant ExpenseItemListModel::data(const QModelIndex &index, int role) const{
    if (index.row()<0 || index.row()>=this->expenseModels.size()){
        return QVariant(QString::null);
    }

    if (role==Qt::DisplayRole && this->expenseModels.size()>0){
        ExpenseItemModelPtr item = this->expenseModels.at(index.row());
        MemberModel* memberModel = item->owner();
        return memberModel->name();
    }

    return QVariant();
}

ExpenseItemModel* ExpenseItemListModel::currentExpenseItem(){
    return this->currentExpensePtr.get();
}
