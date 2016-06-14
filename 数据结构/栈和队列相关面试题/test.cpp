#define _CRT_SECURE_NO_WARNINGS 1
#include "StackAndQueue.h"

void Test1()
{
	//ʵ��һ��ջ��Ҫ��ʵ��Push����ջ����Pop����ջ����
	//Min��������Сֵ�Ĳ�������ʱ�临�Ӷ�ΪO(1)
	//˼·��������ջ��ÿ��ѹջ����DataStack֮ǰ������MinDataStack��ջ��Ԫ�ؽ���
	//�Ƚϣ������MinDataStack��ջ��Ԫ��С����ô���ݼ�����DataStackջ��Ҳ����MinDataStack��
	TwoStack<int> twostack;
	twostack.Push(1);
	twostack.Push(5);
	twostack.Push(9);
	twostack.Push(3);
	twostack.Push(2);
	twostack.Push(0);
	twostack.Push(6);
	cout<<twostack.MinData()<<endl;
	cout<<twostack.Top()<<endl;
	cout<<twostack.Size()<<endl;
	cout<<twostack.Empty()<<endl;

	twostack.Pop();
	twostack.Pop();
	twostack.Pop();
	cout<<twostack.MinData()<<endl;
	cout<<twostack.Top()<<endl;
	cout<<twostack.Size()<<endl;
	cout<<twostack.Empty()<<endl;
}

void Test2()
{
	//ʹ������ջʵ��һ������
	//˼·��������ջ��һ����InStackջ��ֻ������ջ��һ��OutStackջ��ֻ������ջ
	TwoStackForQueue<int> queue;
	queue.Push(1);
	queue.Push(2);
	queue.Push(3);
	queue.Push(4);
	queue.Push(5);
	queue.Push(6);
	cout<<queue<<endl;

	queue.Pop();
	queue.Pop();
	cout<<queue<<endl;

	cout<<queue.Front()<<endl;
	cout<<queue.Back()<<endl;
	cout<<queue.Empty()<<endl;
	cout<<queue.Size()<<endl;
}

void Test3()
{
	//ʹ����������ʵ��һ��ջ
	TwoQueueForStack<int> stack;
	stack.Push(6);
	stack.Push(8);
	stack.Push(0);
	stack.Push(5);
	stack.Push(9);
	stack.Push(1);

	stack.pop();
	stack.pop();
	stack.pop();
	stack.pop();
	stack.pop();

	cout<<stack.Top()<<endl;
	cout<<stack.Size()<<endl;
	cout<<stack.Empty()<<endl;
}

void Test4()
{
	//Ԫ����ջ����ջ˳��ĺϷ��ԣ�����ջ������Ϊ��1��2��3��4��5������ջ����Ϊ��4��5��3��2��1��
	LegalCheck<int> legalcheck;
	//int InArray[5] = {1,2,3,4,5};
	//int OutArray[5] = {4,5,3,2,1};//���1
	//int InArray[] = {1,2,3,4,5,6,7,8,9,10,11};
	//int OutArray[] = {2,5,6,9,8,10,7,4,3,11,1};//���1
	int InArray[] = {1,2,3,4,5,6,7,8,9,10,11};
	int OutArray[] = {2,5,6,9,8,11,7,4,3,10,1};//���0
	size_t size1 = sizeof(InArray)/sizeof(InArray[0]);
	size_t size2 = sizeof(OutArray)/sizeof(OutArray[0]);
	cout<<legalcheck.IsLegalCheck(InArray,OutArray,size1,size2)<<endl;
}


void Test5()
{
	//һ������ʵ������ջ
	ArrayForTwoStack<int> stack;
	stack.Push(1,1);
	stack.Push(1,2);
	stack.Push(1,3);
	stack.Push(1,4);
	stack.Push(1,5);
	cout<<stack.Top(1)<<endl;
	cout<<stack.Empty(1)<<endl;
	cout<<stack.Size(1)<<endl;

	stack.Pop(1);
	stack.Pop(1);
	cout<<stack.Top(1)<<endl;
	cout<<stack.Empty(1)<<endl;
	cout<<stack.Size(1)<<endl;

	stack.Push(2,6);
	stack.Push(2,7);
	stack.Push(2,8);
	stack.Push(2,9);
	stack.Push(2,10);
	cout<<stack.Top(2)<<endl;
	cout<<stack.Empty(2)<<endl;
	cout<<stack.Size(2)<<endl;

	stack.Pop(2);
	stack.Pop(2);
	cout<<stack.Top(2)<<endl;
	cout<<stack.Empty(2)<<endl;
	cout<<stack.Size(2)<<endl;
}


int main()
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	Test5();
	system("pause");
	return 0;
}

