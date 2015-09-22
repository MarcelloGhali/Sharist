#include "ExpenseItem.h"
#include <vector>
#include <map>

class SharedEvent
{
private:
    vector<const ExpenseItem*> expenseItems;
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
	void RemoveExpenseItem(const ExpenseItem* item);
	void AddExpenseItem(const ExpenseItem* item);
	void AddMember(const Member* newMember);
	void RemoveMember(const Member* memberToRemove);
	int GetCapacity();
	int GetGrowthRate();
    string GetEventName() const;
    double* Optimize();
    double* Optimize(double* input);
	void Print();
	~SharedEvent();
};

