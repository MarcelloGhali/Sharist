#ifndef EXPENSEITEMLISTMODEL_H
#define EXPENSEITEMLISTMODEL_H

#include <QAbstractListModel>
#include "ExpenseItemModel.h"
#include "ExpenseItem.h"

class ExpenseItemListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ExpenseItemListModel(QObject *parent = 0);
    Q_PROPERTY(ExpenseItemModel* currentExpenseItem READ currentExpenseItem NOTIFY currentExpenseItemChanged)
    Q_INVOKABLE void createTempExpense();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void AddExpenseItems(vector<const ExpenseItem*>* expenseVector);
    void addExpenseItem(ExpenseItem* expenseItem);
    ExpenseItemModel* currentExpenseItem();
private:
    vector<const ExpenseItem*>* expenses;
    ExpenseItemModel* currentExpense;
signals:
    void currentExpenseItemChanged();
};

#endif // EXPENSEITEMLISTMODEL_H
