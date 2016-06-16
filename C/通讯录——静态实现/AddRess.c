#define _CRT_SECURE_NO_WARNINGS 1
#include "AddRess.h"

void Print_AddRess()
{
	printf("**************************\n");//输出的时候要保证屏幕上干净整齐
	printf("*****0.   退出系统   *****\n");//让别人有读下去的兴趣
	printf("*****1.添加联系人信息*****\n");
	printf("*****2.删除联系人信息*****\n");
	printf("*****3.查找联系人信息*****\n");
	printf("*****4.修改联系人信息*****\n");
	printf("*****5.显示联系人信息*****\n");
	printf("*****6.清空所有联系人*****\n");
	printf("*****7.名字排序联系人*****\n");
	printf("**************************\n");
}

void Add_AddRess(pPeson peson)
{
	assert(peson);//断言指针是否有效

	if(peson->size < MAX)//判断peson->size是否合法
	{
		//简单的输入输出
		printf("添加联系人信息\n");//姓名、性别、年龄、电话、住址
		printf("请输入联系人姓名：\n");
		scanf("%s",&(peson->people[peson->size].name));
		printf("请输入联系人的性别：\n");
		scanf("%s",&(peson->people[peson->size].sex));
		printf("请输入联系人的年龄：\n");
		scanf("%d",&(peson->people[peson->size].age));	
		printf("请输入联系人的电话：\n");
		scanf("%s",&(peson->people[peson->size].tel));
		printf("请输入联系人的住址：\n");
		scanf("%s",&(peson->people[peson->size].address));

		peson->size++;//每次增加一个联系人，有效的size都要+1
	}
	else
	{
		printf("通讯录已满\n");//如果peson->size >= MAX
	}

	//if(peson->size <= peson->capacity)//判断peson->size是否合法
	//{
	//	//简单的输入输出
	//	printf("添加联系人信息\n");//姓名、性别、年龄、电话、住址
	//	printf("请输入联系人姓名：\n");
	//	scanf("%s",&(peson->people[peson->size].name));
	//	printf("请输入联系人的性别：\n");
	//	scanf("%s",&(peson->people[peson->size].sex));
	//	printf("请输入联系人的年龄：\n");
	//	scanf("%d",&(peson->people[peson->size].age));	
	//	printf("请输入联系人的电话：\n");
	//	scanf("%s",&(peson->people[peson->size].tel));
	//	printf("请输入联系人的住址：\n");
	//	scanf("%s",&(peson->people[peson->size].address));

	//	peson->size++;//每次增加一个联系人，有效的size都要+1
	//}
	//else
	//{
	//	PesonMessage *tmp = (PesonMessage* )realloc(peson->people,(peson->capacity+3)*sizeof(PesonMessage));
	//	if (tmp == NULL)
	//	{
	//		printf("out of memory\n");
	//	} 
	//	else
	//	{
	//		peson->people = tmp;
	//	}
	//}
}

void Show_AddRess(pPeson peson)
{
	int i = 0;
	assert(peson);//断言指针是否有效

	printf("%5s\t","name");//%Xs  的方式使字符串从最右边开始打印对齐  X可是是随意的值，这里的取了一个较小的数字
	printf("%5s\t","sex");
	printf("%5s\t","age");
	printf("%5s\t","tel");
	printf("%5s\t","address");
	printf("\n");

	for (i = 0;i <peson->size;i++)
	{
		printf("%5s\t",peson->people[i].name);
		printf("%5s\t",peson->people[i].sex);
		printf("%5d\t",peson->people[i].age);
		printf("%5s\t",peson->people[i].tel);
		printf("%5s\t",peson->people[i].address);
		printf("\n");
	}
}

void Empty_AddRess(pPeson peson)
{
	assert(peson);//断言指针是否有效

	peson->size = 0;
}

void Del_AddRess(pPeson peson)
{
	char name[20] = {0};
	int i = 0;
	assert(peson);//断言指针是否有效
	if (peson->size == 0)
	{
		printf("通讯录已空\n");
	}

	printf("请输入需要删除联系人的姓名");
	scanf("%s",&name);

	for (i = 0;i < peson->size; i++)
	{
		if (strcmp(name,peson->people[i].name) == 0)//判断输入的姓名和通讯录的姓名是否一致
		{
			for (;i < peson->size;i++)
			{
				peson->people[i] = peson->people[i + 1];//发现一致的名字后，从当前下标的后一个下标的所有有效值赋值给前一个
			}                                           //覆盖掉需要删除的值，注意这里不能从最后一个有效值开始往前赋值，会丢失数据的
			peson->size--;//每次删除一个数据，有效size要减掉一个
		} 
	}
	if (i == peson->size)
	{
		printf("对不起，找不到您所要删除的联系人\n");
	}
}

