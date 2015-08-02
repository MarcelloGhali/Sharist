#include "stdafx.h"
#include "SharedEvent.h"

void SharedEvent::print(double** input, int i, int j){
	printf("%d %d \n", i, j);
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			std::cout << expenseMap[i][j] << " ";
		}

		printf("\n");
	}

	printf("\n");
	printf("\n");
}

double* SharedEvent::initVector(int n){
	balanceVector = new double[n];
	// basic init of the map
	for (int i = 0; i < n; i++)
	{
		balanceVector[i] = 0;
	}

	return balanceVector;
}

double** SharedEvent::initMatrix(int size){
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

bool SharedEvent::areNewPeopleAdded(const ExpenseItem* item){
	return true;
}

SharedEvent::SharedEvent()
{
	expenseMap = initMatrix(size);
	optimizedMap = initMatrix(size);
	balanceVector = initVector(size);
	lastMemberOrder = 0;
}

SharedEvent::~SharedEvent()
{
	for (int i = 0; i < size; i++)
	{
		delete[] this->expenseMap[i];
		delete[] this->optimizedMap[i];
	}

	delete[] this->balanceVector;
	delete[] this->expenseMap;
	delete[] this->optimizedMap;
}

void SharedEvent::AddExpenseItem(const ExpenseItem* item){
	//TODO:we currently don't support members in a group
	int splitNumber = item->paid->size() + 1;
	double share = item->cost / splitNumber;
	// if newPeopleAreAdded
	if (areNewPeopleAdded(item)){

	}

	// TODO: validation
	int ownerIndex = membersMap[item->owner];
	for (vector<const Member*>::iterator it = item->paid->begin(); it < item->paid->end(); it++)
	{
		int paidForMemberIndex = membersMap[*it];
		this->expenseMap[paidForMemberIndex][ownerIndex] += share;
	}
}

//TODO:implememnt remove member 
void SharedEvent::RemoveMember(const Member* memberToRemove){
	membersMap.erase(memberToRemove);
}

//TODO:implement add member
void SharedEvent::AddMember(const Member* newMember){
	membersMap.insert(std::pair<const Member*, int>(newMember, lastMemberOrder++));
}

double** SharedEvent::Optimize(double** input){
	expenseMap = input;
	return Optimize();
}

double** SharedEvent::Optimize(){
	//calculating balance vector
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			balanceVector[i] += expenseMap[j][i] - expenseMap[i][j];
		}
	}

	//optimizing
	int sI = -1, lI = -1;
	while (true){
		//geting the <0 number
		for (int i = 0; i < size; i++)
		{
			if (balanceVector[i] < 0){
				sI = i;
				break;
			}
		}

		//getting the >0 number
		for (int i = 0; i < size; i++)
		{
			if (balanceVector[i] > 0){
				lI = i;
				break;
			}
		}

		if (sI > -1 && lI > -1){
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