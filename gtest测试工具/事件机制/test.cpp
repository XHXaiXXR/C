#include<iostream>
using namespace std;

#include<gtest/gtest.h>
#include<map>

class FooTest : public testing::Test
{
public:
	virtual void SetUp()
	{
		cout<<"FooEnvironment::SetUp()"<<endl;
	}
	virtual void TearDown()
	{
		cout<<"FooEnvironment::TearDown()"<<endl;
	}
};

TEST(FooTest, mapfind1)
{
	map<int, int> m;
	m.insert(pair<int, int>(1,1));
	m.insert(pair<int, int>(2,2));
	m.insert(pair<int, int>(3,3));
	m.insert(pair<int, int>(4,4));
	m.insert(pair<int, int>(5,5));
	
	ASSERT_NE(m.find(3), m.end());
}
TEST(FooTest, mapfind2)
{
	map<int, int> m;
	m.insert(pair<int, int>(1,1));
	m.insert(pair<int, int>(2,2));
	m.insert(pair<int, int>(3,3));
	m.insert(pair<int, int>(4,4));
	m.insert(pair<int, int>(5,5));
	
	ASSERT_NE(m.find(3), m.end());
}
TEST(FooTest, mapfind3)
{
	map<int, int> m;
	m.insert(pair<int, int>(1,1));
	m.insert(pair<int, int>(2,2));
	m.insert(pair<int, int>(3,3));
	m.insert(pair<int, int>(4,4));
	m.insert(pair<int, int>(5,5));
	
	ASSERT_NE(m.find(3), m.end());
}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

//class FooTest : public testing::Test
//{
//public:
//	static void SetUpTestCase()
//	{
//		cout<<"FooTest::SetUpTestCase()"<<endl;
//	}
//	static void TearDownTestCase()
//	{
//		cout<<"FooTesr::TearDownTestCase()"<<endl;
//	}
//};
//
//TEST_F(FooTest, find1)
//{
//}
//TEST_F(FooTest, find2)
//{
//
//}
//TEST_F(FooTest, find3)
//{
//
//}
//
//int main(int argc, char* argv[])
//{
//	testing::InitGoogleTest(&argc, argv);
//	return RUN_ALL_TESTS();
//}

////第一种事件机制：全局的开始和结束
////必须要继承Environment类
//class FooEnvironment : public testing::Environment
//{
//public:
//	//SetUP()和TearDown()是Environment类中的两个虚函数
//	//SetUP函数在所有案例执行之前
//	virtual void SetUp()
//	{
//		cout<<"FooEnvironment::Setup()"<<endl;
//	}
//	//TearDown函数在所有案例执行之后
//	virtual void TearDown()
//	{
//		cout<<"FooEnvironment::TearDown()"<<endl;
//	}
//};
//
//TEST(FooEnvironment, mapfind1)
//{
//	map<int, int> m;
//	m.insert(pair<int, int>(1,1));
//	m.insert(pair<int, int>(2,2));
//	m.insert(pair<int, int>(3,3));
//	m.insert(pair<int, int>(4,4));
//	m.insert(pair<int, int>(5,5));
//	
//	ASSERT_NE(m.find(3), m.end());
//}
//
//TEST(FooEnvironment, mapfind3)
//{
//	map<int, int> m;
//	m.insert(pair<int, int>(1,1));
//	m.insert(pair<int, int>(2,2));
//	m.insert(pair<int, int>(3,3));
//	m.insert(pair<int, int>(4,4));
//	m.insert(pair<int, int>(5,5));
//	
//	ASSERT_NE(m.find(5), m.end());
//}
//
//TEST(FooEnvironment, mapfind2)
//{
//	map<int, int> m;
//	m.insert(pair<int, int>(1,1));
//	m.insert(pair<int, int>(2,2));
//	m.insert(pair<int, int>(3,3));
//	m.insert(pair<int, int>(4,4));
//	m.insert(pair<int, int>(5,5));
//	
//	ASSERT_NE(m.find(2), m.end());
//}
//int main(int argc, char* argv[])
//{
//	testing::InitGoogleTest(&argc, argv);//初始化
//	
//	testing::AddGlobalTestEnvironment(new FooEnvironment);//将这个全局的对象添加进去，让框架知道他的存在
//
//	return RUN_ALL_TESTS();//执行所有的测试用例
//}













