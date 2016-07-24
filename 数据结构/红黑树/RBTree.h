#pragma once

enum Colour
{
	RED,
	BLACK,
};

template<class K,class V>
class RBTreeNode
{
public:
	RBTreeNode(const K& key,const V& value)
		:_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_key(key)
		,_value(value)
		,_col(RED)
	{}
public:
	//定义一个三叉链
	RBTreeNode<K,V>* _left;//左孩子
	RBTreeNode<K,V>* _right;//右孩子
	RBTreeNode<K,V>* _parent;//父亲

	K _key;
	V _value;
	Colour _col;
};

template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K,V> Node;
public:
	RBTree()
		:_root(NULL)
	{}
	bool Insert(const K& key,const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key,value);
			//只有一个节点时是根节点，红黑树中根节点的颜色是黑色的
			_root->_col = BLACK;
			return true;
		}

		//插入节点，搜索二叉树节点的插入
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
				return false;
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

		while ((cur != _root) && (parent->_col == RED))//保证了grandfher的存在
		{
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				//情况1  见下图
				if ((uncle) && (uncle->_col == RED))
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					//情况3  见下图
					if (cur == parent->_right)
					{
						_RotateL(parent);
						swap(parent,cur);
					}
					//情况2   见下图
					parent->_col = BLACK;
					grandfather->_col = RED;
					_RotateR(grandfather);

					break;
				}
			} 
			else //grandfather->_right == parent
			{
				Node* uncle = parent->_left;
				//情况1  见下图
				if ((uncle) && (uncle->_col == RED))
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					//情况3  见下图
					if (parent->_left == cur)
					{
						_RotateR(parent);
						swap(parent,cur);
					}
					//情况3
					parent->_col = BLACK;
					grandfather->_col = RED;
					_RotateL(grandfather);

					break;
				}
			}
			_root->_col = BLACK;//记得每次调整完成后，整课二叉树的根节点的颜色要调成黑色
			                    //此时才满足二叉树的性质
		}
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	bool IsBlance()
	{
		//满足一棵红黑树的性质
		//1.根节点是黑色的
		//2.没有连续的红节点
		//3、每条路径上的黑色节点数目相同
		//4、最长路径不超过最短路径的两倍
		
		if (_root == NULL)
		{
			//空数也满足红黑树的性质
			return true;
		}
		if (_root->_col == RED)
		{
			//违背了性质的第一条
			return false;
		}

		int k = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
			{
				k++;
			}
			//求出任意一条路径的黑色节点数量
			cur = cur->_left;
		}
		int count = 0;

		return _IsBlance(_root,k,count);
	}
private:
	bool _IsBlance(Node* root,const int k,int count)
	{
		if (root == NULL)
		{
			//空树满足红黑树的性质
			return true;
		}
		return _IsBlance(root->_left,k,count)
			&& _IsBlance(root->_right,k,count);

		if ((root->_col == RED) && (root->_parent->_col == RED))
		{
			cout<<root->_key<<"  有连续的红节点"<<endl;
			return false;
		}

		if (root->_col == BLACK)
		{
			++count;
		}

		if ((root->_left == NULL) 
		 && (root->_right == NULL)
		 && (k != count))
		{
			cout<<root->_key<<"  路径上的黑色节点数目不相同"<<endl;
			return false;
		}
	}
	void _RotateL(Node* parent)
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
			subR->_parent = NULL;
		} 
		else  //ppNode != NULL
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else  //ppNode->_right == parent
			{
				ppNode->_right = subR;
			}

			subR->_parent = ppNode;
		}
	}
	void _RotateR(Node* parent)
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
			subL->_parent = NULL;
		} 
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			} 
			else //ppNode->_right == parent
			{
				ppNode->_right = subL;
			}

			subL->_parent = ppNode;
		}
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
private:
	Node* _root;
};

