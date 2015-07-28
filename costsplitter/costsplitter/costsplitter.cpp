// costsplitter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Ocasion.h"

void print(double ** results, int n){
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%f ",results[i][j]);
		}

		printf("\n");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int n = 4;
	Ocasion ocasion(n);
	/*int gasExpense[3] = { 1, 0, 1 };
	int foodExpense[3] = { 0, 1, 1 };
	ExpenseItem gas(90, 0, gasExpense);
	ExpenseItem food(100, 1, foodExpense);
	ocasion.AddExpenseItem(&gas);
	ocasion.AddExpenseItem(&food);*/

	double** set = new double*[n];
	set[0] = new double[n]{0, 33, 10, 0};
	set[1] = new double[n]{30, 0, 10, 0};
	set[2] = new double[n]{30, 33, 0, 0};
	set[3] = new double[n]{30, 33, 10, 0};

	double** result = ocasion.Optimize(set);
	print(result, n);
	return 0;
}

