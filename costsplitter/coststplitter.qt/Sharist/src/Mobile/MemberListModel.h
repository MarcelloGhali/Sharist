#ifndef MEMBERLISTMODEL_H
#define MEMBERLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include "Member.h"
#include "MemberModel.h"
#include "ISyncListModel.h"

class MemberListModel : public QAbstractListModel, ISyncListModel
{
    Q_OBJECT
public:
    enum MemberRoles{
        SelectedRole=Qt::UserRole+1,
        NameRole=Qt::UserRole+2
    };
    MemberListModel(QObject *parent = 0);
    MemberListModel(QObject *parent, vector<MemberPtr>* members);
    ~MemberListModel();
    Q_INVOKABLE void deselect();
    Q_PROPERTY(MemberModel* firstSelected READ firstSelected NOTIFY firstSelectedChanged)
    void Sync();
    QList<MemberModel*>* getSelected();
    MemberModel* firstSelected();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
protected:
    QHash<int,QByteArray> roleNames() const;
private:
    QList<MemberModel*> memberModels;
    vector<MemberPtr>* rawMembers;
signals:
    void firstSelectedChanged();
public slots:
};

#endif // MEMBERLISTMODEL_H
