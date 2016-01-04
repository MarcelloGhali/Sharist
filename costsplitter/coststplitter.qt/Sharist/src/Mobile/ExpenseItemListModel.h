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
    ExpenseItemListModel(QObject *parent, vector<ExpenseItemPtr>* rawExpenses);
    ~ExpenseItemListModel();
    Q_PROPERTY(ExpenseItemModel* currentExpenseItem READ currentExpenseItem NOTIFY currentExpenseItemChanged)
    Q_INVOKABLE void createTempExpense();
    void Sync();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    ExpenseItemModel* currentExpenseItem();
private:
    QList<ExpenseItemModel*> expenseModels;
    vector<ExpenseItemPtr>* rawExpenseItems;
    //TODO: move to view model
    ExpenseItemModel* currentExpense;
signals:
    void currentExpenseItemChanged();
};

#endif // EXPENSEITEMLISTMODEL_H
