#include "stdafx.h"
#include "SharedEvent.h"

void SharedEvent::Print(){
	for (int i = 0; i < this->lastMemberOrder; i++){
		for (int j = 0; j < this->lastMemberOrder; j++){
			if (optimizedMap[i][j] == 0) continue;
			printf("%s owes %s: %f \n", this->findMember(i)->Name.c_str(), this->findMember(j)->Name.c_str(), optimizedMap[i][j]);
		}
	}

	double totalSpent = 0;
	double totalOwe = 0;
	for (int i = 0; i < size; i++){
		if (balanceVector[i] < 0) totalOwe += balanceVector[i];
		else totalSpent += balanceVector[i];
	}

	printf("Total spent: %f\nTotal debt: %f", totalSpent, totalOwe);
}

void SharedEvent::Dispose(){
	delete[] this->balanceVector;
	delete[] this->expenseMap;
	delete[] this->optimizedMap;
}

double* SharedEvent::initVector(int n){
	double* toReturn = new double[n];
	// basic init of the map
	for (int i = 0; i < n; i++){
		toReturn[i] = 0;
	}

	return toReturn;
}

double** SharedEvent::initMatrix(int size){
	double** toReturn = new double*[size];
	// basic init of the map
	for (int i = 0; i < size; i++){
		toReturn[i] = new double[size];
	}

	//zeroing
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			toReturn[i][j] = 0;
		}
	}

	return toReturn;

}
SharedEvent::SharedEvent(){
	expenseMap = initMatrix(size);
	optimizedMap = initMatrix(size);
	balanceVector = initVector(size);
	expenseItems = new vector<const ExpenseItem*>();
	membersMap = new map<const Member*, int>();
	lastMemberOrder = 0;
}

SharedEvent::~SharedEvent(){
	Dispose();

	delete this->membersMap;
	delete this->expenseItems;
}

void SharedEvent::Expand(){
	int newSize = size * growthCoefficient;
	double** newExpenseMap, **newOptimizedMap;
	double* newBalanceVector;
	//init
	newExpenseMap = initMatrix(newSize);
	newOptimizedMap = initMatrix(newSize);
	newBalanceVector = initVector(newSize);
	//copy
	memcpy(newExpenseMap, expenseMap, size*sizeof(expenseMap));
	memcpy(newOptimizedMap, optimizedMap, size*sizeof(optimizedMap));
	memcpy(newBalanceVector, balanceVector, size*sizeof(balanceVector));
	//recycle
	Dispose();
	//swap
	expenseMap = newExpenseMap;
	optimizedMap = newOptimizedMap;
	balanceVector = newBalanceVector;
	size = newSize;
}

const Member* SharedEvent::findMember(int index){
	for (map<const Member*, int>::iterator it = this->membersMap->begin(); it != this->membersMap->end(); it++){
		if (it->second == index){
			return it->first;
		}
	}

	return 0;
}

bool SharedEvent::areNewPeopleAdded(const ExpenseItem* item){
	return true;
}

int SharedEvent::GetCapacity(){
	return this->size;
}

int SharedEvent::GetGrowthRate(){
	return this->growthCoefficient;
}

void SharedEvent::AddExpenseItem(const ExpenseItem* item){
	expenseItems->push_back(item);
	// TODO : we currently don't support members in a group
	int splitNumber = item->paid->size() + 1;
	double share = item->cost / splitNumber;
	// TODO : add validation. Currently users needs to be added prior to adding an expense item
	if (areNewPeopleAdded(item)){

	}

	// TODO: validation
	int ownerIndex = membersMap->operator[](item->owner);
	for (vector<const Member*>::iterator it = item->paid->begin(); it < item->paid->end(); it++){
		int paidForMemberIndex = membersMap->operator[](*it);
		this->expenseMap[paidForMemberIndex][ownerIndex] += share;
	}
}

//TODO:implement expense item removal
void SharedEvent::RemoveExpenseItem(const ExpenseItem* item){
	vector<const ExpenseItem*>::iterator pos = find(this->expenseItems->begin(), this->expenseItems->end(), item);
	expenseItems->erase(pos);
}

//TODO:implememnt remove member 
void SharedEvent::RemoveMember(const Member* memberToRemove){
	membersMap->erase(memberToRemove);
}

void SharedEvent::AddMember(const Member* newMember){
	// it is time to grow
	// TODO: add option to re-calculate certain expenses
	if (lastMemberOrder == size){
		Expand();
	}

	membersMap->insert(std::pair<const Member*, int>(newMember, lastMemberOrder++));
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

	double* balanceVectorCpy = initVector(size);
	memcpy(balanceVectorCpy, balanceVector, size*sizeof(balanceVector));
	//optimizing
	int negativeI = -1, positiveI = -1;
	while (true){
		//geting the <0 number
		for (int i = 0; i < size; i++){
			if (balanceVectorCpy[i] < 0){
				negativeI = i;
				break;
			}
		}

		//getting the >0 number
		for (int i = 0; i < size; i++){
			if (balanceVectorCpy[i] > 0){
				positiveI = i;
				break;
			}
		}

		if (negativeI > -1 && positiveI > -1){
			if (abs(balanceVectorCpy[positiveI]) > abs(balanceVectorCpy[negativeI])){
				optimizedMap[negativeI][positiveI] = abs(balanceVectorCpy[negativeI]);
				balanceVectorCpy[positiveI] += balanceVectorCpy[negativeI];
				balanceVectorCpy[negativeI] = 0;
			}
			else{
				optimizedMap[negativeI][positiveI] = balanceVectorCpy[positiveI];
				balanceVectorCpy[negativeI] += balanceVectorCpy[positiveI];
				balanceVectorCpy[positiveI] = 0;
			}
		}
		else break;

		negativeI = -1, positiveI = -1;
	}

	delete[] balanceVectorCpy;
	return optimizedMap;
}