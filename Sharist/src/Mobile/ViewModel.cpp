#include "ViewModel.h"
#include <QQuickItem>

ViewModel::ViewModel(const QUrl &url, QObject *parent):
    QObject(parent),
    _url(url){
}

QUrl ViewModel::GetUrl() const{
    return _url;
}
