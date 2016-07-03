#pragma once

template<class K,class V>
class BSTreeRNode
{
public:
	K _key;
	V _value;

	BSTreeRNode<K,V>* _left;
	BSTreeRNode<K,V>* _right;

	BSTreeRNode(const K& key,const V& value)
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class K,class V>
class BSTreeR
{
	typedef BSTreeRNode<K,V> Node;
public:
	BSTreeR()
		:_root(NULL)
	{}
	bool Insert(const K& key,const V& value)
	{
		return _Insert(_root,key,value);
	}

	Node* Find(const K& key)
	{
		return _Find(_root,key);
	}

	bool ReMove(const K& key)
	{
		return _ReMove(_root,key);
	}

	void IrOrder()
	{
		return _InOrder(_root); 
	}
private:
	bool _ReMove(Node*& root,const K& key)//删除节点后变成一颗新的树，所以改变了树，要用引用
	{
		if (root == NULL)
		{
			return false;
		}
		
		if (root->_key > key)
		{
			_ReMove(root->_left,key);
		} 
		else if (root->_key < key)
		{
			_ReMove(root->_right,key);
		}
		else//root->_key == key 找到了，下面进行删除工作
		{
			if (root->_left == NULL)
			{
				root = root->_right;
			} 
			else if (root->_right == NULL)
			{
				root = root->_left;
			}
			else //root->_left != NULL && root->_right != NULL
			{
				Node* parent = root;
				Node* subRight = root->_right;//subRight为删除节点的右孩子

				while (subRight->_left)//寻找删除节点右孩子的最左节点
				{
					parent = subRight;
					subRight = subRight->_left;
				}

				root->_key = subRight->_key;
				root->_value = subRight->_value;

				if (parent->_left == subRight)
				{
					parent->_left = subRight->_right;
				} 
				else //parent->_right == subRight
				{
					parent->_right = subRight->_right;
				}

				delete subRight;
				return true;
			}
		}
		return false;
	}

	Node* _Find(Node* root,const K& key)
	{
		if (root == NULL)
		{
			return NULL;
		}

		if (root->_key > key)
		{
			_Find(root->_left,key);
		} 
		else if (root->_key < key)
		{
			_Find(root->_right,key);
		}
		else
		{
			return root;
		}
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}

	bool _Insert(Node*& root,const K& key,const V& value)//这里要传root的引用，因为在函数调用中要修改root的值
	{
		if (root == NULL)
		{
			root = new Node(key,value);
			return true;
		}

		if (root->_key > key)
		{
			_Insert(root->_left,key,value);//刚开始写的时候前面没有加return，错误
		} 
		else if (root->_key < key)
		{
			_Insert(root->_right,key,value);
		}
		else //root->_key == key
		{
			return false;
		}
	}
private:
	Node* _root;
};


