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
    ExpenseItemModel(QObject *parent, ExpenseItemPtr expense);
    ExpenseItemModel(const double &total, MemberModelPtr owner, vector<MemberModelPtr> paid, QObject *parent = 0);
    Q_PROPERTY(double cost READ cost WRITE setCost NOTIFY costChanged)
    // qml doesn't support shared_ptr, exposing raw pointers
    Q_PROPERTY(MemberModel* owner READ owner WRITE setOwner NOTIFY ownerChanged)
    Q_PROPERTY(MemberListModel* paid READ paid NOTIFY paidChanged)
    double cost();
    MemberModel* owner();
    MemberListModel* paid();
    void setCost(double value);
    void setOwner(MemberModel* members);
    ExpenseItemPtr getRawExpenseItem();
private:
    ExpenseItemPtr rawExpenseItem;
    MemberModelPtr ownerPtr;
    MemberListModelPtr paidPtr;
signals:
    void costChanged();
    void ownerChanged();
    void paidChanged();
public slots:
};

typedef shared_ptr<ExpenseItemModel> ExpenseItemModelPtr;

#endif // EXPENSEITEMMODEL_H
