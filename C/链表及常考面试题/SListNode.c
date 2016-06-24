#define _CRT_SECURE_NO_WARNINGS 1
#include "SListNode.h"

//这里参的是二级指针，因为要对结构体指针的内容进行修改，所以必须传该指针的地址（即
//一个二级指针），一级指针相当于值传递，不会对实参有改变

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
		pNewNode->_NextNode = NULL;//一定要记得把新开辟结点的下一个结点赋值为空
	} 
	else
	{
		printf("开辟内存失败\n");
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

		while (NULL != pNode)//最好写成while(NULL != pNode)
		{
			printf("%d->",pNode->data);
			pNode = pNode->_NextNode;
		}
		printf("NULL");
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

		//找到尾结点
		while (NULL != pNode->_NextNode)
		{
			//保存尾结点
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
	else if (pNode1->_NextNode == NULL) //当只剩下一个节点的情况下，要单独处理头指针
	{
		*pHead = NULL;
		free(pNode1);
		pNode1 = NULL;
	}
	else
	{
		while (pNode1->_NextNode != NULL)
		{
			pNode2 = pNode1;//用一个指针追踪当前指针，一遍记录当前位置
			pNode1 = pNode1->_NextNode;
		}

		pNode2->_NextNode = NULL;//保证链表最后一个节点的的_NextNode为空

		free(pNode1);//和malloc配套使用   释放最后一个节点
		pNode1 = NULL;//将释放掉的结点赋值为空，以防变成空指针
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

	while (k--)//使prev指向需要删除结点的前一个结点
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

PSListNode MergeSList(PSListNode* pHead1,PSListNode* pHead2)
{
	PSListNode pNode1 = *pHead1;
	PSListNode pNode2 = *pHead2;
	PSListNode pNewNode = NULL;
	PSListNode ptmp = NULL;
	
	if (pNode1->data < pNode2->data)
	{
		pNewNode = pNode1;
		ptmp = pNode1;
		pNode1 = pNode1->_NextNode;
	}
	else
	{
		pNewNode = pNode2;
		ptmp = pNode2;
		pNode2 = pNode2->_NextNode;
	}

	while (pNode1 && pNode2)
	{
		if (pNode1->data < pNode2->data)
		{
			ptmp->_NextNode = pNode1;
			pNode1 = pNode1->_NextNode;
			ptmp = ptmp->_NextNode;
		} 
		else//pNode1->data > pNode2->data
		{
			ptmp->_NextNode = pNode2;
			pNode2 = pNode2->_NextNode;
			ptmp = ptmp->_NextNode;
		}
	}

	if (pNode1)
	{
		ptmp->_NextNode = pNode1;
	}
	if (pNode2)
	{
		ptmp->_NextNode = pNode2;
	}

	return pNewNode;
}


PSListNode JosephCycle(PSListNode* pHead,int num)
{
	PSListNode pNode = *pHead;
	PSListNode del = NULL;
	int k = 0;
	while (pNode->_NextNode != pNode)
	{
		k = num;
		while (--k)
		{
			pNode = pNode->_NextNode;
		}

		printf("del:%d\n",pNode->data);
		pNode->data = pNode->_NextNode->data;
		del = pNode->_NextNode;
		pNode->_NextNode = pNode->_NextNode->_NextNode;
		free(del);
		del = NULL;
	}
	return pNode;
}

PSListNode CheckCycle(PSListNode* pHead)
{
	PSListNode _slow = *pHead;
	PSListNode _fast = *pHead;

	while(_fast && _fast->_NextNode)
	{
		_slow = _slow->_NextNode;
		_fast = _fast->_NextNode->_NextNode;

		if (_slow == _fast)
		{
			return _fast;
		}
	}
	return NULL;
}

int GetCircleLength(PSListNode meet)
{
	PSListNode pNode = NULL;
	int count = 0;
	assert(meet);
	pNode = meet;

	do 
	{
		count++;
		pNode = pNode->_NextNode;
	} while (pNode != meet);

	return count;
}

PSListNode GetCycleEntryNode(PSListNode* pHead,PSListNode* meet)
{
	PSListNode start = *pHead;
	PSListNode meetNode = *meet;

	while (start != meetNode)
	{
		start = start->_NextNode;
		meetNode = meetNode->_NextNode;
	}

	return meetNode;
}

int CheckCross(PSListNode* slist1,PSListNode* slist2)
{
	PSListNode pNode1 = *slist1;
	PSListNode pNode2 = *slist2;
	if (pNode1 == NULL || pNode2 == NULL)
	{
		return -1;
	}
	else
	{
		while (pNode1->_NextNode)
		{
			pNode1 = pNode1->_NextNode;
		}
		while (pNode2->_NextNode)
		{
			pNode2 = pNode2->_NextNode;
		}

		if (pNode1 == pNode2)
		{
			return 1;
		}
		return -1;
	}
}