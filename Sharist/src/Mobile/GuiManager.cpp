#include "GuiManager.h"
#include "ViewModel/SharedEventListView.h"
#include "ViewModel/SharedEventNewView.h"
#include "ViewModel/SharedEventDetailsView.h"
#include "ViewModel/MemberNewView.h"
#include "ViewModel/ExpenseNewView.h"
#include <QQuickItem>
#include <QQmlContext>
#include <QQmlProperty>

GuiManager::GuiManager():
    _baseView(QUrl("qrc:/Base.qml")){
    QQuickItem* root = _baseView.rootObject();
    _navigator = root->findChild<QObject*>("navigatorObj",Qt::FindChildrenRecursively);
    mapping["EventsListView"] = shared_ptr<SharedEventListView>(new SharedEventListView());
    mapping["NewEventView"] = shared_ptr<SharedEventNewView>(new SharedEventNewView());
    mapping["DetailsEventView"] = shared_ptr<SharedEventDetailsView>(new SharedEventDetailsView());
    mapping["MemberNewView"] = shared_ptr<MemberNewView>(new MemberNewView());
    mapping["ExpenseNewView"] = shared_ptr<ExpenseNewView>(new ExpenseNewView());
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
    context->setContextProperty(QString::fromStdString("viewmodel" + viewName), viewModel);
    QMetaObject::invokeMethod(_navigator, "push", Qt::QueuedConnection, Q_ARG(QVariant, url));
}

void GuiManager::Navigate(const string &viewName, QObject *params){
    ViewModel* viewModel = mapping[viewName].get();
    ParameterizedViewModel* pViewModel = qobject_cast<ParameterizedViewModel*>(viewModel);
    pViewModel->Show(params);
    QUrl url = viewModel->GetUrl();
    QQmlContext *context = _baseView.rootContext();
    context->setContextProperty(QString::fromStdString("viewmodel" + viewName), viewModel);
    QMetaObject::invokeMethod(_navigator, "push", Qt::QueuedConnection, Q_ARG(QVariant, url));

}
