//#include "stdafx.h"
#include "ExpenseItem.h"

using namespace::std;

ExpenseItem::ExpenseItem(){
    this->paid = new vector<const Member*>;
    this->owner = NULL;
    this->cost = 0;
}

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
