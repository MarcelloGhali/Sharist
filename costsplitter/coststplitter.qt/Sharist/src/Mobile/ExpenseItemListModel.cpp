#include "ExpenseItemListModel.h"

ExpenseItemListModel::ExpenseItemListModel(QObject *parent):
    QAbstractListModel(parent){ }

int ExpenseItemListModel::rowCount(const QModelIndex &parent) const{
    //int size = this->expenses->size();
    return 1;
}

QVariant ExpenseItemListModel::data(const QModelIndex &index, int role) const{
    if (index.row()<0 || index.row()>=this->expenses->size()){
        return QVariant();
    }

    if (role==Qt::DisplayRole){
        const ExpenseItem* item = this->expenses->at(index.row());
        return QVariant(item->cost);
    }

    return QVariant();
}

void ExpenseItemListModel::AddExpenseItems(vector<const ExpenseItem *> *expenseVector){
    this->beginInsertRows(QModelIndex(),1,1);
    this->expenses = expenseVector;
    this->endInsertRows();
}
