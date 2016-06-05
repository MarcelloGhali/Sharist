#include "SharedEventNewView.h"

SharedEventNewView::SharedEventNewView(QObject* parent):
    ViewModel(QUrl("qrc:/NewSharedEvent.qml"), parent){

}

void SharedEventNewView::setName(const QString &name){
    _name = name;
}

QString SharedEventNewView::getName(){
    return _name;
}

void SharedEventNewView::Save(){
    SharedEventModelPtr ptr(new SharedEventModel(_name));
    AppBaseFacade::GetInstance()->AddSharedEvent(ptr);
    Navigate("EventsListView");
}

