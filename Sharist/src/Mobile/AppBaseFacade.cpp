#include "AppBaseFacade.h"

AppBaseFacade::AppBaseFacade(){
    //model setup
    // core
    MemberPtr slavaP(new Member("Slava"));
    MemberPtr maratP(new Member("Marat"));
    MemberPtr alexP(new Member("Alex"));
    MemberPtr ruslanP(new Member("Ruslan"));
    //Oregon set up
    SharedEventPtr oregonPtr(new SharedEvent("Oregon"));
    vector<MemberPtr> paid;
    paid.push_back(slavaP);
    paid.push_back(alexP);
    ExpenseItemPtr itemP(new ExpenseItem(40, maratP, vector<MemberPtr>(), paid));
    oregonPtr->AddMember(slavaP);
    oregonPtr->AddMember(alexP);
    oregonPtr->AddMember(maratP);
    oregonPtr->AddExpenseItem(itemP);
    //Idaho set up
    SharedEventPtr idahoPtr(new SharedEvent("Idaho"));
    idahoPtr->AddMember(alexP);
    idahoPtr->AddMember(maratP);
    idahoPtr->AddMember(ruslanP);
    vector<SharedEventPtr> eventsList;
    eventsList.push_back(oregonPtr);
    eventsList.push_back(idahoPtr);
    _sharedEventModelList = SharedEventListModelPtr(new SharedEventListModel(0, eventsList));
}

SharedEventListModelPtr AppBaseFacade::GetSharedEventList(){
    return _sharedEventModelList;
}

AppBaseFacade* AppBaseFacade::_instance=0;

AppBaseFacade* AppBaseFacade::GetInstance(){
    if (!_instance){
        _instance = new AppBaseFacade();
    }

    return _instance;
}

void AppBaseFacade::AddSharedEvent(const SharedEventModelPtr &model){
    _sharedEventModelList.get()->addSharedEvent(model);
}

void AppBaseFacade::AddMember(const MemberModelPtr &model){

}
