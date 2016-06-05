#ifndef EXPENSEITEMLISTMODEL_H
#define EXPENSEITEMLISTMODEL_H

#include <QAbstractListModel>
#include "SharedEvent.h"
#include "ExpenseItemModel.h"
#include "ExpenseItem.h"
#include "ISyncListModel.h"

class ExpenseItemListModel : public QAbstractListModel, ISyncListModel
{
    Q_OBJECT
public:
    ExpenseItemListModel(QObject* parent = 0);
    ExpenseItemListModel(QObject* parent, const SharedEventPtr &sharedEvt);
    ~ExpenseItemListModel();
    // qml doesn't support shared_ptr, exposing raw pointers
    Q_PROPERTY(ExpenseItemModel* currentExpenseItem READ currentExpenseItem NOTIFY currentExpenseItemChanged)
    Q_INVOKABLE void createTempExpense();
    void Sync();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    ExpenseItemModel* currentExpenseItem();
private:
    SharedEventPtr rawSharedEvent;
    QList<ExpenseItemModelPtr> expenseModels;
    //TODO: move to view model
    ExpenseItemModelPtr currentExpensePtr;
signals:
    void currentExpenseItemChanged();
};

typedef shared_ptr<ExpenseItemListModel> ExpenseItemListModelPtr;
#endif // EXPENSEITEMLISTMODEL_H
