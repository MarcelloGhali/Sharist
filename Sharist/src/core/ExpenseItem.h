#ifndef EXPENSEITEM_H
#define EXPENSEITEM_H
#include <memory>
#include <vector>
#include "Member.h"

using namespace::std;

class ExpenseItem{
public:
	double cost;
    MemberPtr owner;
    vector<MemberPtr> coveredMembers;
    vector<MemberPtr> paid;
    ExpenseItem();
    //TODO: redesign to avoid copy of vectors
    ExpenseItem(double cost, const MemberPtr &owner, const vector<MemberPtr> &coveredMembers, const vector<MemberPtr> &paid);
	~ExpenseItem();
};

typedef shared_ptr<ExpenseItem> ExpenseItemPtr;

#endif
