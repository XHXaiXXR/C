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
	//����һ��������
	RBTreeNode<K,V>* _left;//����
	RBTreeNode<K,V>* _right;//�Һ���
	RBTreeNode<K,V>* _parent;//����

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
			//ֻ��һ���ڵ�ʱ�Ǹ��ڵ㣬������и��ڵ����ɫ�Ǻ�ɫ��
			_root->_col = BLACK;
			return true;
		}

		//����ڵ㣬�����������ڵ�Ĳ���
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

		while ((cur != _root) && (parent->_col == RED))//��֤��grandfher�Ĵ���
		{
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				//���1  ����ͼ
				if ((uncle) && (uncle->_col == RED))
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					//���3  ����ͼ
					if (cur == parent->_right)
					{
						_RotateL(parent);
						swap(parent,cur);
					}
					//���2   ����ͼ
					parent->_col = BLACK;
					grandfather->_col = RED;
					_RotateR(grandfather);

					break;
				}
			} 
			else //grandfather->_right == parent
			{
				Node* uncle = parent->_left;
				//���1  ����ͼ
				if ((uncle) && (uncle->_col == RED))
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					//���3  ����ͼ
					if (parent->_left == cur)
					{
						_RotateR(parent);
						swap(parent,cur);
					}
					//���3
					parent->_col = BLACK;
					grandfather->_col = RED;
					_RotateL(grandfather);

					break;
				}
			}
			_root->_col = BLACK;//�ǵ�ÿ�ε�����ɺ����ζ������ĸ��ڵ����ɫҪ���ɺ�ɫ
			                    //��ʱ�����������������
		}
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	bool IsBlance()
	{
		//����һ�ú����������
		//1.���ڵ��Ǻ�ɫ��
		//2.û�������ĺ�ڵ�
		//3��ÿ��·���ϵĺ�ɫ�ڵ���Ŀ��ͬ
		//4���·�����������·��������
		
		if (_root == NULL)
		{
			//����Ҳ��������������
			return true;
		}
		if (_root->_col == RED)
		{
			//Υ�������ʵĵ�һ��
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
			//�������һ��·���ĺ�ɫ�ڵ�����
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
			//������������������
			return true;
		}
		return _IsBlance(root->_left,k,count)
			&& _IsBlance(root->_right,k,count);

		if ((root->_col == RED) && (root->_parent->_col == RED))
		{
			cout<<root->_key<<"  �������ĺ�ڵ�"<<endl;
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
			cout<<root->_key<<"  ·���ϵĺ�ɫ�ڵ���Ŀ����ͬ"<<endl;
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

