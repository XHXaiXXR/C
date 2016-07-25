#pragma once

enum PointerTag
{
	THREAD,
	LINK,
};

template<class T>
class BinaryTreeThdNode
{
public:
	BinaryTreeThdNode(const T& data)
		:_left(NULL)
		,_right(NULL)
		,_data(data)
		,_leftTag(LINK)
		,_rightTag(LINK)
	{}
public:
	BinaryTreeThdNode<T>* _left;
	BinaryTreeThdNode<T>* _right;
	T _data;
	PointerTag _leftTag;
	PointerTag _rightTag;
};

template<class T>
class BinaryTreeThd
{
	typedef BinaryTreeThdNode<T> Node;
public:
	BinaryTreeThd(const T* arr,size_t size,const T& invalid)
	{
		size_t inder = 0;
		_root = _GreateTree(arr,size,invalid,inder);
	}
	void PrevOrderThreading()
	{
		Node* prev = NULL;
		_PrevOrderThreading(_root,prev);
	}
	void InOrderThreading()
	{
		Node* prev = NULL;
		_InOrderThreading(_root,prev);
	}
	void PostOrderThreading()
	{
		Node* prev = NULL;
		_PostOrderThreading(_root,prev);
	}
	void InOrder()//µÝ¹é
	{
		_InOrder(_root);
		cout<<endl;
	}
	void PrevOrder()//µÝ¹é
	{
		_PrevOrder(_root);
		cout<<endl;
	}
	void PostOrder()//µÝ¹é
	{
		_PostOrder(_root);
		cout<<endl;
	}
	void InOrderThd()
	{
		Node* cur = _root;

		while (cur)
		{
			while (cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}

			cout<<cur->_data<<" ";

			while (cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout<<cur->_data<<" ";
			}
			cur = cur->_right;
		}
		cout<<endl;
	}
	void PrevOrderThd()
	{
		Node* cur = _root;

		while (cur)
		{
			while (cur->_leftTag == LINK)
			{
				cout<<cur->_data<<" ";
				cur = cur->_left;
			}
			
			cout<<cur->_data<<" ";
			cur = cur->_right;
		}
		cout<<endl;
	}
private:
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
	void _PrevOrderThreading(Node* cur,Node*& prev)
	{
		if (cur == NULL)
		{
			return;
		}

		if (cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}

		if (prev && (prev->_right == NULL))
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}

		prev = cur;

		if (cur->_leftTag == LINK)
		{
			_PrevOrderThreading(cur->_left,prev);
		}
		if (cur->_rightTag == LINK)
		{
			_PrevOrderThreading(cur->_right,prev);
		}
	}
	void _InOrderThreading(Node* cur,Node*& prev)
	{
		if (cur == NULL)
		{
			return;
		}

		_InOrderThreading(cur->_left,prev);

		if (cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}

		if (prev && (prev->_right == NULL))
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}
		
		prev = cur;

		_InOrderThreading(cur->_right,prev);
	}
	void _PostOrderThreading(Node* cur,Node*& prev)
	{
	}
	Node* _GreateTree(const T* arr,size_t size,const T& invalid,size_t& inder)
	{
		Node* root = NULL;
		if ((inder < size) && (arr[inder] != invalid))
		{
			root = new Node(arr[inder]);

			root->_left = _GreateTree(arr,size,invalid,++inder);
			root->_right = _GreateTree(arr,size,invalid,++inder);
		}
		return root;//·µ»Ø¸ù½Úµã
	}
private:
	Node* _root;
};


