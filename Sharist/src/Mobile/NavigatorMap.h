#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <QObject>
#include <QHash>

class NavigatorMap : public QObject
{
    Q_OBJECT
private:
    QHash<QString,QString> map;
public:
    explicit NavigatorMap(QObject *parent = 0);
    QString GetTargetPage(QString pageName, QString targetFunction);
signals:

public slots:
};

#endif // NAVIGATOR_H
