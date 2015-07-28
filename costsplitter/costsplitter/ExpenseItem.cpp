#include "stdafx.h"
#include "ExpenseItem.h"


ExpenseItem::ExpenseItem(double cost, int owner, int* numberOfGroupsCovered)
{
	this->cost = cost;
	this->owner = owner;
	this->numberOfGroupsCovered = numberOfGroupsCovered;
}


ExpenseItem::~ExpenseItem()
{
}
