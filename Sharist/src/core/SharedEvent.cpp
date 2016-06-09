#include "SharedEvent.h"
#include <cmath>
#include <string>
#include <sstream>

SharedEvent::SharedEvent(const string& name):
    membersMap(),
    lastMemberOrder(0),
    expenseMapV(InitSize*InitSize, 0),
    optimizedMapV(InitSize*InitSize, 0),
    eventName(name){
}

string SharedEvent::GetEventName(){
    return eventName;
}

void SharedEvent::SetEventName(const string& name){
    this->eventName = name;
}

void SharedEvent::AddExpenseItem(const ExpenseItemPtr &item){
	// TODO : we currently don't support members in a group
    // TODO: bug size + 1
    int splitNumber = item->paid.size();
	double share = item->cost / splitNumber;
	// TODO : add validation. Currently users needs to be added prior to adding an expense item
//	if (areNewPeopleAdded(item)){

//	}

	// TODO: validation
	int ownerIndex = membersMap[item->owner];
    int k = expenseMapV.size()/InitSize;
    for (vector<MemberPtr>::iterator it = item->paid.begin(); it < item->paid.end(); it++){
        int paidForMemberIndex = membersMap[*it];
        this->expenseMapV[paidForMemberIndex*k + ownerIndex] += share;
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
    int currentSize = std::sqrt(expenseMapV.size());
    // number of members exceed number of available slots check
    if (currentSize == members.size()){
        // doubling current size
        int newSize = currentSize * GrowthFactor;
        expenseMapV.resize(newSize * newSize, 0);
    }

    members.push_back(newMember);
    membersMap.insert(std::pair<MemberPtr, int>(newMember, lastMemberOrder++));
}

vector<double> SharedEvent::Optimize(){
    int k = std::sqrt(expenseMapV.size());
    vector<double> balanceVectorV(k, 0);

    // clearing previously calculated map
    optimizedMapV.clear();
    optimizedMapV.resize(expenseMapV.size(), 0);

	//calculating balance vector
    for (int i = 0; i < k; i++){
        for (int j = 0; j < k; j++){
            balanceVectorV[i] += expenseMapV[j*k + i] - expenseMapV[i*k + j];
		}
	}

	//optimizing
    int negativeI = -1, positiveI = -1;
	while (true){
		//geting the <0 number
        for (vector<double>::iterator it = balanceVectorV.begin(); it < balanceVectorV.end(); it++){
            if (*it < 0){
                negativeI = it - balanceVectorV.begin();
				break;
			}
		}

		//getting the >0 number
        for (vector<double>::iterator it = balanceVectorV.begin(); it < balanceVectorV.end(); it++){
            if (*it > 0){
                positiveI = it - balanceVectorV.begin();
				break;
			}
		}

        if (negativeI > -1 && positiveI > -1){
            if (abs(balanceVectorV[positiveI]) > abs(balanceVectorV[negativeI])){
                optimizedMapV[negativeI*k + positiveI] = abs(balanceVectorV[negativeI]);
                balanceVectorV[positiveI] += balanceVectorV[negativeI];
                balanceVectorV[negativeI] = 0;
			}
			else{
                optimizedMapV[negativeI*k + positiveI] = balanceVectorV[positiveI];
                balanceVectorV[negativeI] += balanceVectorV[positiveI];
                balanceVectorV[positiveI] = 0;
			}
		}
		else break;

        negativeI = -1, positiveI = -1;
	}

    return optimizedMapV;
}

string SharedEvent::Print(){
    string toReturn;
    std::ostringstream str;
    int k = optimizedMapV.size()/InitSize;
    for (int i = 0; i < this->lastMemberOrder; i++){
        for (int j = 0; j < this->lastMemberOrder; j++){
            if (optimizedMapV[i*k + j] == 0) continue;
            str<<this->findMember(i)->Name;
            str<<" owes ";
            str<<this->findMember(j)->Name;
            str<<": ";
            str<<optimizedMapV[i*k + j];
            str<<"\n";
            //printf("%s owes %s: %f \n", this->findMember(i)->Name.c_str(), this->findMember(j)->Name.c_str(), optimizedMap[i*size + j]);
        }
    }

    double totalSpent = 0;
    double totalOwe = 0;
//    for (int i = 0; i < size; i++){
//        if (balanceVector[i] < 0) totalOwe += balanceVector[i];
//        else totalSpent += balanceVector[i];
//    }

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

MemberPtr SharedEvent::findMember(int index) {
    for (map<MemberPtr, int>::iterator it = this->membersMap.begin(); it != this->membersMap.end(); it++){
        if (it->second == index){
            return it->first;
        }
    }

    return 0;
}

vector<MemberPtr> SharedEvent::GetMembers(){
    return members;
}

vector<ExpenseItemPtr> SharedEvent::GetExpenseItems(){
    return expenseItems;
}
