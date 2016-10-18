#include<iostream>
using namespace std;

template<class K>
struct SearchBinaryTreeNode
{
	SearchBinaryTreeNode<K>* _left;
	SearchBinaryTreeNode<K>* _right;
	K _key;

	SearchBinaryTreeNode(const K& key)
		:_left(NULL)
		,_right(NULL)
		,_key(key)
	{}
};

template<class K>
class SearchBinaryTree
{
	typedef SearchBinaryTreeNode<K> Node;
public:
	SearchBinaryTree()
		:_root(NULL)
	{}
	~SearchBinaryTree()
	{
		if(_root != NULL)
		{
			_Destroy(_root);
		}
	}
public:
	bool Insert(const K& key)
	{
		if(_root == NULL)
		{
			_root = new Node(key);
			return true;
		}

		Node* cur = _root;
		Node* parent = NULL;
		while(cur)
		{
			if(cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if(cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(key);
		if(parent->_key > key)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}

		return true;
	}
	bool Find(const K& key)
	{
		Node* cur = _root;

		while(cur)
		{
			if(cur->_key > key)
			{
				cur = cur->_left;
			}
			else if(cur->_key < key)
			{
				cur = cur->_right;
			}
			else
			{
				return true;
			}
		}

		return false;
	}
	bool Remove(const K& key)
	{
		if(_root == NULL)
		{
			return false;
		}

		Node* cur = _root;
		Node* parent = NULL;

		while(cur)
		{
			if(cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if(cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				//找到了
				break;
			}
		}

		if(cur->_left == NULL)
		{
			//删除节点的左孩子为空
			if(parent->_left == cur)
			{
				parent->_left = cur->_right;
			}
			else
			{
				parent->_right = cur->_right;
			}
			delete cur;
		}
		else if(cur->_right == NULL)
		{
			//删除节点的右孩子为空
			if(parent->_left = cur)
			{
				parent->_left = cur->_left;
			}
			else
			{
				parent->_right = cur->_left;
			}
			delete cur;
		}
		else
		{
			//删除节点左右孩子都不为空
			Node* del = cur->_left;
			Node* prevdel = cur;

			//del为删除节点的前躯（相当与cur左孩子的最右节点）
			while(del->_right)
			{
				prevdel = del;
				del = del->_right;
			}

			cur->_key = del->_key;
			prevdel->_right = del->_left;

			delete del;
		}
		
		return true;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
protected:
	void _Destroy(Node* root)
	{
		if(root == NULL)
		{
			return;
		}

		_Destroy(root->_left);
		_Destroy(root->_right);

		delete root;
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
protected:
	Node* _root;
};

void test()
{
	int arr[] = {5,3,4,1,7,8,2,6,0,9};
	size_t size = sizeof(arr)/sizeof(arr[0]);

	SearchBinaryTree<int> bst;
	for(size_t i = 0;i < size;i++)
	{
		bst.Insert(arr[i]);
	}
	bst.InOrder();
	cout<<bst.Find(8)<<endl;

	bst.Remove(5);
	bst.InOrder();
}
int main()
{
	test();
	return 0;
}