// costsplitter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SharedEvent.h"

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

int main(int argc, const char * argv[])
{
	int n = 4;
	Member* marat = new Member("Marat");
	Member* alex = new Member("Alex");
	Member* slava = new Member("Slava");
	vector<const Member*>* gasMembers = new vector<const Member*>();
	gasMembers->push_back(alex);
	gasMembers->push_back(slava);
	vector<const Member*>* foodMembers = new vector<const Member*>();
	foodMembers->push_back(marat);
	foodMembers->push_back(alex);
	ExpenseItem* gas = new ExpenseItem(90, marat, 0, gasMembers);
	ExpenseItem* food = new ExpenseItem(100, slava, 0, foodMembers);
	SharedEvent* oregon = new SharedEvent();
	oregon->AddMember(marat);
	oregon->AddMember(alex);
	oregon->AddMember(slava);
	oregon->AddExpenseItem(gas);
	oregon->AddExpenseItem(food);
	double** result = oregon->Optimize();
	print(result, 10);
	//double** set = new double*[n];
	//set[0] = new double[n]{0, 33, 10, 0};
	//set[1] = new double[n]{30, 0, 10, 0};
	//set[2] = new double[n]{30, 33, 0, 0};
	//set[3] = new double[n]{30, 33, 10, 0};

	/*double** result = ocasion.Optimize(set);
	print(result, n);*/
	return 0;
}

