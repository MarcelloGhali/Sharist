#ifndef SharedEvent_H
#define SharedEvent_H

#include "ExpenseItem.h"
#include <vector>
#include <map>

class SharedEvent{
private:
    map<MemberPtr, int> membersMap;
    vector<MemberPtr> members;
	int lastMemberOrder;
    const int InitSize = 5;
    const int GrowthFactor = 2;
    vector<double> expenseMapV, optimizedMapV;
    string eventName;
    vector<ExpenseItemPtr> expenseItems;
    MemberPtr findMember(int index);
public:
    SharedEvent(const string& name);
    void RemoveExpenseItem(const ExpenseItemPtr &item);
    void AddExpenseItem(const ExpenseItemPtr &item);
    void AddMember(const MemberPtr &newMember);
    void RemoveMember(const MemberPtr &memberToRemove);
    vector<MemberPtr> GetMembers();
    vector<ExpenseItemPtr> GetExpenseItems();
    string GetEventName();
    void SetEventName(const string& name);
    vector<double> Optimize();
    string Print();
};

typedef shared_ptr<SharedEvent> SharedEventPtr;
#endif
