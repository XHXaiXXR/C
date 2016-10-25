#include<iostream>
using namespace std;

template<class K,class V>
struct AVLTreeNode
{
	AVLTreeNode<K,V>* _left;
	AVLTreeNode<K,V>* _right;
	AVLTreeNode<K,V>* _parent;

	K _key;
	V _value;
	int _bf;

	AVLTreeNode(const K& key,const V& value)
		:_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_key(key)
		,_value(value)
		,_bf(0)
	{}
};

template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K,V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}

	bool Insert(const K& key,const V& value)
	{
		if(_root == NULL)
		{
			_root = new Node(key,value);
			return true;
		}

		Node* parent = NULL;
		Node* cur = _root;

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
				return false;
		}
		cur = new Node(key,value);
		if(parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		//更新平衡因子
		while(parent)
		{
			if(parent->_left == cur)
				parent->_bf--;
			else//parent->_right == cur
				parent->_bf++;

			if(parent->_bf == -1 || parent->_bf == 1)
			{
				//当前树的高度已经改变，需要继续向上调整
				cur = parent;
				parent = cur->_parent;
			}
			else if(parent->_bf == 0)
			{
				//当前树的高度没有发生变化，满足AVL树的性质
				break;
			}
			else //parent->_bf == -2 || parent->_bf == 2
			{
				if(parent->_bf == 2)
				{
					if(cur->_bf == 1)
					{
						//左单旋
						_L_Roteta(parent);
					}
					else //cur->_bf == -1
					{
						//右左双旋
						_RL_Roteta(parent);
					}
				}
				else //parent->_bf == -2
				{
					if(cur->_bf == -1)
					{
						//右单旋
						_R_Roteta(parent);
					}
					else //cur->_bf == 1
					{
						//左右双旋
						_LR_Roteta(parent);
					}
				}
				break;//这个break必须加
			}
		}
		return true;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	void PrintBf()
	{
		_PrintBf(_root);
		cout<<endl;
	}
protected:
	void _PrintBf(Node* root)
	{
		if(root == NULL)
			return;

		_PrintBf(root->_left);
		cout<<root->_bf<<" ";
		_PrintBf(root->_right);
	}
	void _InOrder(Node* root)
	{
		if(root == NULL)
			return;

		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}
	//左单旋
	void _L_Roteta(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* ppNode = parent->_parent;

		parent->_right = subRL;
		if(subRL)
		{
			subRL->_parent = parent;
		}
		subR->_left = parent;
		parent->_parent = subR;

		if(ppNode)
		{
			if(ppNode->_left == parent)
				ppNode->_left = subR;
			else //ppNode->_right == parent
				ppNode->_right = subR;

			subR->_parent = ppNode;
		}
		else
		{
			_root = subR;
			subR->_parent = NULL;
		}

		subR->_bf = parent->_bf = 0;
	}
	//右单旋
	void _R_Roteta(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* ppNode = parent->_parent;

		parent->_left = subLR;
		if(subLR)
		{
			subLR->_parent = parent;
		}
		subL->_right = parent;
		parent->_parent = subL;

		if(ppNode)
		{
			if(ppNode->_left == parent)
				ppNode->_left = subL;
			else //ppNode->_right == parent
				ppNode->_right = subL;

			subL->_parent = ppNode;
		}
		else
		{
			_root = subL;
			subL->_parent = NULL;
		}

		subL->_bf = parent->_bf = 0;
	}
	//左右双旋
	void _LR_Roteta(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		_L_Roteta(parent->_left);
		_R_Roteta(parent);

		if(bf == 0)
		{
			subL->_bf = subLR->_bf = parent->_bf = 0;
		}
		else if (bf == -1)
		{
			subLR->_bf = 0;
			parent->_bf = 1;
			subL->_bf = 0;
		}
		else //bf==1
		{
			subLR->_bf = 0;
			parent->_bf = 0;
			subL->_bf = -1;
		}
	}
	
	//右左双旋
	void _RL_Roteta(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		_R_Roteta(parent->_right);
		_L_Roteta(parent);

		if(bf == 0)
		{
			subRL->_bf = subR->_bf = parent->_bf = 0;
		}
		else if (bf == -1)
		{
			subRL->_bf = 0;
			subR->_bf = 1;
			parent->_bf = 0;
		}
		else //bf==1
		{
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
	}
private:
	Node* _root;
};

void test()
{
	//int arr[] = {16,3,7,11,9,29,18,14,15};
	int arr[] = {4,2,6,1,3,5,15,7,16,14};
	int size = sizeof(arr)/sizeof(arr[0]);
	AVLTree<int,int> avl;

	for(int i = 0;i < size;i++)
	{
		avl.Insert(arr[i],i);
	}
	avl.InOrder();
	avl.PrintBf();
}
int main()
{
	test();
	system("pause");
	return 0;
}