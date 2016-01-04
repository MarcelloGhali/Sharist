//#include "stdafx.h"
#include "ExpenseItem.h"

using namespace::std;

ExpenseItem::ExpenseItem():
    paid(NULL),
    owner(NULL),
    cost(0){
}

ExpenseItem::ExpenseItem(double cost, const MemberPtr &owner, const vector<MemberPtr> &coveredMembers, const vector<MemberPtr> &paid):
    cost(cost),
    owner(owner),
    coveredMembers(coveredMembers),
    paid(paid){
}

ExpenseItem::~ExpenseItem(){
}
