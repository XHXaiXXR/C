#pragma once

template<class K, int M>
struct BTreeNode
{
	K _key[M];//关键字，关键字最多M-1个，这里开辟M个空间是为了分裂方便
	BTreeNode<K, M>* _sub[M+1];//孩子，孩子最多M个，同样是为了分裂方便多开辟了一个空间
	BTreeNode<K, M>* _parent;//便于记录孩子分裂以后的指向
	size_t _size;//关键字的个数

	BTreeNode()
		:_parent(NULL)
		,_size(0)
	{
		for (size_t i = 0;i < M;i++)
		{
			_key[i] = K();
			_sub[i] = NULL;
		}
		_sub[M] = NULL;
	}
};

template<class K, int M>
class BTree
{
	typedef BTreeNode<K, M> Node;
public:
	BTree()
		:_root(NULL)
	{}
	pair<Node*, int> Find(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;

		while (cur)
		{
			size_t i = 0;
			for (i = 0;i < cur->_size;)
			{
				if (cur->_key[i] == key)
				{
					return pair<Node*, int>(cur, i);
				}
				else if (cur->_key[i] < key)
				{
					++i;
				}
				else//cur->_key > key
				{
					break;
				}
			}
			parent = cur;
			cur = cur->_sub[i];
		}

		return pair<Node*, int>(parent, -1);
	}
	bool Insert(const K& key)
	{
		if (_root == NULL)
		{
			_root = new Node;
			_root->_key[0] = key;
			_root->_size = 1;
			return true;
		}

		pair<Node*, int> ret = Find(key);
		if (ret.second != -1)
		{
			//已经存在，那就不需要插入了
			return false;
		}

		Node* cur = ret.first;
		K newkey = key;
		Node* sub = NULL;

		while (1)
		{
			_InsertKey(cur, sub, newkey);

			if (cur->_size < M)
			{
				//成功插入并且不需要分裂，那么成功返回
				return true;
			}

			//B树中关键字最多只能是M-1个，走到这里说明此时cur的关键字已经有M个了，这时候需要分裂
			int div = M / 2;//找中间值的下标
			Node* tmp = new Node;//用于存放分裂的右半区间
			int index = 0;
			size_t i= 0;
			for (i = div + 1;i < cur->_size;i++)
			{
				//拷贝右半区间的关键字
				tmp->_key[index++] = cur->_key[i];
				cur->_key[i] = K();
				tmp->_size++;
			}
			index = 0;
			for (i = div + 1;i <= cur->_size;i++)
			{
				//拷贝右半区间的孩子
				tmp->_sub[index++] = cur->_sub[i];
				if (cur->_sub[i])
				{
					cur->_sub[i]->_parent = tmp;
				}
			}

			cur->_size = cur->_size - tmp->_size - 1;//调整cur关键字的数量，这里关键字的数值必须减一，减一是为了将中间字向上提取

			if (cur->_parent == NULL)
			{
				//说明已经调整到了根节点
				_root = new Node;
				_root->_key[0] = cur->_key[div];
				cur->_key[div] = K();

				_root->_sub[0] = cur;
				cur->_parent = _root;
				_root->_sub[1] = tmp;
				tmp->_parent = _root;

				_root->_size = 1;

				return true;
			} 
			else
			{
				newkey = cur->_key[div];
				cur->_key[div] = K();
				cur = cur->_parent;//向上调整
				sub = tmp;
			}
		}

		return true;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
protected:
	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		int i = 0;
		for (i = 0;i < root->_size;i++)
		{
			_InOrder(root->_sub[i]);
			cout<<root->_key[i]<<" ";
		}
		_InOrder(root->_sub[i]);
	}
	void _InsertKey(Node* cur, Node* sub, const K& key)
	{
		//以下只做插入处理，不考虑是否需要分裂的情况

		int end = cur->_size - 1;//找到最后一个关键字
		
		while (end >= 0 && cur->_key[end] > key)
		{
			cur->_key[end + 1] = cur->_key[end];
			cur->_sub[end + 2] = cur->_sub[end + 1];
			end--;
		}
		cur->_key[end + 1] = key;
		cur->_sub[end + 2] = sub;
		if (sub)
		{
			sub->_parent = cur;
		}

		//最后一定要记得关键字的数值加一
		cur->_size++;
	}
private:
	Node* _root;
};

void test()
{   
	BTree<int,3> bt;  
	int arr[] = {53,75,139,49,145,36,101};  
	int size = sizeof(arr)/sizeof(arr[0]);  
	for (size_t i = 0;i < size;i++)  
	{  
		bt.Insert(arr[i]);  
	}  
	bt.InOrder();  
}