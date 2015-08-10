// costsplitter.test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SharedEvent.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MyTest
#include "boost/test/unit_test.hpp"

BOOST_AUTO_TEST_SUITE(core)

BOOST_AUTO_TEST_CASE(sharedevent_should_expand_if_new_members_added){
	Member marat("Marat");
	Member alex("Alex");
	Member slava("Slava");
	vector<const Member*> maratMembers;
	maratMembers.push_back(&alex);
	maratMembers.push_back(&slava);
	ExpenseItem gas(100, &marat, 0, &maratMembers);
	SharedEvent oregon;
	oregon.AddMember(&marat);
	oregon.AddMember(&alex);
	oregon.AddMember(&slava);
	oregon.AddExpenseItem(&gas);
	oregon.Optimize();
	int countResults = oregon.GetCapacity();
	//adding new users
	for (int i = 0; i < 10; i++){
		Member tmpMember("test");
		oregon.AddMember(&tmpMember);
	}
	//check
	oregon.Optimize();
	int countExpandedResults = oregon.GetCapacity();
	BOOST_CHECK(countResults*oregon.GetGrowthRate() == countExpandedResults);
}

BOOST_AUTO_TEST_CASE(sharedevent_should_return_correct_optimization){
	//setup
	Member marat("Marat");
	Member alex("Alex");
	Member slava("Slava");
	vector<const Member*> maratMembers;
	maratMembers.push_back(&alex);
	maratMembers.push_back(&slava);
	vector<const Member*> slavaMembers;
	slavaMembers.push_back(&alex);
	slavaMembers.push_back(&marat);
	ExpenseItem gas(90, &marat, 0, &maratMembers);
	ExpenseItem food(120, &slava, 0, &slavaMembers);
	SharedEvent oregon;
	oregon.AddMember(&marat);
	oregon.AddMember(&alex);
	oregon.AddMember(&slava);
	oregon.AddExpenseItem(&gas);
	oregon.AddExpenseItem(&food);
	//expected
	double alexOweSlava = 50;
	double alexOweMarat = 20;
	//test
	double** results = oregon.Optimize();
	//adding new users
	BOOST_CHECK(results[1][0] == alexOweMarat);
	BOOST_CHECK(results[1][2] == alexOweSlava);
}

BOOST_AUTO_TEST_SUITE_END()