void Seek_AddRess(pPeson peson)
{
	char name[20] = {0};
	int i = 0;
	assert(peson);//断言指针是否有效

	if (peson->size == 0)
	{
		printf("通讯录已空\n");
	}

	printf("请输入需要查找联系人的姓名");
	scanf("%s",&name);

	for (i = 0;i < peson->size; i++)
	{
		if (strcmp(name,peson->people[i].name) == 0)
		{
			printf("%5s\t","name");
			printf("%5s\t","sex");
			printf("%5s\t","age");
			printf("%5s\t","tel");
			printf("%5s\t","address");
			printf("\n");

			printf("%5s\t",peson->people[i].name);
			printf("%5s\t",peson->people[i].sex);
			printf("%5d\t",peson->people[i].age);
			printf("%5s\t",peson->people[i].tel);
			printf("%5s\t",peson->people[i].address);
			printf("\n");
		} 
	}
}

void Revise_AddRess(pPeson peson)
{
	char name[20] = {0};
	char Char_Tmp[20] = {0};
	int Int_Tmp = 0;
	int i = 0;
	int num = 0;
	assert(peson);//断言指针是否有效

	if (peson->size == 0)
	{
		printf("通讯录已空\n");
	}

	printf("请输入需要修改的联系人的姓名");
	scanf("%s",&name);

	for (i = 0;i < peson->size; i++)
	{
		if (strcmp(name,peson->people[i].name) == 0)
		{
			printf("1.name\n");
			printf("2.sex\n");
			printf("3.age\n");
			printf("4.tel\n");
			printf("5.address\n");
			printf("请输入需要修改的对应序号：\n");
			scanf("%d",&num);

			switch (num)
			{
			case 1:
				printf("请输入联系人姓名\n");
				scanf("%s",&Char_Tmp);
				strcpy(peson->people[i].name,Char_Tmp);
				break;
			case 2:
				printf("请输入联系人性别\n");
				scanf("%s",&Char_Tmp);
				strcpy(peson->people[i].sex,Char_Tmp);
				break;
			case 3:
				printf("请输入联系人年龄\n");
				scanf("%d",&Int_Tmp);
				peson->people[i].age = Int_Tmp;
				break;
			case 4:
				printf("请输入联系人电话\n");
				scanf("%s",&Char_Tmp);
				strcpy(peson->people[i].tel,Char_Tmp);
				break;
			case 5:
				printf("请输入联系人住址\n");
				scanf("%s",&Char_Tmp);
				strcpy(peson->people[i].address,Char_Tmp);
				break;
			default:
				printf("对不起，输入错误\n");
				break;
			}
		} 
	}

}

void Sort_AddRess(pPeson peson)//冒泡排序
{
	char name[20] = {0};
	int i = 0;
	int j = 0;
	PesonMessage tmp;
	assert(peson);//断言指针是否有效

	if (peson->size == 0)
	{
		printf("通讯录已空\n");
	}

	for (i = 0; i < peson->size-1; i++)//排序的趟数
	{
		for (j = 0;j < peson->size - i - 1;j++)//比较的个数
		{
			if (strcmp(peson->people[j].name,peson->people[j + 1].name) < 0)
			{
				//strcpy(tmp,peson->people[j].name);    //刚开始欠缺考虑只是交换了两组姓名而已
				//strcpy(peson->people[j].name,peson->people[j + 1].name);
				//strcpy(peson->people[j + 1].name,tmp);
				tmp = peson->people[j];
				peson->people[j] = peson->people[j+1];
				peson->people[j+1] = tmp;
			}
		}
	}
}

void Cheak(pPeson peson)
{
	int index = 0;

	while(1)
	{
		Print_AddRess();
		printf("请选择：\n");
		scanf("%d",&index);

		switch(index)
		{
		case EXIT:
			exit(0);
			break;
		case ADD:
			Add_AddRess(peson);
			break;
		case DEL:
			Del_AddRess(peson);
			break;
		case SEEK:
			Seek_AddRess(peson);
			break;
		case REVISE:
			Revise_AddRess(peson);
			break;
		case SHOW:
			Show_AddRess(peson);
			break;
		case EMPTY:
			Empty_AddRess(peson);
			break;
		case SORT:
			Sort_AddRess(peson);
			break;
		default:
			printf("输入有误\n");
			break;
		}
	}
}
