#ifndef EXPENSEITEMLISTMODEL_H
#define EXPENSEITEMLISTMODEL_H

#include <QAbstractListModel>
#include "ExpenseItem.h"

class ExpenseItemListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ExpenseItemListModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void AddExpenseItems(vector<const ExpenseItem*>* expenseVector);
private:
    vector<const ExpenseItem*>* expenses;
};

#endif // EXPENSEITEMLISTMODEL_H
