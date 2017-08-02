#include<iostream>
#include<gtest/gtest.h>
using namespace std;

//int Abs(int x)
//{
//	return x > 0 ? x : -x;
//}
//
//TEST(TestCaseAbs, Positive)
//{
//	ASSERT_EQ(Abs(3), 3);
//}

//bool fun1()
//{
//	cout<<"hello1"<<endl;
//	return true;
//}
//bool fun2()
//{
//	cout<<"hello2"<<endl;
//	return true;
//}
//bool fun3()
//{
//	cout<<"hello3"<<endl;
//	return true;
//}
//bool fun4()
//{
//	cout<<"hello4"<<endl;
//	return true;
//}
//
//TEST(TestCaseFun, fun1)
//{
//	ASSERT_TRUE(fun1());	
//}
//
//TEST(TestCaseFun, fun2)
//{
//	ASSERT_TRUE(fun2());	
//}
//
//TEST(TestCaseFun, fun3)
//{
//	ASSERT_TRUE(fun3());	
//}
//
//TEST(TestCaseFunP, fun4)
//{
//	//ASSERT_TRUE(fun4());	
//	//ASSERT_FALSE(fun4());	
//	EXPECT_FALSE(fun4()) << fun4() << endl;	
//	cout<<"无论失败与否都输出这句话"<<endl;
//}

bool fun()
{
	cout<<"hello"<<endl;
	return true;
}

TEST(TeseCaseFun, fun)
{
	ASSERT_TRUE(fun());
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
