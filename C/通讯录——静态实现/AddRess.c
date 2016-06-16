#define _CRT_SECURE_NO_WARNINGS 1
#include "AddRess.h"

void Print_AddRess()
{
	printf("**************************\n");//�����ʱ��Ҫ��֤��Ļ�ϸɾ�����
	printf("*****0.   �˳�ϵͳ   *****\n");//�ñ����ж���ȥ����Ȥ
	printf("*****1.�����ϵ����Ϣ*****\n");
	printf("*****2.ɾ����ϵ����Ϣ*****\n");
	printf("*****3.������ϵ����Ϣ*****\n");
	printf("*****4.�޸���ϵ����Ϣ*****\n");
	printf("*****5.��ʾ��ϵ����Ϣ*****\n");
	printf("*****6.���������ϵ��*****\n");
	printf("*****7.����������ϵ��*****\n");
	printf("**************************\n");
}

void Add_AddRess(pPeson peson)
{
	assert(peson);//����ָ���Ƿ���Ч

	if(peson->size < MAX)//�ж�peson->size�Ƿ�Ϸ�
	{
		//�򵥵��������
		printf("�����ϵ����Ϣ\n");//�������Ա����䡢�绰��סַ
		printf("��������ϵ��������\n");
		scanf("%s",&(peson->people[peson->size].name));
		printf("��������ϵ�˵��Ա�\n");
		scanf("%s",&(peson->people[peson->size].sex));
		printf("��������ϵ�˵����䣺\n");
		scanf("%d",&(peson->people[peson->size].age));	
		printf("��������ϵ�˵ĵ绰��\n");
		scanf("%s",&(peson->people[peson->size].tel));
		printf("��������ϵ�˵�סַ��\n");
		scanf("%s",&(peson->people[peson->size].address));

		peson->size++;//ÿ������һ����ϵ�ˣ���Ч��size��Ҫ+1
	}
	else
	{
		printf("ͨѶ¼����\n");//���peson->size >= MAX
	}

	//if(peson->size <= peson->capacity)//�ж�peson->size�Ƿ�Ϸ�
	//{
	//	//�򵥵��������
	//	printf("�����ϵ����Ϣ\n");//�������Ա����䡢�绰��סַ
	//	printf("��������ϵ��������\n");
	//	scanf("%s",&(peson->people[peson->size].name));
	//	printf("��������ϵ�˵��Ա�\n");
	//	scanf("%s",&(peson->people[peson->size].sex));
	//	printf("��������ϵ�˵����䣺\n");
	//	scanf("%d",&(peson->people[peson->size].age));	
	//	printf("��������ϵ�˵ĵ绰��\n");
	//	scanf("%s",&(peson->people[peson->size].tel));
	//	printf("��������ϵ�˵�סַ��\n");
	//	scanf("%s",&(peson->people[peson->size].address));

	//	peson->size++;//ÿ������һ����ϵ�ˣ���Ч��size��Ҫ+1
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
	assert(peson);//����ָ���Ƿ���Ч

	printf("%5s\t","name");//%Xs  �ķ�ʽʹ�ַ��������ұ߿�ʼ��ӡ����  X�����������ֵ�������ȡ��һ����С������
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
	assert(peson);//����ָ���Ƿ���Ч

	peson->size = 0;
}

void Del_AddRess(pPeson peson)
{
	char name[20] = {0};
	int i = 0;
	assert(peson);//����ָ���Ƿ���Ч
	if (peson->size == 0)
	{
		printf("ͨѶ¼�ѿ�\n");
	}

	printf("��������Ҫɾ����ϵ�˵�����");
	scanf("%s",&name);

	for (i = 0;i < peson->size; i++)
	{
		if (strcmp(name,peson->people[i].name) == 0)//�ж������������ͨѶ¼�������Ƿ�һ��
		{
			for (;i < peson->size;i++)
			{
				peson->people[i] = peson->people[i + 1];//����һ�µ����ֺ󣬴ӵ�ǰ�±�ĺ�һ���±��������Чֵ��ֵ��ǰһ��
			}                                           //���ǵ���Ҫɾ����ֵ��ע�����ﲻ�ܴ����һ����Чֵ��ʼ��ǰ��ֵ���ᶪʧ���ݵ�
			peson->size--;//ÿ��ɾ��һ�����ݣ���ЧsizeҪ����һ��
		} 
	}
	if (i == peson->size)
	{
		printf("�Բ����Ҳ�������Ҫɾ������ϵ��\n");
	}
}

void Seek_AddRess(pPeson peson)
{
	char name[20] = {0};
	int i = 0;
	assert(peson);//����ָ���Ƿ���Ч

	if (peson->size == 0)
	{
		printf("ͨѶ¼�ѿ�\n");
	}

	printf("��������Ҫ������ϵ�˵�����");
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
	assert(peson);//����ָ���Ƿ���Ч

	if (peson->size == 0)
	{
		printf("ͨѶ¼�ѿ�\n");
	}

	printf("��������Ҫ�޸ĵ���ϵ�˵�����");
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
			printf("��������Ҫ�޸ĵĶ�Ӧ��ţ�\n");
			scanf("%d",&num);

			switch (num)
			{
			case 1:
				printf("��������ϵ������\n");
				scanf("%s",&Char_Tmp);
				strcpy(peson->people[i].name,Char_Tmp);
				break;
			case 2:
				printf("��������ϵ���Ա�\n");
				scanf("%s",&Char_Tmp);
				strcpy(peson->people[i].sex,Char_Tmp);
				break;
			case 3:
				printf("��������ϵ������\n");
				scanf("%d",&Int_Tmp);
				peson->people[i].age = Int_Tmp;
				break;
			case 4:
				printf("��������ϵ�˵绰\n");
				scanf("%s",&Char_Tmp);
				strcpy(peson->people[i].tel,Char_Tmp);
				break;
			case 5:
				printf("��������ϵ��סַ\n");
				scanf("%s",&Char_Tmp);
				strcpy(peson->people[i].address,Char_Tmp);
				break;
			default:
				printf("�Բ����������\n");
				break;
			}
		} 
	}

}

void Sort_AddRess(pPeson peson)//ð������
{
	char name[20] = {0};
	int i = 0;
	int j = 0;
	PesonMessage tmp;
	assert(peson);//����ָ���Ƿ���Ч

	if (peson->size == 0)
	{
		printf("ͨѶ¼�ѿ�\n");
	}

	for (i = 0; i < peson->size-1; i++)//���������
	{
		for (j = 0;j < peson->size - i - 1;j++)//�Ƚϵĸ���
		{
			if (strcmp(peson->people[j].name,peson->people[j + 1].name) < 0)
			{
				//strcpy(tmp,peson->people[j].name);    //�տ�ʼǷȱ����ֻ�ǽ�����������������
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
		printf("��ѡ��\n");
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
			printf("��������\n");
			break;
		}
	}
}
