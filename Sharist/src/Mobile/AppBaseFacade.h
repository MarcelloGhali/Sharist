#ifndef APPBASEFACADE_H
#define APPBASEFACADE_H

#include "SharedEvent.h"
#include "Model/SharedEventListModel.h"

class AppBaseFacade
{
public:
    void AddMember(const MemberModelPtr &model);
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
