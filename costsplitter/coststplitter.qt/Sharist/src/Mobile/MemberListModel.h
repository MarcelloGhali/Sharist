#ifndef MEMBERLISTMODEL_H
#define MEMBERLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include "Member.h"
#include "MemberModel.h"

class MemberListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MemberRoles{
        SelectedRole=Qt::UserRole+1,
        NameRole=Qt::UserRole+2
    };
    MemberListModel(QObject *parent = 0);
    Q_INVOKABLE void deselect(int i);
    Q_INVOKABLE MemberModel* getFirstSelected();
    QList<MemberModel*>* getSelected();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    void addMember(MemberModel* model);
    bool setData(const QModelIndex &index, const QVariant &value, int role);
protected:
    QHash<int,QByteArray> roleNames() const;
private:
    QList<MemberModel*> memberModels;
signals:

public slots:
};

#endif // MEMBERLISTMODEL_H
