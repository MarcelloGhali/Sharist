#include "stdafx.h"
#include "Ocasion.h"
#include <math.h>

void Ocasion::print(double** input, int i, int j){
	printf("%d %d \n", i, j);
	for (int i = 0; i < this->partyCount; i++)
	{
		for (int j = 0; j < this->partyCount; j++)
		{
			std::cout << expenseMap[i][j] << " ";
		}

		printf("\n");
	}

	printf("\n");
	printf("\n");
}

double* Ocasion::initVector(int n){
	balanceVector = new double[n];
	// basic init of the map
	for (int i = 0; i < n; i++)
	{
		balanceVector[i] = 0;
	}

	return balanceVector;
}

double** Ocasion::initMatrix(int size){
	double** toReturn = new double*[size];
	// basic init of the map
	for (int i = 0; i < size; i++)
	{
		toReturn[i] = new double[size];
	}

	//zeroing
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			toReturn[i][j] = 0;
		}
	}

	return toReturn;
}

int Ocasion::countSplitParties(ExpenseItem* item){
	int count = 0;
	for (int i = 0; i < this->partyCount; i++)
	{
		if (item->numberOfGroupsCovered[i]) count++;
	}

	return count;
}

Ocasion::Ocasion(int n)
{
	partyCount = n;
	expenseMap = initMatrix(n);
	optimizedMap = initMatrix(n);
	balanceVector = initVector(n);
}

Ocasion::~Ocasion()
{
	// deallocation
	for (int i = 0; i < partyCount; i++)
	{
		delete[] this->expenseMap[i];
		delete[] this->optimizedMap[i];
	}

	//TODO: deallocate vector, results
	delete[] this->balanceVector;

}

void Ocasion::AddExpenseItem(ExpenseItem* item){
	int splitNumber = countSplitParties(item);
	double share = item->cost / splitNumber;
	for (int i = 0; i < this->partyCount; i++)
	{
		if (item->numberOfGroupsCovered[i]){
			if (i != item->owner){
				this->expenseMap[i][item->owner] += share;
			}
		}
	}
}

double** Ocasion::Optimize(double** input){
	expenseMap = input;
	return Optimize();
}


double** Ocasion::Optimize(){
	//calculating balance vector
	for (int i = 0; i < partyCount; i++)
	{
		for (int j = 0; j < partyCount; j++)
		{
			balanceVector[i] += expenseMap[j][i] - expenseMap[i][j];
		}
	}

	//optimizing
	int sI = -1, lI = -1;
	while (true){
		//geting the <0 number
		for (int i = 0; i < partyCount; i++)
		{
			if (balanceVector[i] < 0){
				sI = i;
				break;
			}
		}

		//getting the >0 number
		for (int i = 0; i < partyCount; i++)
		{
			if (balanceVector[i] > 0){
				lI = i;
				break;
			}
		}

		if (sI>-1 && lI > -1){
			if (abs(balanceVector[lI]) > abs(balanceVector[sI])){
				optimizedMap[sI][lI] = abs(balanceVector[sI]);
				balanceVector[lI] += balanceVector[sI];
				balanceVector[sI] = 0;
			}
			else{
				optimizedMap[sI][lI] = balanceVector[lI];
				balanceVector[sI] += balanceVector[lI];
				balanceVector[lI] = 0;
			}
		}
		else break;

		sI = -1, lI = -1;
	}

	return optimizedMap;
}