#ifndef SHAREDEVENTLISTVIEW_H
#define SHAREDEVENTLISTVIEW_H

#include "Model/SharedEventListModel.h"
#include "ViewModel/ViewModel.h"
#include <QUrl>
#include <QString>
#include <QQuickView>

class SharedEventListView : public ViewModel
{
    Q_OBJECT
public:
    Q_INVOKABLE void NavigateToDetails(const int &index);
    Q_INVOKABLE void NavigateToNew();
    Q_PROPERTY(SharedEventListModel* eventsList READ getEventsList NOTIFY eventsListChanged)
    SharedEventListModel* getEventsList();
    SharedEventListView(QObject *parent=0);
    ~SharedEventListView();
    void Show();
private:
    SharedEventListModelPtr _events;
signals:
    void eventsListChanged();
};

#endif // SHAREDEVENTLISTVIEW_H
