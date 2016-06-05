#ifndef MemberListModel_H
#define MemberListModel_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include "ExpenseItem.h"
#include "Member.h"
#include "MemberModel.h"
#include "ISyncListModel.h"

class MemberListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MemberRoles{
        SelectedRole=Qt::UserRole+1,
        NameRole=Qt::UserRole+2
    };
    MemberListModel(QObject *parent = 0);
    MemberListModel(QObject *parent, const vector<MemberPtr> &members);
    ~MemberListModel();
//    Q_INVOKABLE void deselect();
    // qml doesn't support shared_ptr, exposing raw pointers
    //Q_PROPERTY(MemberModel* firstSelected READ firstSelected NOTIFY firstSelectedChanged)
    //Q_INVOKABLE MemberModel* getMemberByIndex(const QModelIndex &index);
    void Sync(const vector<MemberPtr> &members);
//    QList<MemberModelPtr> getSelected();
//    MemberModel* firstSelected();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
//    bool setData(const QModelIndex &index, const QVariant &value, int role);
protected:
    QHash<int,QByteArray> roleNames() const;
private:
    QList<MemberModelPtr> memberModels;
    vector<MemberPtr> rawMembers;
signals:
    //void firstSelectedChanged();
public slots:
};

typedef shared_ptr<MemberListModel> MemberListModelPtr;
#endif // MEMBERLISTMODEL_H
