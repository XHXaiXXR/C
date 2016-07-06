#pragma once
#include <queue>
#include <stack>

template<class T>
class BinaryTreeNode
{
public:
	T _date;

	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;
public:
	BinaryTreeNode(const T& date)
		:_date(date)
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
	BinaryTree(const T* arr,size_t size,const T& invalid)
	{
		size_t inder = 0;
		_root = _CreateTree(arr,size,invalid,inder);
	}
	void PrevOrder()//�ݹ� ǰ�����
	{
		_PrevOrder(_root);
		cout<<endl;
	}
	void InOrder()//�ݹ� �������
	{
		_InOrder(_root);
		cout<<endl;
	}
	void PostOrder()//�ݹ� �������
	{
		_PostOrder(_root);
		cout<<endl;
	}
	void QueueLevelOrder()//�ǵݹ�ʵ�֣����е�Ӧ�ã��������
	{
		queue<Node* > q;
		if (_root)
		{
			q.push(_root);
		}

		while (!q.empty())//�����в�Ϊ��ʱ����ѭ��
		{
			Node* _front = q.front();
			q.pop();
			cout<<_front->_date<<" ";

			if (_front->_left)
			{
				q.push(_front->_left);
			}
			if (_front->_right)
			{
				q.push(_front->_right);
			}
		}
		cout<<endl;
	}

	void StackPrevOrder()//�ǵݹ�ʵ�֣�ջ��Ӧ�ã�ǰ�����
	{
		stack<Node* > s;
		if (_root)
		{
			s.push(_root);
		}

		while (!s.empty())
		{
			Node* _top = s.top();
			cout<<_top->_date<<" ";
			s.pop();
			if (_top->_right)
			{
				s.push(_top->_right);
			}
			if (_top->_left)
			{
				s.push(_top->_left);
			}
		}
		cout<<endl;
	}

	void StackInOrder()//�ǵݹ�ʵ�֣�ջ��Ӧ�ã��������
	{
		stack<Node* > s;
		if (_root == NULL)
		{
			return;
		}

		Node* cur = _root;

		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			Node* _top = s.top();
			cout<<_top->_date<<" ";
			s.pop();

			cur = _top->_right;
		}
		cout<<endl;
	}

	void StackPostOrder()//�ǵݹ�ʵ�֣�ջ��Ӧ�ã��������
	{
		stack<Node*> s;
		if (_root == NULL)
		{
			return;
		}
		Node* cur = _root;
		Node* prev = NULL;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			Node* _top = s.top();
			if (_top->_right == NULL || _top->_right == prev)
			{
				cout<<_top->_date<<" ";
				s.pop();
				prev = _top;
			} 
			else
			{
				cur = _top->_right;
			}
		}
		cout<<endl;
	}
protected:
	void _PostOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout<<root->_date<<" ";
	}
	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return ;
		}

		_InOrder(root->_left);
		cout<<root->_date<<" ";
		_InOrder(root->_right);
	}
	void _PrevOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		cout<<root->_date<< " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}
	Node* _CreateTree(const T* arr,size_t size,const T& invalid,size_t& inder)
	{
		Node* root = NULL;
		if (arr[inder] != invalid && inder < size)
		{
			root = new Node(arr[inder]);
			root->_left = _CreateTree(arr,size,invalid,++inder);
			root->_right = _CreateTree(arr,size,invalid,++inder);
		}
		return root;
	}
private:
	Node* _root;
};

