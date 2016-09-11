#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<stack>
#include<assert.h>

enum OP
{
	OP_NUM,
	OP_SYMBOL,
	ADD,
	SUB,
	MUL,
	DIV,
};
struct Cell
{
	int _symbol;
	int _value;
};
void test()
{
	//12 3 4 + * 6 - 8 2 / +
	Cell RPNArray[] = \
	{\
	{OP_NUM,12},\
	{OP_NUM,3},\
	{OP_NUM,4},\
	{OP_SYMBOL,ADD},\
	{OP_SYMBOL,MUL},\
	{OP_NUM,6},\
	{OP_SYMBOL,SUB},\
	{OP_NUM,8},\
	{OP_NUM,2},\
	{OP_SYMBOL,DIV},\
	{OP_SYMBOL,ADD},\
	};

	int size = sizeof(RPNArray)/sizeof(RPNArray[0]);
	stack<int> s;

	for(int i = 0;i < size;i++)
	{
		if(RPNArray[i]._symbol == OP_NUM)
		{
			s.push(RPNArray[i]._value);
		}
		else
		{
			int right = s.top();
			s.pop();
			int left = s.top();
			s.pop();

			switch(RPNArray[i]._value)
			{
			case ADD:
				{
					s.push(left + right);
				}
				break;
			case SUB:
				{
					s.push(left - right);
				}
				break;
			case MUL:
				{
					s.push(left * right);
				}
				break;
			case DIV:
				{
					s.push(left / right);
				}
				break;
			default:
				assert(false);
			}
		}
	}
	cout<<"½á¹û = "<<s.top()<<endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}