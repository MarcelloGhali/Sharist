#ifndef PARAMETERIZEDVIEWMODEL_H
#define PARAMETERIZEDVIEWMODEL_H
#include "ViewModel.h"

class ParameterizedViewModel : public ViewModel
{
    Q_OBJECT
public:
    ParameterizedViewModel(const QUrl &url, QObject* parent);
    virtual void Show(QObject* model) = 0;
};

#endif // PARAMETERIZEDVIEWMODEL_H
