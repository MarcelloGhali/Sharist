#pragma once
#include "ExpenseItem.h"
#include "Member.h"
#include "stdafx.h"

class SharedEvent
{
private:
    vector<const ExpenseItem*> expenseItems;
	map<const Member*, int> membersMap;
	int lastMemberOrder;
	int size = 10;
	const double growthCoefficient = 2;
    double* expenseMap, *optimizedMap;
    double* balanceVector;
    double* initVector(int n);
	bool areNewPeopleAdded(const ExpenseItem* item);
	const Member* findMember(int index);
    void expand();
    void dispose();
public:
	SharedEvent();
	void RemoveExpenseItem(const ExpenseItem* item);
	void AddExpenseItem(const ExpenseItem* item);
	void AddMember(const Member* newMember);
	void RemoveMember(const Member* memberToRemove);
	int GetCapacity();
	int GetGrowthRate();
    double* Optimize();
    double* Optimize(double* input);
	void Print();
	~SharedEvent();
};

