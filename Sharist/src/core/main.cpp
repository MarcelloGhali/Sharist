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
	Member* marat = new Member("Marat");
	Member* alex = new Member("Alex");
	Member* slava = new Member("Slava");
	Member* mila = new Member("Mila");
	vector<const Member*>* maratMembers = new vector<const Member*>();
	maratMembers->push_back(alex);
	maratMembers->push_back(slava);
	vector<const Member*>* slavaMembers = new vector<const Member*>();
	slavaMembers->push_back(marat);
	slavaMembers->push_back(alex);
	slavaMembers->push_back(mila);
	vector<const Member*>* alexMembers = new vector<const Member*>();
	alexMembers->push_back(marat);
	alexMembers->push_back(slava);
	alexMembers->push_back(mila);
	ExpenseItem* gas = new ExpenseItem(100, marat, 0, maratMembers);
	ExpenseItem* food = new ExpenseItem(100, slava, 0, slavaMembers);
	ExpenseItem* alexexp = new ExpenseItem(110, alex, 0, alexMembers);
	ExpenseItem* milaexp = new ExpenseItem(60, mila, 0, maratMembers);
	SharedEvent* oregon = new SharedEvent();
	oregon->AddMember(marat);
	oregon->AddMember(alex);
	oregon->AddMember(slava);
	oregon->AddMember(mila);
	oregon->AddExpenseItem(gas);
	oregon->AddExpenseItem(food);
	oregon->AddExpenseItem(alexexp);
	oregon->AddExpenseItem(milaexp);
	oregon->Optimize();
	oregon->Print();
	return 0;
}

