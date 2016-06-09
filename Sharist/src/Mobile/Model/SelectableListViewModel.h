#ifndef SELECTABLELISTVIEWMODEL_H
#define SELECTABLELISTVIEWMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <Model/MemberModel.h>

class SelectableListViewModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum MemberRoles{
        SelectedRole=Qt::UserRole+1,
        NameRole=Qt::UserRole+2
    };
    SelectableListViewModel(QObject *parent = 0);
    SelectableListViewModel(vector<MemberModelPtr> available, QObject* parent = 0);
    vector<MemberModelPtr> getSelected();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
protected:
    QHash<int,QByteArray> roleNames() const;
private:
    vector<MemberModelPtr> _availableVector;
    map<MemberModelPtr, bool> _selectedVector;
};

typedef shared_ptr<SelectableListViewModel> SelectableListViewModelPtr;

#endif // SELECTABLELISTVIEWMODEL_H
