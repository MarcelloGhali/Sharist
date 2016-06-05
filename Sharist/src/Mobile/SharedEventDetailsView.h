#ifndef SHAREDEVENTDETAILSVIEW_H
#define SHAREDEVENTDETAILSVIEW_H

#include "ParameterizedViewModel.h"
#include "SharedEventModel.h"

class SharedEventDetailsView : public ParameterizedViewModel
{
    Q_OBJECT
public:
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
