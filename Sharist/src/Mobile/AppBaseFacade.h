#ifndef APPBASEFACADE_H
#define APPBASEFACADE_H

#include "SharedEvent.h"
#include "SharedEventListModel.h"

class AppBaseFacade
{
public:
    void AddSharedEvent(const SharedEventModelPtr &model);
    SharedEventListModelPtr GetSharedEventList();
    static AppBaseFacade* GetInstance();
private:
    static AppBaseFacade* _instance;
    AppBaseFacade();
    vector<SharedEventPtr> _sharedEventList;
    SharedEventListModelPtr _sharedEventModelList;
};

typedef shared_ptr<AppBaseFacade> AppBaseFacadePtr;
#endif // APPBASEFACADE_H
