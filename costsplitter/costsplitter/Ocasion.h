#pragma once
#include "ExpenseItem.h"
class Ocasion
{
private:
	int partyCount;
	double** expenseMap,** optimizedMap;
	double* balanceVector;
	double* initVector(int n);
	int countSplitParties(const ExpenseItem* item);
	bool isMutualDebt(int i, int j);
	int tryGetIndirectDebtRow(int i, int j);
	int tryGetInirectConnectingRow(int i, int j);
	void print(double** matrix, int i, int j);
	double** initMatrix(int n);
public:
	Ocasion(int n);
	void AddExpenseItem(const ExpenseItem* item);
	double** Optimize();
	double** Optimize(double** input);
	~Ocasion();
};

