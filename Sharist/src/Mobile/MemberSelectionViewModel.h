#ifndef MEMBERSELECTIONVIEWMODEL_H
#define MEMBERSELECTIONVIEWMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <MemberModel.h>

class MemberSelectionViewModel : QAbstractListModel
{
//public:
//    enum MemberRoles{
//        SelectedRole=Qt::UserRole+1,
//        NameRole=Qt::UserRole+2
//    };
//    MemberSelectionViewModel(QObject* parent = 0);
//    void Sync(const vector<MemberPtr> &members);
//    MemberModel* getSelected();
//    void ClearSelection();
//    int rowCount(const QModelIndex &parent = QModelIndex()) const;
//    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
//    bool setData(const QModelIndex &index, const QVariant &value, int role);
//protected:
//    QHash<int,QByteArray> roleNames() const;
//private:
//    vector<MemberPtr> members;
//    QHash<MemberPtr, bool> selectedTable;
};

#endif // MEMBERSELECTIONVIEWMODEL_H
