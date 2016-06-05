#include "ExpenseItem.h"

using namespace::std;

ExpenseItem::ExpenseItem():
    paid(),
    owner(),
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
