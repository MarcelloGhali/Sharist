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
    SharedEventListModel(QObject *parent, const vector<SharedEventPtr> &events);
    SharedEventModelPtr getModel(const int &index);
    // qml doesn't support shared_ptr, exposing raw pointers
    Q_PROPERTY(SharedEventModel* selectedSharedEvent READ selectedSharedEvent NOTIFY selectedSharedEventChanged)
    Q_PROPERTY(int selectedIndex READ selectedIndex WRITE setSelectedIndex NOTIFY selectedIndexChanged)
    Q_INVOKABLE void addSharedEvent(const QString& sharedEvent);
    void addSharedEvent(const SharedEventModelPtr model);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    SharedEventModel* selectedSharedEvent();
    void setSelectedIndex(int index);
    int selectedIndex();
signals:
    void selectedSharedEventChanged();
    void selectedIndexChanged();
protected:
    QHash<int,QByteArray> roleNames() const;
private:
    QList<SharedEventModelPtr> sharedEvents;
    int _selectedIndex;
};

typedef shared_ptr<SharedEventListModel> SharedEventListModelPtr;

#endif // SHAREDEVENTMODEL_H
