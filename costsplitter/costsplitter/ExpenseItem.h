#pragma once
class ExpenseItem
{
public:
	double cost;
	int owner;
	int* numberOfGroupsCovered;
	ExpenseItem(double cost, int owner, int* numberOfGroupsCovered);
	~ExpenseItem();
};

