#ifndef SHAREDEVENTLISTMODEL_H
#define SHAREDEVENTLISTMODEL_H

#include <QAbstractListModel>
#include "SharedEventModel.h"

class SharedEventListModel: public QAbstractListModel
{
    Q_OBJECT
public:
    enum SharedEventRoles{
        NameRole=Qt::UserRole+1
    };
    SharedEventListModel(QObject *parent=0);
    Q_PROPERTY(SharedEventModel* selectedSharedEvent READ selectedSharedEvent)
    Q_PROPERTY(int selectedIndex READ selectedIndex WRITE setSelectedIndex)
//    Q_INVOKABLE SharedEventModel* getSelected(const int index);
    void addSharedEvent(SharedEventModel *event);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int selectedIndex();
    void setSelectedIndex(int index);
    SharedEventModel* selectedSharedEvent();
protected:
    QHash<int,QByteArray> roleNames() const;
private:
    QList<SharedEventModel*> sharedEvents;
    int _selectedIndex;
};

#endif // SHAREDEVENTMODEL_H
