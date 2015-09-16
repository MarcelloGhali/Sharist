#ifndef SHAREDEVENTMODEL_H
#define SHAREDEVENTMODEL_H

#include <QAbstractListModel>
#include "SharedEvent.h"

class SharedEventModel: public QAbstractListModel
{
    Q_OBJECT
public:
    enum SharedEventRoles{
        NameRole=Qt::UserRole+1
    };

    SharedEventModel(QObject *parent=0);
    void addSharedEvent(const SharedEvent &event);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
protected:
    QHash<int,QByteArray> roleNames() const;
private:
    QList<SharedEvent> sharedEvents;
};

#endif // SHAREDEVENTMODEL_H
