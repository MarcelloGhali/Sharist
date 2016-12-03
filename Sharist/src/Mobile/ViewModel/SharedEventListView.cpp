#include "SharedEventListView.h"
#include "QQmlContext"
#include <QModelIndex>

SharedEventListView::SharedEventListView(QObject *parent):
    ViewModel(QUrl("qrc:/ListSharedEvent.qml"), parent){
    AppBaseFacade* instance = AppBaseFacade::GetInstance();
    _events = instance->GetSharedEventList();
}

SharedEventListView::~SharedEventListView(){

}

SharedEventListModel* SharedEventListView::getEventsList(){
    return _events.get();
}

void SharedEventListView::NavigateToDetails(const int &selected){
    SharedEventModelPtr modelPtr = _events.get()->getModel(selected);
    emit Navigate("DetailsEventView",modelPtr);
}

void SharedEventListView::NavigateToNew(){
    emit Navigate("NewEventView");
}
