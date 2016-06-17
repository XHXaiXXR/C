#define _CRT_SECURE_NO_WARNINGS 1
#include "SListNode.h"

//����ε��Ƕ���ָ�룬��ΪҪ�Խṹ��ָ������ݽ����޸ģ����Ա��봫��ָ��ĵ�ַ����
//һ������ָ�룩��һ��ָ���൱��ֵ���ݣ������ʵ���иı�

void InitList(PSListNode* pHead)
{
	assert(pHead);
	pHead = NULL;
}

PSListNode ByeNode(DataType data)
{
	PSListNode pNewNode = (PSListNode)malloc(sizeof(struct SListNode));
	if (pNewNode != NULL)
	{
		pNewNode->data = data;
		pNewNode->_NextNode = NULL;//һ��Ҫ�ǵð��¿��ٽ�����һ����㸳ֵΪ��
	} 
	else
	{
		printf("�����ڴ�ʧ��\n");
	}

	return pNewNode;
}

void PrintList(PSListNode* pHead)
{
	PSListNode pNode = NULL;
	assert(pHead);
	if (*pHead == NULL)
	{
		return;
	} 
	else
	{
		pNode = *pHead;

		while (NULL != pNode)//���д��while(NULL != pNode)
		{
			printf("%d ",pNode->data);
			pNode = pNode->_NextNode;
		}
		printf("\n");
	}
}

void PushBack(PSListNode* pHead, DataType data)
{
	PSListNode pNode = NULL;
	PSListNode pNewNode = NULL;
	assert(pHead);
	if (*pHead == NULL)
	{
		*pHead = ByeNode(data);
	} 
	else
	{
		pNode = *pHead;

		//�ҵ�β���
		while (NULL != pNode->_NextNode)
		{
			//����β���
			pNode = pNode->_NextNode;
		}

		pNewNode = ByeNode(data);
		pNode->_NextNode = pNewNode;
		pNewNode->_NextNode = NULL;
	}
}

void PopBack(PSListNode* pHead)
{
	PSListNode pNode1 = NULL;   
	PSListNode pNode2 = NULL;
	assert(pHead);
    pNode1 = *pHead;

	if (*pHead == NULL)
	{
		printf("SListNode is emtpy\n");
		return;
	} 
	else if (pNode1->_NextNode == NULL) //��ֻʣ��һ���ڵ������£�Ҫ��������ͷָ��
	{
		*pHead = NULL;
		free(pNode1);
		pNode1 = NULL;
	}
	else
	{
		while (pNode1->_NextNode != NULL)
		{
			pNode2 = pNode1;//��һ��ָ��׷�ٵ�ǰָ�룬һ���¼��ǰλ��
			pNode1 = pNode1->_NextNode;
		}

		pNode2->_NextNode = NULL;//��֤�������һ���ڵ�ĵ�_NextNodeΪ��

		free(pNode1);//��malloc����ʹ��   �ͷ����һ���ڵ�
		pNode1 = NULL;//���ͷŵ��Ľ�㸳ֵΪ�գ��Է���ɿ�ָ��
	}
}

void PushFront(PSListNode* pHead, DataType data)
{
	PSListNode pNode = NULL;
	assert(pHead);

	if (*pHead == NULL)
	{
		*pHead = ByeNode(data);
		(*pHead)->_NextNode = NULL;
	} 
	else
	{
		pNode = ByeNode(data);
		pNode->_NextNode = *pHead;
		*pHead = pNode;
	}
}

void PopFront(PSListNode* pHead)
{
	PSListNode pNode = NULL;
	assert(pHead);

	
	if (NULL == *pHead)
	{
		printf("SListNode is empty\n");
	} 
	else if ((*pHead)->_NextNode == NULL)
	{
		pNode = *pHead;
		*pHead = NULL;
		free(pNode);
		pNode = NULL;
	}
	else
	{
		pNode = *pHead;
		*pHead = (*pHead)->_NextNode;
		free(pNode);
		pNode = NULL;
	}
}

PSListNode Find(PSListNode* pHead, DataType data)
{
	PSListNode pNode = NULL;
	assert(pHead);

	pNode = *pHead;
	while (NULL != pNode)
	{
		if (pNode->data == data)
		{
			return pNode;
		} 
		else
		{
			pNode = pNode->_NextNode;
		}
	}

	return NULL;
}

