#include <iostream>
using namespace std;

template<class T>
struct TreeNode
{
	int _data;
	TreeNode<T>* _left;
	TreeNode<T>* _right;

	TreeNode(int data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class T>
class Tree
{
	typedef TreeNode<T> Node;
public:
	Tree(int* prev, int* in, size_t size)
		:_root(NULL)
	{
		_CreateRoot(_root, prev, in, size);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
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
	void _CreateRoot(Node*& root, int* prev, int* in, size_t size)
	{
		if (size <= 0)
		{
			return;
		}

		root = new Node(prev[0]);
		int index = 0;
		for (; index < size;index++)
		{
			if (prev[0] == in[index])
			{
				break;
			}
		}

		int leftsize = index;
		int rightsize = size - index -1;
		_CreateRoot(root->_left, prev+1, in, leftsize);
		_CreateRoot(root->_right, prev+index+1, in+index+1, rightsize);
	}
private:
	Node* _root;
};

int main()
{
	int prev[] = {1, 2, 3, 4, 5, 6};
	int in[] = {3, 2, 4, 1, 6, 5};
	int size = sizeof(prev)/sizeof(prev[0]);
	Tree<int> t(prev, in, size);
	t.InOrder();

	system("pause");
	return 0;
}