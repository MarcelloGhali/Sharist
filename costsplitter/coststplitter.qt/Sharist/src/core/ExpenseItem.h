//#pragma once
//#include "stdafx.h"
#include <vector>
#include "Member.h"

using namespace::std;

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

