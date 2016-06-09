#ifndef SHAREDEVENTDETAILSVIEW_H
#define SHAREDEVENTDETAILSVIEW_H

#include "ViewModel/ParameterizedViewModel.h"
#include "Model/SharedEventModel.h"

class SharedEventDetailsView : public ParameterizedViewModel
{
    Q_OBJECT
public:
    Q_INVOKABLE void AddExpense();
    Q_INVOKABLE void AddMember();
    Q_PROPERTY(SharedEventModel* eventModel READ getEventModel NOTIFY eventModelChanged)
    SharedEventDetailsView(QObject *parent=0);
    SharedEventModel* getEventModel();
    void Show(QObject* model);
signals:
    void eventModelChanged();
private:
    SharedEventModel* _eventModel;
};

#endif // SHAREDEVENTDETAILSVIEW_H
