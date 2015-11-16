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
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(ExpenseItemListModel *expenseList READ expenseList NOTIFY expenseListChanged)
    Q_PROPERTY(MemberListModel *memberList READ memberList NOTIFY memberListChanged)
private:
    SharedEvent* rawSharedEvent;
    ExpenseItemListModel* expensesListModel;
    MemberListModel* memberListModel;
public:
    SharedEventModel(QObject *parent = 0);
    SharedEventModel(SharedEvent* rawSharedEvent);
    QString name() const;
    ExpenseItemListModel* expenseList();
    MemberListModel* memberList();
signals:
    void expenseListChanged();
    void nameChanged();
    void memberListChanged();
};

#endif // SHAREDEVENTMODEL_H
