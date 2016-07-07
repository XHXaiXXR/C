#pragma once

template<class T>
class BinaryTreeNode
{
public:
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;

	BinaryTreeNode(const T& data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(const T* a,size_t size,const T& invalid)//invalid为非法值
	{
		size_t inder = 0;
		_root = _GreateTree(a,size,invalid,inder);
	}
	void PrevOrder()//前序遍历
	{
		_PrevOrder(_root);
		cout<<endl;
	}
	void InOrder()//中序遍历
	{
		_InOrder(_root);
		cout<<endl;
	}
	void PostOrder()//后序遍历
	{
		_PostOrder(_root);
		cout<<endl;
	}
	size_t Size()//节点的个数
	{
		return _Size(_root);
	}
	size_t LeafSize()//叶子节点的个数
	{
		return _LeafSize(_root);
	}
	size_t Depth()//二叉树的高度
	{
		return _Depth(_root);
	}
	size_t GetKLevel(size_t k)//第k层叶子节点的个数
	{
		return _GetKLevel(_root,k);
	}
	Node* Find(const T& data)//寻找某个节点
	{
		return _Find(_root,data);
	}
protected:
	Node* _Find(Node* root,const T& data)
	{
		if (root == NULL)
		{
			return NULL;
		}

		if (root->_data == data)
		{
			return root;
		}

		//现在左树中进行寻找
		Node* ret = _Find(root->_left,data);
		if (ret)
		{
			return ret;
		}
		//再去右树中进行寻找
		return _Find(root->_right,data);
	}
	size_t _GetKLevel(Node* root,size_t k)
	{
		if (root == NULL)
		{
			return 0;
		}

		if (k == 1)
		{
			return 1;
		}
		return _GetKLevel(root->_left,k-1) + _GetKLevel(root->_right,k-1);//之前把k-1写成了k--，导致程序错误
	}
	size_t _Depth(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		return _Depth(root->_left) > _Depth(root->_right) ? _Depth(root->_left)+1 : _Depth(root->_right)+1;//三目运算符
	}
	size_t _LeafSize(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		if (root->_left == NULL && root->_right == NULL)
		{
			return 1;
		}

		return _LeafSize(root->_left)+_LeafSize(root->_right);
	}
	size_t _Size(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		return _Size(root->_left)+_Size(root->_right)+1;
	}
	void _PostOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout<<root->_data<<" ";
	}
	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);
	}
	void _PrevOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		cout<<root->_data<<" ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}
	Node* _GreateTree(const T* a,size_t size,const T& invalid,size_t& inder)//需要改变掉inder的值，所以要用引用
	{
		Node* root = NULL;
		if (a[inder] != invalid && inder < size)
		{
			root = new Node(a[inder]);
			root->_left = _GreateTree(a,size,invalid,++inder);
			root->_right = _GreateTree(a,size,invalid,++inder);
		}
		return root;//返回根节点
	}
private:
	Node* _root;
};
