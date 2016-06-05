#ifndef MEMBERMODEL_H
#define MEMBERMODEL_H

#include <QObject>
#include "Member.h"

class MemberModel : public QObject
{
    Q_OBJECT
public:
    MemberModel(QObject *parent = 0);
    MemberModel(QObject *parent, MemberPtr member);
    ~MemberModel();
//    Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
//    bool selected();
//    void setSelected(bool isSelected);
    QString name();
    MemberPtr getRawMember();
private:
    //bool _isSelected;
    MemberPtr rawMember;
signals:
//    void selectedChanged();
    void nameChanged();
public slots:
};

typedef shared_ptr<MemberModel> MemberModelPtr;

Q_DECLARE_METATYPE(MemberModel*)
#endif // MEMBERMODEL_H
