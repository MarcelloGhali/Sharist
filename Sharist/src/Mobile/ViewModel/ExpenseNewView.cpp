#include "ExpenseNewView.h"
#include "Model/MemberListModel.h"

ExpenseNewView::ExpenseNewView(QObject *parent):
    ParameterizedViewModel(QUrl("qrc:/NewExpenseItem.qml"), parent){
}

void ExpenseNewView::Show(QObject *model){
    SharedEventModel* ptr = qobject_cast<SharedEventModel*>(model);
    _sharedEvent = ptr;
    MemberListModel *memberListModel= ptr->memberList();
    SelectableListViewModelPtr newPtr(new SelectableListViewModel(memberListModel->getMembers(),0));
    SelectableListViewModelPtr newPtr1(new SelectableListViewModel(memberListModel->getMembers(),0));
    _ownerModel = newPtr;
    _paidModel = newPtr1;
}

SelectableListViewModel* ExpenseNewView::getOwnerModel(){
   SelectableListViewModel* model = _ownerModel.get();
   return model;
}

SelectableListViewModel* ExpenseNewView::getPaidModel(){
   return _paidModel.get();
}

int ExpenseNewView::getTotal(){
   return _total;
}

void ExpenseNewView::setTotal(const int &val){
    _total = val;
}

void ExpenseNewView::Save(){
    MemberModelPtr owner = _ownerModel->getSelected()[0];
    vector<MemberModelPtr> paid = _paidModel->getSelected();
    ExpenseItemModelPtr ptr(new ExpenseItemModel(_total, owner, paid));
    _sharedEvent->AddExpenseItem(ptr);
    emit Navigate("DetailsEventView", _sharedEvent);
}
