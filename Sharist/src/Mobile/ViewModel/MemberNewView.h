#ifndef MEMBERNEWVIEW_H
#define MEMBERNEWVIEW_H

#include <QObject>
#include "ParameterizedViewModel.h"

class MemberNewView : public ParameterizedViewModel
{
    Q_OBJECT
public:
    Q_INVOKABLE void Save();
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    MemberNewView(QObject *parent = 0);
    QString getName();
    void setName(const QString &name);
    void Show(const shared_ptr<QObject> &model);
private:
    SharedEventModelPtr _eventPtr;
    QString _name;
signals:
    void nameChanged();
};

#endif // MEMBERNEWVIEW_H
