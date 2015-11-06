#ifndef MEMBERMODEL_H
#define MEMBERMODEL_H

#include <QObject>

class MemberModel : public QObject
{
    Q_OBJECT
public:
    explicit MemberModel(QObject *parent = 0);

signals:

public slots:
};

#endif // MEMBERMODEL_H
