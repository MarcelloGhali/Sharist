#include "ExpenseItem.h"
#include <vector>
#include <map>

class SharedEvent{
private:
    map<MemberPtr, int> membersMap;
    vector<MemberPtr> members;
	int lastMemberOrder;
    static int size;
    static double growthCoefficient;
    //TODO: use vector instead
    double* expenseMap, *optimizedMap;
    double* balanceVector;
    string eventName;
    double* initVector(int n);
    MemberPtr findMember(int index);
    void expand();
    void dispose();
public:
    SharedEvent(string name);
    vector<ExpenseItemPtr> expenseItems;
    void RemoveExpenseItem(const ExpenseItemPtr &item);
    void AddExpenseItem(const ExpenseItemPtr &item);
    void AddMember(const MemberPtr &newMember);
    void RemoveMember(const MemberPtr &memberToRemove);
    vector<MemberPtr>* GetMembers();
	int GetCapacity();
	int GetGrowthRate();
    string GetEventName();
    void SetEventName(string name);
    double* Optimize();
    double* Optimize(double* input);
    string Print();
	~SharedEvent();
};

