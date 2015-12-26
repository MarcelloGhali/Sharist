#ifndef SHAREDEVENTMODEL_H
#define SHAREDEVENTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "ExpenseItemListModel.h"
#include "MemberListModel.h"
#include "SharedEvent.h"

class SharedEventModel : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString result READ result NOTIFY resultChanged)
    Q_PROPERTY(ExpenseItemListModel *expenseList READ expenseList NOTIFY expenseListChanged)
    Q_PROPERTY(MemberListModel *memberList READ memberList NOTIFY memberListChanged)
    Q_INVOKABLE void addExpenseItem(ExpenseItemModel* model);
    Q_INVOKABLE void addMember(QString name);
    SharedEventModel(QObject *parent = 0);
    SharedEventModel(SharedEvent* rawSharedEvent);
    QString name() const;
    QString result();
    ExpenseItemListModel* expenseList();
    MemberListModel* memberList();
private:
    SharedEvent* rawSharedEvent;
    ExpenseItemListModel* expensesListModel;
    MemberListModel* memberListModel;
signals:
    void expenseListChanged();
    void nameChanged();
    void memberListChanged();
    void resultChanged();
};

#endif // SHAREDEVENTMODEL_H
