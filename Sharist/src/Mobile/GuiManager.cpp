#include "GuiManager.h"
#include "SharedEventListView.h"
#include "SharedEventNewView.h"
#include "SharedEventDetailsView.h"
#include <QQuickItem>
#include <QQmlContext>

GuiManager::GuiManager():
    _baseView(QUrl("qrc:/Base.qml")){
    QQuickItem* root = _baseView.rootObject();
    _navigator = root->findChild<QObject*>("navigatorObj",Qt::FindChildrenRecursively);
    mapping["EventsListView"] = shared_ptr<SharedEventListView>(new SharedEventListView());
    mapping["NewEventView"] = shared_ptr<SharedEventNewView>(new SharedEventNewView());
    mapping["DetailsEventView"] = shared_ptr<SharedEventDetailsView>(new SharedEventDetailsView());
    for(std::map<string,ViewModelPtr>::iterator it=mapping.begin(); it!=mapping.end(); it++){
        ViewModelPtr viewModel = it->second;
        QObject::connect(viewModel.get(), SIGNAL(Navigate(string, QObject*)),
                         this, SLOT(Navigate(string, QObject*)));
        QObject::connect(viewModel.get(), SIGNAL(Navigate(string)),
                         this, SLOT(Navigate(string)));
    }
}

void GuiManager::Start(){
    this->Navigate("EventsListView");
    _baseView.show();
}

void GuiManager::Navigate(const string &viewName){
    ViewModel* viewModel = mapping[viewName].get();
    QUrl url = viewModel->GetUrl();
    QQmlContext *context = _baseView.rootContext();
    context->setContextProperty("viewmodel", viewModel);
    QMetaObject::invokeMethod(_navigator, "push", Qt::QueuedConnection, Q_ARG(QVariant, url));
}

void GuiManager::Navigate(const string &viewName, QObject *params){
    ViewModel* viewModel = mapping[viewName].get();
    ParameterizedViewModel* pViewModel = qobject_cast<ParameterizedViewModel*>(viewModel);
    pViewModel->Show(params);
    QUrl url = viewModel->GetUrl();
    QQmlContext *context = _baseView.rootContext();
    context->setContextProperty("viewmodel", viewModel);
    QMetaObject::invokeMethod(_navigator, "push", Qt::QueuedConnection, Q_ARG(QVariant, url));
}
