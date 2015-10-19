#ifndef SHAREDEVENTMODEL_H
#define SHAREDEVENTMODEL_H

#include <QObject>
#include <SharedEvent.h>

class SharedEventModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
private:
    SharedEvent* rawSharedEvent;
public:
    SharedEventModel(QObject *parent = 0);
    SharedEventModel(SharedEvent* rawSharedEvent);
    QString name() const;
signals:
    void nameChanged();
};

#endif // SHAREDEVENTMODEL_H
