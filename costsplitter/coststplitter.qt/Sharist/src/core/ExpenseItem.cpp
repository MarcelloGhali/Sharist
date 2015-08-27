//#include "stdafx.h"
#include "ExpenseItem.h"

using namespace::std;

ExpenseItem::ExpenseItem(double cost, const Member* owner, vector<const Member*>* coveredMembers, vector<const Member*>* paid)
{
	this->cost = cost;
	this->owner = owner;
	this->coveredMembers = coveredMembers;
	this->paid = paid;
}

ExpenseItem::~ExpenseItem()
{

}
