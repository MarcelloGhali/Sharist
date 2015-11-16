#include <string>
#include "ExpenseItemListModel.h"

ExpenseItemListModel::ExpenseItemListModel(QObject *parent):
    QAbstractListModel(parent){
    this->expenses = NULL;
}

int ExpenseItemListModel::rowCount(const QModelIndex &parent) const{
    if (this->expenses==NULL){
        return 0;
    }

    return this->expenses->size();
}

QVariant ExpenseItemListModel::data(const QModelIndex &index, int role) const{
    if (index.row()<0 || index.row()>=this->expenses->size()){
        return QVariant(QString::null);
    }

    if (role==Qt::DisplayRole && this->expenses->size()>0){
        const ExpenseItem* item = this->expenses->at(index.row());
        const Member* member = item->owner;
        QString outStr = QString::fromStdString(member->Name) + ": " + QString::number(item->cost);
        return QVariant(outStr);
    }

    return QVariant();
}

void ExpenseItemListModel::AddExpenseItems(vector<const ExpenseItem *> *expenseVector){
    this->beginInsertRows(QModelIndex(),1,1);
    this->expenses = expenseVector;
    this->endInsertRows();
}
