#include "SharedEventDetailsView.h"

SharedEventDetailsView::SharedEventDetailsView(QObject *parent):
    ParameterizedViewModel(QUrl("qrc:/DetailsSharedEvent.qml"), parent){

}

SharedEventModel* SharedEventDetailsView::getEventModel(){
    return _eventModel;
}

void SharedEventDetailsView::Show(QObject *model){
    _eventModel = qobject_cast<SharedEventModel*>(model);
}
