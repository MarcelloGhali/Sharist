// costsplitter.test.cpp : Defines the entry point for the console application.
//

#define BOOST_TEST_MODULE MyTest
#include "stdafx.h"
#include "boost/test/unit_test.hpp"

BOOST_AUTO_TEST_CASE(my_test){
	BOOST_CHECK(2 + 2 == 5);
}