#include "stdafx.h"
#include "SharedEvent.h"

void SharedEvent::Print(){
	for (int i = 0; i < this->lastMemberOrder; i++){
		for (int j = 0; j < this->lastMemberOrder; j++){
			if (optimizedMap[i][j] == 0) continue;
			string first = this->findMember(i)->Name;
			string second = this->findMember(j)->Name;
			cout << first << " owes " << second << ": " << optimizedMap[i][j] << "\n";
		}
	}

	printf("\n");
	printf("\n");
}

const Member* SharedEvent::findMember(int index){
	for (map<const Member*, int>::iterator it = this->membersMap.begin(); it != this->membersMap.end(); it++){
		if (it->second == index){
			return it->first;
		}
	}
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
	expenseItems.push_back(item);
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

//TODO:implement expense item removal
void SharedEvent::RemoveExpenseItem(const ExpenseItem* item){
	vector<const ExpenseItem*>::iterator pos = find(expenseItems.begin(), expenseItems.end(), item);
	expenseItems.erase(pos);
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
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			balanceVector[i] += expenseMap[j][i] - expenseMap[i][j];
		}
	}

	//optimizing
	int negativeI = -1, positiveI = -1;
	while (true){
		//geting the <0 number
		for (int i = 0; i < size; i++){
			if (balanceVector[i] < 0){
				negativeI = i;
				break;
			}
		}

		//getting the >0 number
		for (int i = 0; i < size; i++){
			if (balanceVector[i] > 0){
				positiveI = i;
				break;
			}
		}

		if (negativeI > -1 && positiveI > -1){
			if (abs(balanceVector[positiveI]) > abs(balanceVector[negativeI])){
				optimizedMap[negativeI][positiveI] = abs(balanceVector[negativeI]);
				balanceVector[positiveI] += balanceVector[negativeI];
				balanceVector[negativeI] = 0;
			}
			else{
				optimizedMap[negativeI][positiveI] = balanceVector[positiveI];
				balanceVector[negativeI] += balanceVector[positiveI];
				balanceVector[positiveI] = 0;
			}
		}
		else break;

		negativeI = -1, positiveI = -1;
	}

	return optimizedMap;
}