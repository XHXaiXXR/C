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
	int _bf;//平衡因子
	K _key;
	V _value;
	AVLTreeNode* _left;//左孩子
	AVLTreeNode* _right;//右孩子
	AVLTreeNode* _parent;//父亲
};

template<class K,class V>
class AVLTree
{
	typedef AVLTreeNode<K,V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	void _RotateL(Node* parent)//左单旋
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
		subR->_bf = parent->_bf = 0;//刚开始总是没有更新平衡因子导致程序错误
	}
	void _RotateR(Node* parent)//右单旋
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
		subL->_bf = parent->_bf = 0;//刚开始总是没有更新平衡因子导致程序错误
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
				return false;//如果插入的值已经存在，则错误返回
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

		//更新平衡因子
		while (parent)
		{
			if (parent->_right == cur)//新插入的节点如果在父节点的右边，平衡因子++
			{
				parent->_bf++;
			} 
			else//parent->_left == cur   新插入的节点如果在父节点的左边，平衡因子--
			{
				parent->_bf--;
			}

			if ((parent->_bf == 1) || (parent->_bf == -1))
			{
				//向上调整
				cur = parent;
				parent = cur->_parent;
			} 
			else if(parent->_bf == 0)
			{
				break;
			}
			else  // (parent->_bf == 2) || (parent->_bf == -2)
			{
				//这时候不满足AVL树的平衡条件，需要旋转AVL树，更新平衡因子
				//旋转-->调整成平衡树

				//考虑一般情况下写出的代码
				//if ((parent->_bf == 2) && (cur->_bf == 1))
				//{
				//	左单旋
				//		_RotateL(parent);
				//} 
				//if((parent->_bf == -2) && (cur->_bf == -1))
				//{
				//	右单旋
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

		int left = Height(root->_left);//递归遍历左子树的高度
		int right = Height(root->_right);//递归遍历右子树的高度

		return (left)>(right)?(left+1):(right+1);
	}
	bool _IsBlance(Node* root)
	{
		if (root == NULL)
		{
			//空子树也满足AVL树的条件
			return true;
		}

		int left = Height(root->_left);
		int right = Height(root->_right);

		if ((right-left) != (root->_bf))
		{
			cout<<"平衡因子异常："<<root->_key<<endl;
			return false;
		}

		//abs()  绝对值函数
		return (abs(right-left) < 2)
			&& (_IsBlance(root->_left))
			&& (_IsBlance(root->_right));
	}
private:
	Node* _root;
};

