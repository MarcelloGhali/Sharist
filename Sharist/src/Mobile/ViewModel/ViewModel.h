#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <string>
#include "AppBaseFacade.h"
#include <QQuickView>

class ViewModel : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void NavigateBack();
    ViewModel(const QUrl &url, QObject *parent=0);
    ViewModel();
    QUrl GetUrl() const;
private:
    QUrl _url;
signals:
    void Navigate(string target);
    void Navigate(string target, const shared_ptr<QObject> &model, const bool &pop = false);
};

typedef std::shared_ptr<ViewModel> ViewModelPtr;

#endif // VIEWMODEL_H