void Erase(PSListNode* pHead, PSListNode pos)
{
	PSListNode pNode = NULL;
	PSListNode pNode2 = NULL;
	assert(pHead);
	assert(pos);

	pNode = *pHead;

	while (NULL != pNode)
	{
		if (pNode->_NextNode == pos )
		{
			pNode2 = pNode->_NextNode;
			pNode->_NextNode = pNode->_NextNode->_NextNode;
			free(pNode2);
			pNode2 = NULL;
		} 
		else if(pNode == pos)
		{
			*pHead = (*pHead)->_NextNode;
			free(pNode);
			pNode = NULL;
		}
		else
		{
			pNode = pNode->_NextNode;
		}
	}
}

void Insert(PSListNode* pHead, PSListNode pos, DataType data)
{
	PSListNode pNode = NULL;
	PSListNode pNewNode = NULL;
	assert(pHead);
	assert(pos);

	pNode = *pHead;

	while (NULL != pNode)
	{
		if (pNode->_NextNode == pos)
		{
			pNewNode = ByeNode(data);
			pNewNode->_NextNode = pNode->_NextNode;
			pNode->_NextNode = pNewNode;
			break;
		} 
		else if(pNode == pos)
		{
			pNewNode = ByeNode(data);
			pNewNode->_NextNode = *pHead;
			*pHead = pNewNode;
			break;
		}
		else
		{
			pNode = pNode->_NextNode;
		}
	}
}

void DestroyList(PSListNode* pHead)
{
	PSListNode pNode = NULL;
	PSListNode pNode2 = NULL;
	assert(pHead);

	pNode = *pHead;

	while (NULL != pNode)
	{
		pNode2 = pNode;
		pNode = pNode->_NextNode;
		free(pNode2);
		pNode2 = NULL;
	}
	*pHead = NULL;
}

void BubblingSort(PSListNode* pHead)
{
	PSListNode cur = NULL;
	PSListNode prev = NULL;
	DataType tmp = 0;
	assert(pHead);

	cur = *pHead;

	while (cur != prev)
	{
		while (cur->_NextNode != prev)
		{
			if (cur->data > cur->_NextNode->data)
			{
				tmp = cur->data;
				cur->data = cur->_NextNode->data;
				cur->_NextNode->data = tmp;
			}
			cur = cur->_NextNode;
		}
		prev = cur;
		cur = *pHead;
	}
}

void EraseNotHead(PSListNode pos)
{
	PSListNode Del = NULL;
	assert(pos->_NextNode != NULL);
	if (pos == NULL)
	{
		return;
	}

	pos->data = pos->_NextNode->data;

	Del = pos->_NextNode;
	pos->_NextNode = pos->_NextNode->_NextNode;
	free(Del);
	Del = NULL;
}


void ReverseLish(PSListNode* pHead)
{
	PSListNode cur = NULL;
	PSListNode NewpHead = NULL;
	assert(pHead);

	while((*pHead)->_NextNode != NULL)
	{
		NewpHead = *pHead;
		*pHead = (*pHead)->_NextNode;
		NewpHead->_NextNode = cur;
		cur = NewpHead;
	}

	(*pHead)->_NextNode = NewpHead;
}

void InsertFrontNode(PSListNode pos,DataType data)
{
	DataType tmp = 0;
	PSListNode pNewNode = NULL;
	if (pos == NULL)
	{
		return;
	}
	pNewNode = ByeNode(data);

	tmp = pNewNode->data;
	pNewNode->data = pos->data;
	pos->data = tmp;

	pNewNode->_NextNode = pos->_NextNode;
	pos->_NextNode = pNewNode;
}


PSListNode FindMidNode(PSListNode* pHead)
{
	PSListNode cur = NULL;
	PSListNode prev = NULL;
	PSListNode pNode = NULL;
	assert(pHead);

	pNode = *pHead;
	cur = pNode;
	prev = pNode;

	while (prev->_NextNode != NULL && prev->_NextNode->_NextNode != NULL)
	{
		cur = pNode->_NextNode;
		prev = pNode->_NextNode->_NextNode;
		pNode = pNode->_NextNode;
	}

	return cur;
}

void DelKNode(PSListNode* pHead,int k)
{
	PSListNode cur = NULL;
	PSListNode prev = NULL;
	PSListNode pNode = NULL;
	PSListNode Del = NULL;
	assert(pHead);
	assert(k > 1);
	pNode = *pHead;
	cur = pNode;
	prev = pNode;

	while (k--)//ʹprevָ����Ҫɾ������ǰһ�����
	{
		cur = cur->_NextNode;
	}
	while (cur->_NextNode != NULL)
	{
		cur = cur->_NextNode;
		prev = prev->_NextNode;
	}

	Del = prev->_NextNode;
	prev->_NextNode = prev->_NextNode->_NextNode;
	free(Del);
	Del = NULL;
}