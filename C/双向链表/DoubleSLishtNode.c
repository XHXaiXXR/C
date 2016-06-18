#define _CRT_SECURE_NO_WARNINGS 1
#include "DoubleSLishtNode.h"

void InitDSList(PDoubleSListNode* pHead)
{
	assert(pHead);
	pHead = NULL;
}

PDoubleSListNode ByeNode(DataType data)
{
	PDoubleSListNode pNewNode = (PDoubleSListNode)malloc(sizeof(struct DoubleSListNode));

	if (pNewNode == NULL)
	{
		printf("开辟结点失败\n");
	} 
	else
	{
		pNewNode->data = data;
		pNewNode->_LeftNode = NULL;
		pNewNode->_RightNode = NULL;
	}

	return pNewNode;
}

void PrintfDSList(PDoubleSListNode* pHead)
{
	PDoubleSListNode pNode = NULL;
	assert(pHead);

	if (*pHead == NULL)
	{
		return;
	}

	pNode = *pHead;

	while (NULL !=pNode)
	{
		printf("%d ",pNode->data);
		pNode = pNode->_RightNode;
	}
	printf("\n");
}

void PushBack(PDoubleSListNode* pHead,DataType data)
{
	PDoubleSListNode pNode = NULL;
	PDoubleSListNode pNewNode = NULL;
	assert(pHead);
	if (*pHead == NULL)
	{
		*pHead = ByeNode(data);
	} 
	else
	{
		pNode = *pHead;

		while (NULL !=pNode->_RightNode)
		{
			pNode = pNode->_RightNode;
		}

		pNewNode = ByeNode(data);
		pNewNode->_RightNode = NULL;
		pNewNode->_LeftNode = pNode;
		pNode->_RightNode = pNewNode;
	}
}

void PopBack(PDoubleSListNode* pHead)
{
	PDoubleSListNode pPurNode = NULL;
	PDoubleSListNode pCurNode = NULL;
	assert(pHead);

	if (*pHead == NULL)
	{
		printf("DoubleSListNode is empty\n");
		return;
	} 
	else if ((*pHead)->_RightNode == NULL)
	{
		pPurNode = *pHead;
		free(pPurNode);
		pPurNode = NULL;
		*pHead = NULL;
	}
	else
	{
		pPurNode = *pHead;
		while (NULL != pPurNode->_RightNode)
		{
			pPurNode = pPurNode->_RightNode;
		}

		pCurNode = pPurNode;
		pPurNode->_LeftNode->_RightNode = NULL;
		free(pCurNode);
		pCurNode = NULL;
	}
}

void PushFront(PDoubleSListNode* pHead,DataType data)
{
	PDoubleSListNode pNewNode = NULL;
	assert(pHead);

	if (*pHead == NULL)
	{
		*pHead = ByeNode(data);
	}
	else
	{
		pNewNode = ByeNode(data);
		pNewNode->_RightNode = (*pHead);
		pNewNode->_LeftNode = NULL;
		*pHead = pNewNode;
	}
}


void PopFront(PDoubleSListNode* pHead)
{
	PDoubleSListNode pNode = NULL;
	assert(pHead);
	if (*pHead == NULL)
	{
		printf("DoubleSListNode is emtpy\n");
		return;
	}

	//if ((*pHead)->_RightNode = NULL)
	//{
	//	pNode = *pHead;
	//	free(pNode);
	//	pNode = NULL;
	//	*pHead = NULL;
	//} 
	else
	{
		if (NULL != (*pHead)->_RightNode)
		{
			pNode = *pHead;
			*pHead = (*pHead)->_RightNode;
			free(pNode);
			pNode = NULL;
		} 
		else
		{
			//pNode = *pHead;
			//free(pNode);
			//pNode = NULL;
			//*pHead = NULL;
			free(*pHead);
			*pHead = NULL;
		}
	}
}

PDoubleSListNode Find(PDoubleSListNode* pHead,DataType x)
{
	PDoubleSListNode pNode = NULL;
	assert(pHead);
	if (*pHead == NULL)
	{
		printf("PDoubleSListNode is empty\n");
		return *pHead;
	}

	pNode = *pHead;
	while (NULL !=pNode)
	{
		if (pNode->data == x)
		{
			return pNode;
		} 
		else
		{
			pNode = pNode->_RightNode;
		}
	}

	return NULL;
}

void Erase(PDoubleSListNode* pHead,PDoubleSListNode pos)
{
	PDoubleSListNode pNode = NULL;
	assert(pHead);

	if (pos == NULL)
	{
		printf("Erase is error\n");
		return;
	} 
	else
	{
		if (pos == *pHead)
		{
			//pNode = pos;
			//pos = pos->_RightNode;
			//free(pNode);
			//pNode = NULL;
			pNode = *pHead;
			*pHead = (*pHead)->_RightNode;
			free(pNode);
			pNode = NULL;
		} 
		else
		{
			pNode = pos;
			pos->_LeftNode->_RightNode = pos->_RightNode;
			free(pNode);
			pNode = NULL;
		}
	}
}


//还没屡清楚，等我弄明白了后面再补上
//void Insert(PDoubleSListNode* pHead,PDoubleSListNode pos,DataType x)
//{
//	PDoubleSListNode pNode = NULL;
//	PDoubleSListNode pNewNode = NULL;
//	assert(pHead);
//
//	if (pos == NULL)
//	{
//		printf("no find x\n");
//		return;
//	} 
//
//	pNode = *pHead;
//	while (NULL != pNode)
//	{
//		if (pNode == pos)
//		{
//			pNewNode = ByeNode(x);
//			if (pos->_RightNode == NULL)
//			{
//				PushBack(pHead,x);
//			} 
//			else
//			{
//				pNewNode->_RightNode = pos->_RightNode;
//				pos->_RightNode->_LeftNode = pNewNode;
//				pos->_RightNode = pNewNode;
//				pNewNode->_LeftNode = pos;
//			}
//		} 
//		else
//		{
//			pNode = pNode->_RightNode;
//		}
//	}
//}