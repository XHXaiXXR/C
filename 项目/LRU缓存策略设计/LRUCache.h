#pragma once

#include <iostream>
using namespace std;

//缓存链表，hash表的节点类型
template<class K, class T>
struct CacheNode
{
	K _key;
	T _data;
	struct CacheNode<K, T>* _hashlistprev;//指向hash链表节点的前一个节点指针
	struct CacheNode<K, T>* _hashlistnext;//指向hash链表节点的后一个节点的指针
	struct CacheNode<K, T>* _lrulistprev;//指向双向链表节点的前一个节点的指针
	struct CacheNode<K, T>* _lrulistnext;//指向双向链表节点的后一个节点的指针

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
	//定义key值的比较方式
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
	//向缓存中放入数据
	void LRUCacheSet(K key, T data)
	{
		Node* cur = _GetValFromHashMap(key);  
		if (NULL == cur)//hashmap中并没有这个缓存单元，需要新创建一个缓存单元
		{
			cur = new Node(key, data);//给缓存节点分配一块空间
			_InserteValToHashMap(cur);//将缓存节点插入hashmap中
			
			Node* lastNode = _InserteValToListHead(cur);//将缓存节点插入链表的头部
			if (NULL != lastNode)//只在双向链表中移除了，在hashmap中依然存在
			{
				_RemoveFromHashMap(lastNode);//从hashmap中移除这个单元
				delete lastNode;
			}
		} 
		else //cur != NULL
		{
			_UpdateLRUList(cur);
		}
	}
	//从缓存中得到数据
	bool LRUCacheGet(K key, T& data)
	{
		Node* cur = _GetValFromHashMap(key);//从hashmap中获取一块指定缓存
		if (NULL != cur)
		{
			//找到了该缓存，需要将缓存从双向链表中移除，并重新插会双向链表的头部
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
	//删除双向链表
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
		_RemoveFromList(node);//这个缓存本身就存在在双向链表中，现在这个缓存被重新访问，所以将这个缓存从双向链表中取出
		_InserteValToListHead(node);//重新插入双向链表的头部
	}
	//移除在hashmap中的指定节点
	void _RemoveFromHashMap(Node* node)
	{
		if (NULL != node)
		{
			if (NULL == node->_hashlistprev)//移除的节点是头结点
			{
				_hashmap[ _HashFunc(node->_key) ] = node->_hashlistnext;

				if (node->_hashlistnext)
				{
					node->_hashlistnext->_hashlistprev = NULL;
				}
			}
			else//移除的节点是普通节点
			{
				node->_hashlistprev->_hashlistnext = node->_hashlistnext;
				if (node->_hashlistnext)
				{
					node->_hashlistnext->_hashlistprev = node->_hashlistprev;
				}
			}
		}
	}
	//移除双向链表的指定节点（注意是移除不是删除，因为hashmap中还有结点呢，如果一个节点删除两次，那么程序会崩溃）
	void _RemoveFromList(Node* node)
	{
		if (NULL == node)
		{
			return;
		}

		if (_lrulisthead == _lrulisttail)//只有一个节点的情况下
		{
			_lrulisthead = _lrulisttail = NULL;
		}
		else if (node == _lrulisthead)//删除的节点是头结点的情况
		{
			_lrulisthead = _lrulisthead->_lrulistnext;
			_lrulisthead->_lrulistprev = NULL;
		}
		else if (node == _lrulisttail)//删除的节点是尾结点的情况
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
	//将缓存节点插入链表的头部
	Node* _InserteValToListHead(Node* node)
	{
		//双向链表是按照缓存的先后顺序升序排序的（先进链表的在后，后进链表的在前）
		Node* lastNode = NULL;

		if (++_size > _capacity)
		{
			//缓存数目已经达到上限，需要删除最久没有被访问过的数据（双向链表的尾结点）
			lastNode = _lrulisttail;
			_RemoveFromList(lastNode);
		}

		if (NULL == _lrulisthead)//如果当前链表中没有节点
		{
			_lrulisthead = _lrulisttail = node;

			node->_lrulistprev = NULL;
			node->_lrulistnext = NULL;
		} 
		else//直接进行头插
		{
			node->_lrulistnext = _lrulisthead;
			_lrulisthead->_lrulistprev = node;
			node->_lrulistprev = NULL;
			_lrulisthead = node;//改变头结点的指向
		}

		return lastNode;
	}
	//将缓存节点插入hashmap中
	void _InserteValToHashMap(Node* node)
	{
		Node* cur = _hashmap[_HashFunc(node->_key)];//直接定址法获取hashmap中的当前位置

		if (NULL == cur)
		{
			_hashmap[ _HashFunc(node->_key) ] = node;

			node->_hashlistprev = NULL;
			node->_hashlistnext = NULL;
		} 
		else//cur != NULL
		{
			//将节点插入hashmap指定位置的前面中
			node->_hashlistnext = cur;
			cur->_hashlistprev = node;

			_hashmap[ _HashFunc(node->_key) ] = node;//更新hashmap当前位置的节点
			node->_hashlistprev = NULL;
		}
	}
	int _HashFunc(const K& key)
	{
		//直接定址法，找到相应的下标
		return key%_capacity;
	}

	//从hashmap中获取一个缓存单元
	Node* _GetValFromHashMap(const K& key)
	{
		Node* cur = _hashmap[ _HashFunc(key) ];//直接定址法获取hashmap中的当前位置

		if (cur != NULL)
		{
			Compare com;
			while (cur)
			{
				if ( com(key, cur->_key) )
				{
					//如果缓存中已经有了这个缓存，那么直接返回这块缓存就可以了
					return cur;
				}
				//拉链法
				cur = cur->_hashlistnext;
			}
		}
		
		return NULL;
	}
private:
	size_t _capacity;//缓存的容量
	Node** _hashmap;//hash数组
	Node* _lrulisthead;//指向双向链表的头指针
	Node* _lrulisttail;//指向双向链表的尾指针
	size_t _size;//记录当前缓存节点的个数
};