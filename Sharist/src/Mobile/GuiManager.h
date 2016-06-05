#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <QObject>
#include <QHash>
#include <string>
#include <QQuickView>
#include "ViewModel.h"

using namespace std;

class GuiManager : QObject
{
    Q_OBJECT
private:
    QObject *_navigator;
    QQuickView _baseView;
    std::map<string, ViewModelPtr> mapping;
public:
    GuiManager();
    void Start();
public slots:
    void Navigate(const string &viewName);
    void Navigate(const string &viewName, QObject* params);
};

typedef std::shared_ptr<GuiManager> GuiManagerPtr;
#endif // NAVIGATOR_H
