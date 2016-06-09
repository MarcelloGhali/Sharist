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
    void Sync(const vector<MemberPtr> &members);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    vector<MemberModelPtr> getMembers();
protected:
    QHash<int,QByteArray> roleNames() const;
private:
    QList<MemberModelPtr> memberModels;
    vector<MemberPtr> rawMembers;
public slots:
};

typedef shared_ptr<MemberListModel> MemberListModelPtr;
#endif // MEMBERLISTMODEL_H
