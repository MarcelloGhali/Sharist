#ifndef EXPENSENEWVIEW_H
#define EXPENSENEWVIEW_H

#include "ParameterizedViewModel.h"
#include "Model/SelectableListViewModel.h"

class ExpenseNewView : public ParameterizedViewModel
{
    Q_OBJECT
public:
    Q_INVOKABLE void Save();
    Q_PROPERTY(SelectableListViewModel* ownerModel READ getOwnerModel NOTIFY ownerModelChanged)
    Q_PROPERTY(SelectableListViewModel* paidModel READ getPaidModel NOTIFY paidModelChanged)
    Q_PROPERTY(int total READ getTotal WRITE setTotal NOTIFY newTotalChanged)
    int getTotal();
    ExpenseNewView(QObject* parent = 0);
    void Show(const shared_ptr<QObject> &model);
    SelectableListViewModel* getOwnerModel();
    SelectableListViewModel* getPaidModel();
    void setTotal(const int &val);
signals:
    void newTotalChanged();
    void ownerModelChanged();
    void paidModelChanged();
private:
    int _total;
    SharedEventModelPtr _sharedEvent;
    SelectableListViewModelPtr _ownerModel;
    SelectableListViewModelPtr _paidModel;
};

#endif // EXPENSENEWVIEW_H
