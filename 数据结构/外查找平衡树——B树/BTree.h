#pragma once

template<class K,int M>
struct BTreeNode
{
	K _key[M];//多给了一个位置是为了方便处理分裂
	BTreeNode<K,M>* _subs[M+1];//多给了一个位置是为了方便处理分裂
	BTreeNode<K,M>* _parent;
	size_t _size;//存了几个关键字

	//构造函数
	BTreeNode()
		:_parent(NULL)
		,_size(0)
	{
		for (size_t i = 0;i < M;i++)
		{
			_key[i] = K();
			_subs[i] = NULL;
		}
		_subs[M] = NULL;
	}
};

template<class K,int M>
class BTree
{
	typedef BTreeNode<K,M> Node;
public:
	BTree()//构造函数
		:_root(NULL)
	{}
	pair<Node*,int> Find(const K& key)
	{
		Node* parent = NULL;
		Node* cur = _root;

		while (cur)
		{
			size_t i = 0;
			for (i = 0;i < cur->_size;)
			{
				if (cur->_key[i] == key)
				{
					return pair<Node*,int>(cur,i);
				} 
				else if (cur->_key[i] > key)
				{
					break;
				}
				else
				{
					i++;
				}
			}
			parent = cur;
			cur = cur->_subs[i];
		}
		return pair<Node*,int>(parent,-1);//_root == NULL 的情况下返回
		                                  //找不到的情况下返回
	}
	bool Insert(const K& key)
	{
		//第一个数据插入的情况
		if (_root == NULL)
		{
			_root = new Node;
			_root->_key[0] = key;
			_root->_size = 1;
			return true;
		}

		pair<Node*,int> ret = Find(key);
		if (ret.second != -1)
		{
			//表明key值已经存在，则无需插入，错误返回
			return false;
		}

		Node* cur = ret.first;
		K newkey = key;
		Node* sub = NULL;
		while (1)
		{
			InsertKey(cur,newkey,sub);
			if (cur->_size < M)
			{
				return true;
			}
			//分裂
			int div = M / 2;
			Node* tmp = new Node;//先创建一个新的结点
			int index = 0;
			size_t i = 0;
			for (i = div + 1;i <cur->_size;i++)
			{
				//拷贝右半区间的数据到新结点
				tmp->_key[index++] = cur->_key[i];
				tmp->_size++;
				cur->_key[i] = K();
			}
			index = 0;
			for (i = div+1;i<cur->_size;i++)
			{
				//拷贝右半区间的孩子结点到新结点
				tmp->_subs[index++] = cur->_subs[i];
				if (cur->_subs[i])
				{
					cur->_subs[i]->_parent = tmp;
				}
			}

			cur->_size = cur->_size - tmp->_size - 1;//中位数往上提
			if (cur->_parent == NULL)
			{
				_root = new Node;

				_root->_key[0] = cur->_key[div];
				cur->_key[div] = K();
				
				_root->_subs[0] = cur;
				cur->_parent = _root;
				_root->_subs[1] = tmp;
				tmp->_parent = _root;
				
				_root->_size = 1;
				
				return true;
			}
			else
			{
				newkey = cur->_key[div];
				cur->_key[div] = K();
				cur = cur->_parent;
				sub = tmp;
			}
		}
		return true;//只要能跳出while（1）的死循环，就一定有返回值的了，
		            //这里的返回值是没有意义的
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
private:
	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		size_t i = 0;
		for (i = 0;i < root->_size;i++)
		{
			_InOrder(root->_subs[i]);
			cout<<root->_key[i]<<" ";
		}
		_InOrder(root->_subs[i]);
	}
	void InsertKey(Node* cur,const K& key,Node* sub)
	{
		int end = cur->_size-1;//让end指向数据的最后一个位置
		while (end >= 0)
		{
			if (cur->_key[end] > key)
			{
				cur->_key[end+1] = cur->_key[end];
				cur->_subs[end+2] = cur->_subs[end+1];
				end--;
			}
			else
			{
				//end->_key < key
				break;
			}
		}
		cur->_key[end+1] = key;
		cur->_subs[end+2] = sub;
		if (sub)
		{
			//如果孩子存在
			sub->_parent = cur;
		}
		cur->_size++;
	}
protected:
	Node* _root;
};