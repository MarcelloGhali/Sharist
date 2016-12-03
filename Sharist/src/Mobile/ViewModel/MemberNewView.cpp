#include "MemberNewView.h"

MemberNewView::MemberNewView(QObject *parent):
    ParameterizedViewModel(QUrl("qrc:/NewMember.qml"), parent){

}

void MemberNewView::setName(const QString &name){
    _name = name;
}

QString MemberNewView::getName(){
    return _name;
}

void MemberNewView::Save(){
    _eventPtr->AddMember(_name);
    emit Navigate("DetailsEventView",_eventPtr, true);
}

void MemberNewView::Show(const shared_ptr<QObject> &model){
    _eventPtr = dynamic_pointer_cast<SharedEventModel>(model);
}
