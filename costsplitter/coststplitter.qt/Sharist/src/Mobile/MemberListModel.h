#ifndef MEMBERLISTMODEL_H
#define MEMBERLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include "Member.h"

class MemberListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MemberListModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void addMembers(vector<const Member*>* membersVector);
private:
    vector<const Member*>* members;
signals:

public slots:
};

#endif // MEMBERLISTMODEL_H
