#ifndef EXPENSEITEMMODEL_H
#define EXPENSEITEMMODEL_H

#include <QObject>
#include "ExpenseItem.h"

class ExpenseItemModel : public QObject
{
    Q_OBJECT
public:
    ExpenseItemModel(QObject *parent = 0);
    ExpenseItemModel(ExpenseItem* expense);
    Q_PROPERTY(QString cost READ cost NOTIFY costChanged)
    Q_PROPERTY(Member* owner READ owner NOTIFY ownerChanged)
    Q_PROPERTY(vector<const Member*>* paid READ paid NOTIFY paidChanged)
    QString cost() const;
    Member* owner();
    vector<const Member*>* paid();
private:
    ExpenseItem* rawExpenseItem;
signals:
    void costChanged();
    void ownerChanged();
    void paidChanged();
public slots:
};

#endif // EXPENSEITEMMODEL_H
