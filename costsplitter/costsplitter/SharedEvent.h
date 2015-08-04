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
	//TODO:add growth
	int size = 10;
	const double growthCoefficient = 0.5;
	double** expenseMap, ** optimizedMap;
	double* balanceVector;
	double** initMatrix(int n);
	double* initVector(int n);
	bool areNewPeopleAdded(const ExpenseItem* item);
	const Member* findMember(int index);
public:
	SharedEvent();
	void RemoveExpenseItem(const ExpenseItem* item);
	void AddExpenseItem(const ExpenseItem* item);
	void AddMember(const Member* newMember);
	void RemoveMember(const Member* memberToRemove);
	double** Optimize();
	double** Optimize(double** input);
	void Print();
	~SharedEvent();
};

