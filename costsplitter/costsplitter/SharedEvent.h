#pragma once
#include "ExpenseItem.h"
#include "Member.h"
#include "stdafx.h"

class SharedEvent
{
private:
	map<const Member*, int> membersMap;
	int lastMemberOrder;
	const int size = 10;
	const double growthCoefficient = 0.5;
	double** expenseMap, ** optimizedMap;
	double* balanceVector;
	int countSplitParties(const ExpenseItem* item);
	void print(double** matrix, int i, int j);
	double** initMatrix(int n);
	double* initVector(int n);
	bool areNewPeopleAdded(const ExpenseItem* item);
public:
	SharedEvent();
	void RemoveExpenseItem(const ExpenseItem* item);
	void AddExpenseItem(const ExpenseItem* item);
	void AddMember(const Member* newMember);
	void RemoveMember(const Member* memberToRemove);
	double** Optimize();
	double** Optimize(double** input);
	~SharedEvent();
};

