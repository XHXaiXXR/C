#pragma once
#include <cmath>

template<class K>
struct AVLTreeNode
{
	K _key;
	int _bf;//ƽ������
	AVLTreeNode* _left;
	AVLTreeNode* _right;
	AVLTreeNode* _parent;

	AVLTreeNode(const K& key)
		:_key(key)
		,_bf(0)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
	{}
};

template<class K>
class AVLTree
{
	typedef AVLTreeNode<K> Node;
public:
	AVLTree()
		:_root(NULL)
	{}

	bool Insert(const K& key)
	{
		if (_root == NULL)
		{
			_root = new Node(key);
			return true;
		}

		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
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
		if (parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		} 
		else//parent->_key < key
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		//����ƽ������
		while (parent)
		{
			if (parent->_left == cur)
			{
				parent->_bf--;
			} 
			else//parent->_right == cur
			{
				parent->_bf++;
			}

			if (parent->_bf == 0)
			{
				break;
			} 
			else if (parent->_bf == -1 || parent->_bf == 1)
			{
				cur = parent;
				parent = cur->_parent;
			}
			else
			{
				//��ƽ�⣬��תʹ֮ƽ��
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
					{
						_RotateL(parent);
					} 
					else//cur->_bf == -1
					{
						_RotateRL(parent);
					}
				} 
				else//parent->_bf == -2
				{
					if (cur->_bf == -1)
					{
						_RotateR(parent);
					} 
					else//cur->_bf == 1
					{
						_RotateLR(parent);
					}
				}

				//������ϣ��Ϳ����˳��ˣ�parent���ϵĽڵ�ƽ�����Ӳ�����Ӱ��
				break;
			}
		}
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}

	bool IsBlance()
	{
		return _IsBlance(_root);
	}
protected:
	int _Height(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		int leftH = _Height(root->_left) + 1;
		int rightH = _Height(root->_right) + 1;

		return leftH > rightH ? leftH : rightH;
	}
	bool _IsBlance(Node* root)
	{
		if (root == NULL)
		{
			//����Ҳ����AVL����ƽ������
			return true;
		}

		int leftH = _Height(root->_left);
		int rightH = _Height(root->_right);

		cout<<"bf = "<<root->_bf<<endl;

		return (abs(rightH - leftH) < 2) && (_IsBlance(root->_left)) && (_IsBlance(root->_right));
	}
	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout<<root->_key<<" ";
		_InOrder(root->_right);
	}
	void _RotateL(Node* parent)//����
	{
		Node* ppNode = parent->_parent;
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)	
		{
			subRL->_parent = parent;
		}
		subR->_left = parent;
		parent->_parent = subR;

		if (ppNode == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		} 
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			} 
			else
			{
				ppNode->_right = subR;
			}
			subR->_parent = ppNode;
		}

		subR->_bf = parent->_bf = 0;
	}
	void _RotateR(Node* parent)//�ҵ���
	{
		Node* ppNode = parent->_parent;
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		subL->_right = parent;
		parent->_parent = subL;

		if (ppNode == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		} 
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}
			subL->_parent = ppNode;
		}

		subL->_bf = parent->_bf = 0;
	}
	void _RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		_RotateL(parent->_left);//������
		_RotateR(parent);//���ҵ���

		if (bf == -1)
		{
			parent->_bf = 1;
			subL->_bf = 0;
		} 
		else if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
		}
		else//bf == 0
		{
			subL->_bf = parent->_bf = 0;
		}

		subLR->_bf = 0;
	}
	void _RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		_RotateR(parent->_right);
		_RotateL(parent);

		if (bf == -1)
		{
			subR->_bf = 1;
			parent->_bf = 0;
		} 
		else if (bf == 1)
		{
			parent->_bf = -1;
			subR->_bf = 0;
		}
		else//bf == 0
		{
			parent->_bf = subR->_bf = 0;
		}
		subRL->_bf = 0;
	}
private:
	Node* _root;
};

void test3()
{
	int arr[] = {4,2,6,1,3,5,15,7,16,14};  
	//int arr[] = {10,5,7};//��������˫��
	//int arr[] = {10,15,12};//��������˫��	
	int size = sizeof(arr)/sizeof(arr[0]);  

	AVLTree<int> a;  
	int i = 0;  
	for (;i < size;i++)  
	{  
		a.Insert(arr[i]);  
		cout<<a.IsBlance()<<endl;
	} 
	a.InOrder();
}