#ifndef EXPENSEITEMMODEL_H
#define EXPENSEITEMMODEL_H

#include <QObject>
#include <QVariant>
#include "ExpenseItem.h"
#include "MemberListModel.h"
#include "MemberModel.h"

class ExpenseItemModel : public QObject
{
    Q_OBJECT
public:
    ExpenseItemModel(QObject *parent = 0);
    ExpenseItemModel(ExpenseItem* expense);
    Q_PROPERTY(double cost READ cost WRITE setCost NOTIFY costChanged)
    Q_PROPERTY(MemberModel* owner READ owner WRITE setOwner NOTIFY ownerChanged)
    Q_PROPERTY(MemberListModel* paid READ paid WRITE setPaid NOTIFY paidChanged)
    double cost();
    MemberModel* owner();
    MemberListModel* paid();
    void setCost(double value);
    void setOwner(MemberModel* members);
    void setPaid(MemberListModel* members);
private:
    ExpenseItem* rawExpenseItem;
signals:
    void costChanged();
    void ownerChanged();
    void paidChanged();
public slots:
};

#endif // EXPENSEITEMMODEL_H
