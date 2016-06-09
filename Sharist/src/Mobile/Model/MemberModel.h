#ifndef MEMBERMODEL_H
#define MEMBERMODEL_H

#include <QObject>
#include "Member.h"

class MemberModel : public QObject
{
    Q_OBJECT
public:
    MemberModel(QObject *parent = 0);
    MemberModel(const QString &name, QObject *parent = 0);
    MemberModel(QObject *parent, MemberPtr member);
    ~MemberModel();
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    QString name();
    MemberPtr getRawMember();
private:
    MemberPtr rawMember;
signals:
    void nameChanged();
public slots:
};

typedef shared_ptr<MemberModel> MemberModelPtr;

Q_DECLARE_METATYPE(MemberModel*)
#endif // MEMBERMODEL_H
