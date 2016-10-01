#include<iostream>
using namespace std;
#include<stack>

enum Tag
{
	THREAD,
	LINK,
};

template<class T>
struct BinaryTreeThdNode
{
	T _data;
	BinaryTreeThdNode<T>* _left;
	BinaryTreeThdNode<T>* _right;
	Tag _lefttag;
	Tag _righttag;

	BinaryTreeThdNode(const T& data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
		,_lefttag(LINK)
		,_righttag(LINK)
	{}
};

template<class T>
class BinaryTreeThd
{
	typedef BinaryTreeThdNode<T> Node;
public:
	BinaryTreeThd(const T* arr,const size_t size,const T& invalid)
		:_root(NULL)
	{
		size_t index = 0;
		_root = _GreateTree(arr,size,index,invalid);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	void PrevOrderThreading()
	{
		Node* prev = NULL;
		_PrevOrderThreading(_root,prev);
	}
	void PrevOrderThd()
	{
		Node* cur = _root;

		while(cur)
		{
			while(cur->_lefttag == LINK)
			{
				cout<<cur->_data<<" ";
				cur = cur->_left;
			}

			cout<<cur->_data<<" ";
			cur = cur->_right;
		}
		cout<<endl;
	}
	void InOrderThreading()
	{
		Node* prev = NULL;
		_InOrderThreading(_root,prev);
	}
	void InOrderThd()
	{
		Node* cur = _root;

		while(cur)
		{
			while(cur->_lefttag == LINK)
			{
				cur = cur->_left;
			}
			
			cout<<cur->_data<<" ";

			while(cur->_righttag == THREAD)
			{
				cur = cur->_right;
				cout<<cur->_data<<" ";
			}
			cur = cur->_right;
		}
		cout<<endl;
	}
	void PostOrderThreading()
	{
		Node* prev = NULL;
		_PostOrderThreading(_root,prev);
	}
private:
	void _PostOrderThreading(Node* cur,Node*& prev)
	{
		if(cur == NULL)
		{
			return;
		}
		
		if(cur->_lefttag == LINK)
		{
			_PostOrderThreading(cur->_left,prev);
		}
		if(cur->_righttag == LINK)
		{
			_PostOrderThreading(cur->_right,prev);
		}

		if(cur->_left == NULL)
		{
			cur->_lefttag == THREAD;
			cur->_left = prev;
		}
		if(prev && (prev->_right == NULL))
		{
			prev->_righttag = THREAD;
			prev->_right = cur;
		}
		prev = cur;
	}
	void _InOrderThreading(Node* cur,Node*& prev)
	{
		if(cur == NULL)
		{
			return;
		}
		
		if(cur->_lefttag == LINK)
		{
			_InOrderThreading(cur->_left,prev);
		}

		if(cur->_left == NULL)
		{
			cur->_lefttag = THREAD;
			cur->_left = prev;
		}
		if(prev && (prev->_right == NULL))
		{
			prev->_righttag = THREAD;
			prev->_right = cur;
		}
		prev = cur;

		if(cur->_righttag == LINK)
		{
			_InOrderThreading(cur->_right,prev);
		}
	}
	void _PrevOrderThreading(Node* cur,Node*& prev)
	{
		if(cur == NULL)
		{
			return;
		}

		if(cur->_left == NULL)
		{
			cur->_lefttag = THREAD;
			cur->_left = prev;
		}
		if(prev && (prev->_right == NULL))
		{
			prev->_righttag = THREAD;
			prev->_right = cur;
		}
		prev = cur;

		if(cur->_lefttag == LINK)
		{
			_PrevOrderThreading(cur->_left,prev);
		}
		if(cur->_righttag == LINK)
		{
			_PrevOrderThreading(cur->_right,prev);
		}
	}
	void _InOrder(Node* root)
	{
		if(root == NULL)
		{
			return;
		}
		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);
	}
	Node* _GreateTree(const T* arr,const size_t size,size_t& index,const T& invalid)
	{
		Node* root = NULL;
		if(index < size && arr[index] != invalid)
		{
			root = new Node(arr[index]);

			root->_left = _GreateTree(arr,size,++index,invalid);
			root->_right = _GreateTree(arr,size,++index,invalid);
		}
		return root;
	}
private:
	Node* _root;
};

void test()
{
	int arr[] = {1,2,3,'#','#',4,'#','#',5,6};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	int invalid = '#';
	BinaryTreeThd<int> bt(arr,size,invalid);
	bt.InOrder();

	//bt.PrevOrderThreading();
	//bt.PrevOrderThd();
	
	bt.InOrderThreading();
	bt.InOrderThd();
	
	//bt.PostOrderThreading();
}
int main()
{
	test();
	return 0;
}