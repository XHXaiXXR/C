#pragma once

enum Tag
{
	THREAD,
	LINK,
};

template<class T>
struct TreeThreadNode
{
	T _data;
	TreeThreadNode* _left;
	TreeThreadNode* _right;
	Tag _leftTag;
	Tag _rightTag;

	TreeThreadNode(T data = T())
		:_data(data)
		,_left(NULL)
		,_right(NULL)
		,_leftTag(LINK)
		,_rightTag(LINK)
	{}
};

template<class T>
class TreeThread
{
	typedef TreeThreadNode<T> Node;
public:
	TreeThread()
		:_root(NULL)
	{}

	TreeThread(const T* arr, int size, const T invalid)
	{
		int index = 0;
		_root = _CreateTree(arr, size, invalid, index);
	}
	void StackPrevOrder()
	{
		stack<Node*> s;
		if (_root != NULL)
		{
			s.push(_root);
		}

		while (s.size() != 0)
		{
			Node* top = s.top();
			cout<<top->_data<<" ";
			s.pop();

			if (top->_right)
			{
				s.push(top->_right);
			}
			if (top->_left)
			{
				s.push(top->_left);
			}
		}
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

	void InOrderThreading()
	{
		Node* prev = NULL;
		_InOrderThreading(_root,prev);
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

	void PostOrderThd()
	{

	}
protected:
	void _PostOrderThreading(Node* cur, Node*& prev)
	{
		if (cur == NULL)
		{
			return;
		}

		if (cur->_leftTag == LINK)
		{
			_PostOrderThreading(cur->_left,prev);
		}
		if (cur->_rightTag == LINK)
		{
			_PostOrderThreading(cur->_right,prev);
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
	}
	void _InOrderThreading(Node* cur, Node*& prev)
	{
		if (cur == NULL)
		{
			return;
		}

		if (cur->_leftTag == LINK)
		{
			_InOrderThreading(cur->_left,prev);
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

		if (cur->_rightTag == LINK)
		{
			_InOrderThreading(cur->_right,prev);
		}
	}
	void _PrevOrderThreading(Node* cur, Node*& prev)
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

	Node* _CreateTree(const T* arr,int size, const T invalid,int& index)
	{
		Node* root = NULL;
		if (arr[index] != invalid && index < size)
		{
			root = new Node(arr[index]);
			root->_left = _CreateTree(arr,size,invalid,++index);
			root->_right = _CreateTree(arr,size,invalid,++index);
		}
		return root;
	}
private:
	Node* _root;
};

void test2()
{	
	int arr[] = {1,2,3,'#','#',4,'#','#',5,6};
	int size = sizeof(arr)/sizeof(arr[0]);

	TreeThread<int> t(arr,size,'#');
	t.StackPrevOrder();

	//t.PrevOrderThreading();
	//t.PrevOrderThd();

	//t.InOrderThreading();
	//t.InOrderThd();
}