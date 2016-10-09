#include<iostream>
using namespace std;

template<class T>
struct BSTreeRNode
{
	T _key;
	BSTreeRNode<T>* _left;
	BSTreeRNode<T>* _right;

	BSTreeRNode(const T& key)
		:_key(key)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class T>
class BSTreeR
{
	typedef BSTreeRNode<T> Node;
public:
	BSTreeR()
		:_root(NULL)
	{}
public:
	bool Insert(const T& key)
	{
		return _Insert(_root,key);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	Node* TreeToList()
	{
		if(_root == NULL)
		{
			return NULL;
		}

		Node* prev = NULL;
		_TreeToList(_root,prev);

		//Ñ°ÕÒÍ·½Úµã
		while(_root->_left)
		{
			_root = _root->_left;
		}
		return _root;
	}
	void Display() 
	{
		Node* cur = _root;
		while(cur)
		{
			cout<<cur->_key<<" ";
			cur = cur->_right;
		}
		cout<<endl;
	}
private:
	void _TreeToList(Node* cur,Node*& prev)
	{
		if(cur == NULL)
		{
			return;
		}

		_TreeToList(cur->_left,prev);

		cur->_left = prev;
		if(prev)
		{
			prev->_right = cur;
		}
		prev = cur;

		_TreeToList(cur->_right,prev);
	}
	void _InOrder(Node* root)
	{
		if(root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}
	bool _Insert(Node*& root,const T& key)
	{
		if(root == NULL)
		{
			root = new Node(key);
			return true;
		}

		if(root->_key > key)
		{
			_Insert(root->_left,key);
		}
		else if(root->_key < key)
		{
			_Insert(root->_right,key);
		}
		else//root->_key == key
		{
			return false;
		}

		return true;
	}
private:
	Node* _root;
};
void test()
{
	BSTreeR<int> bst;
	bst.Insert(5);
	bst.Insert(9);
	bst.Insert(0);
	bst.Insert(6);
	bst.Insert(8);
	bst.Insert(2);

	bst.InOrder();

	bst.TreeToList();
	bst.Display();
}
int main()
{
	test();
	return 0;
}