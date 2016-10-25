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
		//����ƽ������
		while(parent)
		{
			if(parent->_left == cur)
				parent->_bf--;
			else//parent->_right == cur
				parent->_bf++;

			if(parent->_bf == -1 || parent->_bf == 1)
			{
				//��ǰ���ĸ߶��Ѿ��ı䣬��Ҫ�������ϵ���
				cur = parent;
				parent = cur->_parent;
			}
			else if(parent->_bf == 0)
			{
				//��ǰ���ĸ߶�û�з����仯������AVL��������
				break;
			}
			else //parent->_bf == -2 || parent->_bf == 2
			{
				if(parent->_bf == 2)
				{
					if(cur->_bf == 1)
					{
						//����
						_L_Roteta(parent);
					}
					else //cur->_bf == -1
					{
						//����˫��
						_RL_Roteta(parent);
					}
				}
				else //parent->_bf == -2
				{
					if(cur->_bf == -1)
					{
						//�ҵ���
						_R_Roteta(parent);
					}
					else //cur->_bf == 1
					{
						//����˫��
						_LR_Roteta(parent);
					}
				}
				break;//���break�����
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
	//�ж�һ�����Ƿ���ƽ�������
	bool IsBlance()
	{
		return _IsBlance(_root);
	}
	bool IsBlance_OP()
	{
		int Height = 0;

		return _IsBlance_OP(_root,Height);
	}
protected:
	bool _IsBlance_OP(Node* root,int& height)
	{
		if (root == NULL)
		{
			height = 0;
			return true;
		}

		int leftHeight = 0;
		if (_IsBlance_OP(root->_left,leftHeight) == false)
		{
			return false;
		}

		int rightHeight = 0;
		if (_IsBlance_OP(root->_right,rightHeight) == false)
		{
			return false;
		}

		height = leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;

		return abs(rightHeight - leftHeight) < 2;
	}

	bool _IsBlance(Node* root)
	{
		if (root == NULL)
			return true;
		
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);

		if (abs(leftHeight - rightHeight) >= 2)
		{
			cout<<"ƽ�������쳣��"<<root->_key<<endl;
			return false;
		}

		return abs(rightHeight - leftHeight) < 2
			&& _IsBlance(root->_left)
			&& _IsBlance(root->_right);
	}
	int _Height(Node* root)
	{
		if(root == NULL)
			return 0;

		int leftHeight = _Height(root->_left) + 1;
		int rightHeight = _Height(root->_right) + 1;

		return leftHeight > rightHeight ? leftHeight : rightHeight;
	}
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
	//����
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
	//�ҵ���
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
	//����˫��
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
	
	//����˫��
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
		//cout<<"IsBlance? "<<avl.IsBlance()<<endl;
		cout<<"IsBlance? "<<avl.IsBlance_OP()<<endl;

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