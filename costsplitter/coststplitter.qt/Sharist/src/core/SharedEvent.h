#include "ExpenseItem.h"
#include <vector>
#include <map>

class SharedEvent
{
private:
	map<const Member*, int> membersMap;
	int lastMemberOrder;
    static int size;
    static double growthCoefficient;
    double* expenseMap, *optimizedMap;
    double* balanceVector;
    string eventName;
    double* initVector(int n);
	const Member* findMember(int index);
    void expand();
    void dispose();
public:
    SharedEvent(string name);
    vector<const ExpenseItem*> expenseItems;
	void RemoveExpenseItem(const ExpenseItem* item);
	void AddExpenseItem(const ExpenseItem* item);
	void AddMember(const Member* newMember);
	void RemoveMember(const Member* memberToRemove);
	int GetCapacity();
	int GetGrowthRate();
    string GetEventName();
    void SetEventName(string name);
    double* Optimize();
    double* Optimize(double* input);
	void Print();
	~SharedEvent();
};

