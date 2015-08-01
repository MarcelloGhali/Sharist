#pragma once
#include "stdafx.h"
#include "Member.h"

class ExpenseItem
{
public:
	double cost;
	const Member* owner;
	vector<const Member*>* coveredMembers;
	vector<const Member*>* paid;
	ExpenseItem(double cost, const Member* owner, vector<const Member*>* coveredMembers, vector<const Member*>* paid);
	~ExpenseItem();
};

