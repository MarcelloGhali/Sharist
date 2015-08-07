// costsplitter.test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SharedEvent.h"
#define BOOST_TEST_MODULE MyTest
#include "boost/test/unit_test.hpp"

BOOST_AUTO_TEST_CASE(sharedevent_should_expand_if_new_members_added){
	Member* marat = new Member("Marat");
	Member* alex = new Member("Alex");
	Member* slava = new Member("Slava");
	vector<const Member*>* maratMembers = new vector<const Member*>();
	maratMembers->push_back(alex);
	maratMembers->push_back(slava);
	ExpenseItem* gas = new ExpenseItem(100, marat, 0, maratMembers);
	SharedEvent* oregon = new SharedEvent();
	oregon->AddMember(marat);
	oregon->AddMember(alex);
	oregon->AddMember(slava);
	oregon->AddExpenseItem(gas);
	double **results = oregon->Optimize();
	int countResults = oregon->GetCapacity();
	//adding new users
	vector<const Member*>* tmpMembers = new vector<const Member*>();
	for (int i = 0; i < 10; i++){
		const Member *tmpMember = new Member("test");
		tmpMembers->push_back(tmpMember);
		oregon->AddMember(tmpMember);
	}
	//check
	double **expandedResults = oregon->Optimize();
	int countExpandedResults = oregon->GetCapacity();
	BOOST_CHECK(countResults*oregon->GetGrowthRate() == countExpandedResults);
	//cleanup
	for (vector<const Member*>::iterator it = tmpMembers->begin(); it < tmpMembers->end(); it++){
		delete *it;
	}

	delete tmpMembers;
}