#ifndef SHAREDEVENTMODEL_H
#define SHAREDEVENTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "ExpenseItemListModel.h"
#include "SharedEvent.h"

class SharedEventModel : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString result READ result NOTIFY resultChanged)
    // qml doesn't support shared_ptr, exposing raw pointers
    Q_PROPERTY(ExpenseItemListModel* expenseList READ expenseList NOTIFY expenseListChanged)
    Q_PROPERTY(MemberListModel* memberList READ memberList NOTIFY memberListChanged)
    Q_INVOKABLE void AddExpenseItem(ExpenseItemModel* model);
    Q_INVOKABLE void AddMember(QString name);
    SharedEventModel(QObject* parent = 0);
    SharedEventModel(const QString &name, QObject* parent = 0);
    SharedEventModel(QObject* parent, const SharedEventPtr &rawSharedEvent);
    QString name() const;
    QString result();
    ExpenseItemListModel* expenseList();
    MemberListModel* memberList();
private:
    SharedEventPtr rawSharedEventPtr;
    ExpenseItemListModelPtr expensesListModelPtr;
    MemberListModelPtr memberListModelPtr;
signals:
    void expenseListChanged();
    void nameChanged();
    void memberListChanged();
    void resultChanged();
};

typedef shared_ptr<SharedEventModel> SharedEventModelPtr;
#endif // SHAREDEVENTMODEL_H
