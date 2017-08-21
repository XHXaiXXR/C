#include<iostream>
#include<gtest/gtest.h>
using namespace std;

bool Integer(int num)
{
	if(num >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

class IsInteger : public testing::TestWithParam<int>
{};

TEST_P(IsInteger, test)
{
	int n = GetParam(); 
	ASSERT_TRUE(Integer(n));	
}

INSTANTIATE_TEST_CASE_P(TrueReturn, IsInteger, testing::Range(1,5));

