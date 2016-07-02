#pragma once

template<class K,class V>
class BSTreeNode
{
public:
	K _key;
	V _value;

	BSTreeNode<K,V>* _left;
	BSTreeNode<K,V>* _right;

	BSTreeNode(const K& key,const V& value)
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class K,class V>
class BSTree
{
	typedef BSTreeNode<K,V> Node;
public:
	BSTree()
		:_root(NULL)
	{}
	bool Insert(const K& key,const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key,value);
		}

		//_root != NULL
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			} 
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else//cur->_key == key
			{
				return false;
			}
		}

		if (parent->_key > key)
		{
			parent->_left = new Node(key,value);
		} 
		else
		{
			parent->_right = new Node(key,value);
		}
	}

	Node* Find(const K& key)
	{
		if (_root == NULL)
		{
			return NULL;
		}

		Node* cur = _root;

		while (cur)
		{
			if (cur->_key > key)
			{
				cur = cur->_left;
			} 
			else if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}

		return NULL;
	}

	bool ReMove(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;

		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				break;
			}
		}

		if (cur == NULL)//树不存在或者找不到的情况下
		{
			return false;
		}

		if (cur->_left == NULL)
		{
			//parent->_left = cur->_right;

			if (parent == NULL)//处理删除节点为根节点的情况
			{
				_root = cur->_right;
			} 
			else
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_right;
				} 
				else //parent->_right == cur
				{
					parent->_right = cur->_right;
				}
			}
		} 
		else if (cur->_right == NULL)
		{
			//parent->_right = cur->_left;
			if (parent == NULL)//处理删除节点为根节点的情况
			{
				_root = cur->_left;
			} 
			else
			{
				if (parent->_left == cur)
				{
					parent->_left = cur->_left;
				} 
				else //parent->_right == cur
				{
					parent->_right = cur->_left;
				}
			}
		}
		else//左右孩子都有节点
		{
			parent = cur;//这句代码刚刚忘记加了，导致程序崩溃
			//要确保while循环进不去的时候，parent能有赋值
			Node* tmp = cur->_right;
			while (tmp->_left)
			{
				parent = tmp;
				//找右孩子的最左节点
				tmp = tmp->_left;
			}

			cur->_key = tmp->_key;
			cur->_value = tmp->_value;

			if (parent->_left == tmp)
			{
				parent->_left = tmp->_right;
			} 
			else //parent->_right == tmp
			{
				parent->_right = tmp->_right;
			}

			delete tmp;//记得要释放内存
		}
	}

	void InOrder()
	{
		return _InOrder(_root);
	}
private:
	void _InOrder(Node*& root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}
private:
	Node* _root;
};

