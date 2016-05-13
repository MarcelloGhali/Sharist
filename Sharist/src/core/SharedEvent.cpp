#include "SharedEvent.h"
#include <cmath>
#include <string>
#include <sstream>

int SharedEvent::size = 5;
double SharedEvent::growthCoefficient = 2;

SharedEvent::SharedEvent(string name):
    eventName(name),
    expenseMap(initVector(size*size)),
    optimizedMap(initVector(size*size)),
    balanceVector(initVector(size)),
    lastMemberOrder(0){
}

SharedEvent::~SharedEvent(){
    dispose();
}

int SharedEvent::GetCapacity(){
	return this->size;
}

string SharedEvent::GetEventName(){
    return eventName;
}

void SharedEvent::SetEventName(string name){
    this->eventName = name;
}

int SharedEvent::GetGrowthRate(){
	return this->growthCoefficient;
}

void SharedEvent::AddExpenseItem(const ExpenseItemPtr &item){
	// TODO : we currently don't support members in a group
    int splitNumber = item->paid.size();
	double share = item->cost / splitNumber;
	// TODO : add validation. Currently users needs to be added prior to adding an expense item
//	if (areNewPeopleAdded(item)){

//	}

	// TODO: validation
	int ownerIndex = membersMap[item->owner];
    for (vector<MemberPtr>::iterator it = item->paid.begin(); it < item->paid.end(); it++){
        int paidForMemberIndex = membersMap[*it];
        this->expenseMap[paidForMemberIndex*size + ownerIndex] += share;
	}

    expenseItems.push_back(item);
}

//TODO:implement expense item removal
void SharedEvent::RemoveExpenseItem(const ExpenseItemPtr &item){
    vector<ExpenseItemPtr>::iterator pos = find(expenseItems.begin(), expenseItems.end(), item);
	expenseItems.erase(pos);
}

//TODO:implememnt remove member 
void SharedEvent::RemoveMember(const MemberPtr &memberToRemove){
	membersMap.erase(memberToRemove);
}

void SharedEvent::AddMember(const MemberPtr &newMember){
	// it is time to grow
	// TODO: add option to re-calculate certain expenses
	if (lastMemberOrder == size){
        expand();
	}
    members.push_back(newMember);
    membersMap.insert(std::pair<MemberPtr, int>(newMember, lastMemberOrder++));
}

double* SharedEvent::Optimize(double* input){
	expenseMap = input;
	return Optimize();
}

double* SharedEvent::Optimize(){
    //TODO: cover with idenmotancy tests
    //clearing balance vector
    for(int i=0;i<size;i++){
        balanceVector[i]=0;
    }
    //clearing optimized map
    for(int i=0;i<size*size;i++){
        optimizedMap[i]=0;
    }


	//calculating balance vector
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
            balanceVector[i] += expenseMap[j*size + i] - expenseMap[i*size + j];
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
                optimizedMap[negativeI*size + positiveI] = abs(balanceVectorCpy[negativeI]);
				balanceVectorCpy[positiveI] += balanceVectorCpy[negativeI];
				balanceVectorCpy[negativeI] = 0;
			}
			else{
                optimizedMap[negativeI*size + positiveI] = balanceVectorCpy[positiveI];
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

string SharedEvent::Print(){
    string toReturn;
    std::ostringstream str;
    for (int i = 0; i < this->lastMemberOrder; i++){
        for (int j = 0; j < this->lastMemberOrder; j++){
            if (optimizedMap[i*size + j] == 0) continue;
            str<<this->findMember(i)->Name;
            str<<" owes ";
            str<<this->findMember(j)->Name;
            str<<": ";
            str<<optimizedMap[i*size + j];
            str<<"\n";
            //printf("%s owes %s: %f \n", this->findMember(i)->Name.c_str(), this->findMember(j)->Name.c_str(), optimizedMap[i*size + j]);
        }
    }

    double totalSpent = 0;
    double totalOwe = 0;
    for (int i = 0; i < size; i++){
        if (balanceVector[i] < 0) totalOwe += balanceVector[i];
        else totalSpent += balanceVector[i];
    }

    // TODO: define what is total spend and total debt
    totalSpent=0;
    for(vector<ExpenseItemPtr>::iterator it=expenseItems.begin(); it!=expenseItems.end();it++){
        totalSpent+=(**it).cost;
    }

    str<<"\nTotal spent: ";
    str<<totalSpent;
    str<<"\nTotal debt: ";
    str<<totalOwe;
    //printf("Total spent: %f\nTotal debt: %f", totalSpent, totalOwe);
    toReturn=str.str();
    return toReturn;
}

void SharedEvent::dispose(){
    delete[] this->balanceVector;
    delete[] this->expenseMap;
    delete[] this->optimizedMap;
}

void SharedEvent::expand(){
    int newSize = size * growthCoefficient;
    double* newExpenseMap, *newOptimizedMap;
    double* newBalanceVector;
    //init
    newExpenseMap = initVector(newSize*newSize);
    newOptimizedMap = initVector(newSize*newSize);
    newBalanceVector = initVector(newSize);
    //copy
    memcpy(newExpenseMap, expenseMap, size*sizeof(expenseMap));
    memcpy(newOptimizedMap, optimizedMap, size*sizeof(optimizedMap));
    memcpy(newBalanceVector, balanceVector, size*sizeof(balanceVector));
    //recycle
    dispose();
    //swap
    expenseMap = newExpenseMap;
    optimizedMap = newOptimizedMap;
    balanceVector = newBalanceVector;
    size = newSize;
}

MemberPtr SharedEvent::findMember(int index) {
    for (map<MemberPtr, int>::iterator it = this->membersMap.begin(); it != this->membersMap.end(); it++){
        if (it->second == index){
            return it->first;
        }
    }

    return 0;
}

double* SharedEvent::initVector(int n){
    double* toReturn = new double[n];
    // basic init of the map
    for (int i = 0; i < n; i++){
        toReturn[i] = 0;
    }

    return toReturn;
}

vector<MemberPtr>* SharedEvent::GetMembers(){
    return &members;
}
