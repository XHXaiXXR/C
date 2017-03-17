#pragma once

template<class T>
struct SortTreeNode
{
	T _data;
	SortTreeNode* _left;
	SortTreeNode* _right;

	SortTreeNode(T data = T())
		:_data(data)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class T>
class SortTree
{
	typedef SortTreeNode<T> Node;
public:
	SortTree()
		:_root(NULL)
	{}

	bool Insert(T data)
	{
		Node* newNode = new Node(data);

		if (_root == NULL)
		{
			_root = newNode;
			return true;
		}

		Node* cur = _root;
		Node* prev = NULL;

		while (cur)
		{
			if (cur->_data > newNode->_data)
			{
				prev = cur;
				cur = cur->_left;
			} 
			else if (cur->_data < newNode->_data)
			{
				prev = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}

		if (prev->_data > newNode->_data)
		{
			prev->_left = newNode;
		}
		else
		{
			prev->_right= newNode;
		}
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

	Node* Find(T data)
	{
		if (_root = NULL)
		{
			return NULL;
		}

		Node* cur = _root;
		while (cur)
		{
			if (cur->_data > data)
			{
				cur = cur->_left;
			} 
			else if (cur->_data < data)
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
	bool Remove(T data)
	{
		if (_root == NULL)
		{
			return false;
		}

		Node* cur = _root;
		Node* prev = NULL;

		while (cur)
		{
			if (cur->_data > data)
			{
				prev = cur;
				cur = cur->_left;
			}
			else if (cur->_data < data)
			{
				prev = cur;
				cur = cur->_right;
			}
			else
			{
				break;
			}
		}

		if (cur == NULL)
		{
			return false;
		}

		if (cur->_left == NULL)
		{
			//删除节点是根节点的情况
			if (prev == NULL)
			{
				_root = cur->_right;
			}

			if (prev->_left == cur)
			{
				prev->_left = cur->_right;
			} 
			else
			{
				prev->_right = cur->_right;
			}
		} 
		else if (cur->_right == NULL)
		{
			//删除根节点的情况
			if (prev == NULL)
			{
				_root = cur->_left;
			}

			if (prev->_left == cur)
			{
				prev->_left = cur->_left;
			}
			else
			{
				prev->_right = cur->_left;

			}
		}
		else
		{
			Node* tmp = cur->_right;
			Node* tmpprev = cur;
			while (tmp->_left)
			{
				tmpprev = tmp;
				tmp = tmp->_left;
			}

			swap(cur->_data,tmp->_data);

			if (tmpprev->_left == tmp)
			{
				tmpprev->_left = tmp->_right;
			} 
			else
			{
				tmpprev->_right = tmp->_right;
			}

			if (prev == NULL)
			{
				_root = cur;
			}

			cur = tmp;
		}

		delete cur;
	}
protected:
	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return ;
		}

		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);
	}
private:
	Node* _root;
};

void test()
{
	int arr[] = {5,9,3,6,7,0,4,2,8,1};
	SortTree<int> t;

	for (int i = 0;i < sizeof(arr)/sizeof(arr[0]);i++)
	{
		t.Insert(arr[i]);
	}

	t.InOrder();
	t.Remove(0);
	t.Remove(3);
	t.Remove(4);
	t.Remove(7);
	t.Remove(8);
	t.InOrder();
}