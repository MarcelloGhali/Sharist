#include "SharedEventDetailsView.h"

SharedEventDetailsView::SharedEventDetailsView(QObject *parent):
    ParameterizedViewModel(QUrl("qrc:/DetailsSharedEvent.qml"), parent){

}

SharedEventModel* SharedEventDetailsView::getEventModel(){
    return _eventModel.get();
}

void SharedEventDetailsView::Show(const shared_ptr<QObject> &model){
    _eventModel = dynamic_pointer_cast<SharedEventModel>(model);
}

void SharedEventDetailsView::AddMember(){
    emit Navigate("MemberNewView", _eventModel);
}

void SharedEventDetailsView::AddExpense(){
    emit Navigate("ExpenseNewView", _eventModel);
}
