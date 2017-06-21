#pragma once

#include <iostream>
using namespace std;

//��������hash��Ľڵ�����
template<class K, class T>
struct CacheNode
{
	K _key;
	T _data;
	struct CacheNode<K, T>* _hashlistprev;//ָ��hash����ڵ��ǰһ���ڵ�ָ��
	struct CacheNode<K, T>* _hashlistnext;//ָ��hash����ڵ�ĺ�һ���ڵ��ָ��
	struct CacheNode<K, T>* _lrulistprev;//ָ��˫������ڵ��ǰһ���ڵ��ָ��
	struct CacheNode<K, T>* _lrulistnext;//ָ��˫������ڵ�ĺ�һ���ڵ��ָ��

	CacheNode(K key = K(), T data = T())
		:_key(key)
		,_data(data)
		,_hashlistprev(NULL)
		,_hashlistnext(NULL)
		,_lrulistprev(NULL)
		,_lrulistnext(NULL)
	{}
};

template<class K>
struct IsEqual
{
	//����keyֵ�ıȽϷ�ʽ
	bool operator()(const K& left, const K& right)
	{
		if(left == right)
			return true;
		else
			return false;
	}
};

template<class K, class T, class Compare = IsEqual<K>>
class LRUCache
{
	typedef CacheNode<K, T> Node;
public:
	LRUCache(size_t capacity = 10)
		:_capacity(capacity)
		,_hashmap(new Node*[capacity])
		,_lrulisthead(NULL)
		,_lrulisttail(NULL)
		,_size(0)
	{
		memset(_hashmap, 0, sizeof(Node*) * capacity);
	}
	~LRUCache()
	{
		_DeleteList(_lrulisthead);
		delete[] _hashmap;

		_capacity = 0;
		_hashmap = NULL;
		_lrulisthead = NULL;
		_lrulisttail = NULL;
		_size = 0;
	}
public:
	//�򻺴��з�������
	void LRUCacheSet(K key, T data)
	{
		Node* cur = _GetValFromHashMap(key);  
		if (NULL == cur)//hashmap�в�û��������浥Ԫ����Ҫ�´���һ�����浥Ԫ
		{
			cur = new Node(key, data);//������ڵ����һ��ռ�
			_InserteValToHashMap(cur);//������ڵ����hashmap��
			
			Node* lastNode = _InserteValToListHead(cur);//������ڵ���������ͷ��
			if (NULL != lastNode)//ֻ��˫���������Ƴ��ˣ���hashmap����Ȼ����
			{
				_RemoveFromHashMap(lastNode);//��hashmap���Ƴ������Ԫ
				delete lastNode;
			}
		} 
		else //cur != NULL
		{
			_UpdateLRUList(cur);
		}
	}
	//�ӻ����еõ�����
	bool LRUCacheGet(K key, T& data)
	{
		Node* cur = _GetValFromHashMap(key);//��hashmap�л�ȡһ��ָ������
		if (NULL != cur)
		{
			//�ҵ��˸û��棬��Ҫ�������˫���������Ƴ��������²��˫�������ͷ��
			_UpdateLRUList(cur);
			data = cur->_data;
			return true;
		} 
		else
		{
			return false;
		}
	}
private:
	//ɾ��˫������
	void _DeleteList(Node* head)
	{
		Node* cur = head;

		while (cur)
		{
			head = head->_lrulistnext;
			delete cur;
			cur = head;
		}
	}
	void _UpdateLRUList(Node* node)
	{
		_RemoveFromList(node);//������汾��ʹ�����˫�������У�����������汻���·��ʣ����Խ���������˫��������ȡ��
		_InserteValToListHead(node);//���²���˫�������ͷ��
	}
	//�Ƴ���hashmap�е�ָ���ڵ�
	void _RemoveFromHashMap(Node* node)
	{
		if (NULL != node)
		{
			if (NULL == node->_hashlistprev)//�Ƴ��Ľڵ���ͷ���
			{
				_hashmap[ _HashFunc(node->_key) ] = node->_hashlistnext;

				if (node->_hashlistnext)
				{
					node->_hashlistnext->_hashlistprev = NULL;
				}
			}
			else//�Ƴ��Ľڵ�����ͨ�ڵ�
			{
				node->_hashlistprev->_hashlistnext = node->_hashlistnext;
				if (node->_hashlistnext)
				{
					node->_hashlistnext->_hashlistprev = node->_hashlistprev;
				}
			}
		}
	}
	//�Ƴ�˫�������ָ���ڵ㣨ע�����Ƴ�����ɾ������Ϊhashmap�л��н���أ����һ���ڵ�ɾ�����Σ���ô����������
	void _RemoveFromList(Node* node)
	{
		if (NULL == node)
		{
			return;
		}

		if (_lrulisthead == _lrulisttail)//ֻ��һ���ڵ�������
		{
			_lrulisthead = _lrulisttail = NULL;
		}
		else if (node == _lrulisthead)//ɾ���Ľڵ���ͷ�������
		{
			_lrulisthead = _lrulisthead->_lrulistnext;
			_lrulisthead->_lrulistprev = NULL;
		}
		else if (node == _lrulisttail)//ɾ���Ľڵ���β�������
		{
			_lrulisttail = _lrulisttail->_lrulistprev;
			_lrulisttail->_lrulistnext = NULL;
		}
		else
		{
			node->_lrulistnext->_lrulistprev = node->_lrulistprev;
			node->_lrulistprev->_lrulistnext = node->_lrulistnext;
		}

		--_size;

	}
	//������ڵ���������ͷ��
	Node* _InserteValToListHead(Node* node)
	{
		//˫�������ǰ��ջ�����Ⱥ�˳����������ģ��Ƚ�������ں󣬺���������ǰ��
		Node* lastNode = NULL;

		if (++_size > _capacity)
		{
			//������Ŀ�Ѿ��ﵽ���ޣ���Ҫɾ�����û�б����ʹ������ݣ�˫�������β��㣩
			lastNode = _lrulisttail;
			_RemoveFromList(lastNode);
		}

		if (NULL == _lrulisthead)//�����ǰ������û�нڵ�
		{
			_lrulisthead = _lrulisttail = node;

			node->_lrulistprev = NULL;
			node->_lrulistnext = NULL;
		} 
		else//ֱ�ӽ���ͷ��
		{
			node->_lrulistnext = _lrulisthead;
			_lrulisthead->_lrulistprev = node;
			node->_lrulistprev = NULL;
			_lrulisthead = node;//�ı�ͷ����ָ��
		}

		return lastNode;
	}
	//������ڵ����hashmap��
	void _InserteValToHashMap(Node* node)
	{
		Node* cur = _hashmap[_HashFunc(node->_key)];//ֱ�Ӷ�ַ����ȡhashmap�еĵ�ǰλ��

		if (NULL == cur)
		{
			_hashmap[ _HashFunc(node->_key) ] = node;

			node->_hashlistprev = NULL;
			node->_hashlistnext = NULL;
		} 
		else//cur != NULL
		{
			//���ڵ����hashmapָ��λ�õ�ǰ����
			node->_hashlistnext = cur;
			cur->_hashlistprev = node;

			_hashmap[ _HashFunc(node->_key) ] = node;//����hashmap��ǰλ�õĽڵ�
			node->_hashlistprev = NULL;
		}
	}
	int _HashFunc(const K& key)
	{
		//ֱ�Ӷ�ַ�����ҵ���Ӧ���±�
		return key%_capacity;
	}

	//��hashmap�л�ȡһ�����浥Ԫ
	Node* _GetValFromHashMap(const K& key)
	{
		Node* cur = _hashmap[ _HashFunc(key) ];//ֱ�Ӷ�ַ����ȡhashmap�еĵ�ǰλ��

		if (cur != NULL)
		{
			Compare com;
			while (cur)
			{
				if ( com(key, cur->_key) )
				{
					//����������Ѿ�����������棬��ôֱ�ӷ�����黺��Ϳ�����
					return cur;
				}
				//������
				cur = cur->_hashlistnext;
			}
		}
		
		return NULL;
	}
private:
	size_t _capacity;//���������
	Node** _hashmap;//hash����
	Node* _lrulisthead;//ָ��˫�������ͷָ��
	Node* _lrulisttail;//ָ��˫�������βָ��
	size_t _size;//��¼��ǰ����ڵ�ĸ���
};