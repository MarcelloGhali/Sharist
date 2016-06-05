#ifndef SHAREDEVENTNEWVIEW_H
#define SHAREDEVENTNEWVIEW_H

#include "ViewModel.h"

class SharedEventNewView : public ViewModel
{
    Q_OBJECT
public:
    Q_INVOKABLE void Save();
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    SharedEventNewView(QObject* parent = 0);
    QString getName();
    void setName(const QString &name);
private:
    QString _name;
signals:
    void nameChanged();
};

#endif // SHAREDEVENTNEWVIEW_H
