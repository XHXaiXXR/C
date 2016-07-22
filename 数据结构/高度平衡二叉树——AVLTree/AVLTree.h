#pragma once

template<class K,class V>
class AVLTreeNode
{
public:
	AVLTreeNode(const K& key,const V& value)       
		:_key(key)
		,_value(value)
		,_bf(0)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
	{}
public:
	int _bf;//ƽ������
	K _key;
	V _value;
	AVLTreeNode* _left;//����
	AVLTreeNode* _right;//�Һ���
	AVLTreeNode* _parent;//����
};

template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K,V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	void _RotateL(Node* parent)//����
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* ppNode = parent->_parent;

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
			_root->_parent = NULL;
		} 
		else//ppNode != NULL
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			} 
			else//ppNode->_right == parent
			{
				ppNode->_right = subR;
			}
			subR->_parent = ppNode; 
		}
		subR->_bf = parent->_bf = 0;//�տ�ʼ����û�и���ƽ�����ӵ��³������
	}
	void _RotateR(Node* parent)//�ҵ���
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* ppNode = parent->_parent;

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
			_root->_parent = NULL;
		} 
		else // ppNode != NULL
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			} 
			else//ppNode->_right == parent
			{
				ppNode->_right = subL;
			}
			subL->_parent = ppNode;
		}
		subL->_bf = parent->_bf = 0;//�տ�ʼ����û�и���ƽ�����ӵ��³������
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
			parent->_bf = 0;
			subR->_bf = 1;
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

	void _RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		if (bf == -1)
		{
			parent->_bf = 1;
			subL->_bf = 0;
		} 
		else if (bf = 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
		}
		else//bf==0
		{
			parent->_bf = subL->_bf = 0;
		}

		subLR->_bf = 0;
	}
	bool Insert(const K& key,const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key,value);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key > key)
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
				return false;//��������ֵ�Ѿ����ڣ�����󷵻�
			}
		}
		cur = new Node(key,value);
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
			if (parent->_right == cur)//�²���Ľڵ�����ڸ��ڵ���ұߣ�ƽ������++
			{
				parent->_bf++;
			} 
			else//parent->_left == cur   �²���Ľڵ�����ڸ��ڵ����ߣ�ƽ������--
			{
				parent->_bf--;
			}

			if ((parent->_bf == 1) || (parent->_bf == -1))
			{
				//���ϵ���
				cur = parent;
				parent = cur->_parent;
			} 
			else if(parent->_bf == 0)
			{
				break;
			}
			else  // (parent->_bf == 2) || (parent->_bf == -2)
			{
				//��ʱ������AVL����ƽ����������Ҫ��תAVL��������ƽ������
				//��ת-->������ƽ����

				//����һ�������д���Ĵ���
				//if ((parent->_bf == 2) && (cur->_bf == 1))
				//{
				//	����
				//		_RotateL(parent);
				//} 
				//if((parent->_bf == -2) && (cur->_bf == -1))
				//{
				//	�ҵ���
				//		_RotateR(parent);
				//}
				//break;

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
				if (parent->_bf == -2)
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
				break;
			}
		}
	}

	bool IsBlance()
	{
		return _IsBlance(_root);
	}
	void InOrderSort()
	{
		_InOrderSort(_root);
		cout<<endl;
	}
private:
	void _InOrderSort(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrderSort(root->_left);
		cout<<root->_key<<" ";
		_InOrderSort(root->_right);
	}
	int Height(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		int left = Height(root->_left);//�ݹ�����������ĸ߶�
		int right = Height(root->_right);//�ݹ�����������ĸ߶�

		return (left)>(right)?(left+1):(right+1);
	}
	bool _IsBlance(Node* root)
	{
		if (root == NULL)
		{
			//������Ҳ����AVL��������
			return true;
		}

		int left = Height(root->_left);
		int right = Height(root->_right);

		if ((right-left) != (root->_bf))
		{
			cout<<"ƽ�������쳣��"<<root->_key<<endl;
			return false;
		}

		//abs()  ����ֵ����
		return (abs(right-left) < 2)
			&& (_IsBlance(root->_left))
			&& (_IsBlance(root->_right));
	}
private:
	Node* _root;
};

