#ifndef MEMBERMODEL_H
#define MEMBERMODEL_H

#include <QObject>
#include "Member.h"

class MemberModel : public QObject
{
    Q_OBJECT
public:
    MemberModel(QObject *parent = 0);
    MemberModel(const Member* member);
    Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    bool selected();
    void setSelected(bool isSelected);
    QString name();
    const Member* getRawMember();
private:
    bool _isSelected;
    const Member* rawMember;
signals:
    void selectedChanged();
    void nameChanged();
public slots:
};

Q_DECLARE_METATYPE(MemberModel*)
#endif // MEMBERMODEL_H
