#pragma once

enum COL
{
	RED,
	BLACK,
};

template<class K>
struct RBTreeNode
{
	K _key;
	COL _col;
	RBTreeNode* _left;
	RBTreeNode* _right;
	RBTreeNode* _parent;

	RBTreeNode(K key = K())
		:_key(key)
		,_col(RED)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
	{}
};

template<class K>
class RBTree
{
	typedef RBTreeNode<K> Node;
public:
	RBTree()
		:_root(NULL)
	{}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	bool Insert(const K& key)
	{
		if (_root == NULL)
		{
			_root = new Node(key);
			//������и��ڵ����ɫ�����Ǻ�ɫ��
			_root->_col = BLACK;
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
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		//��֤��grandfather�Ĵ���
		while (cur != _root && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;

			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				
				//��һ�����
				if (uncle && uncle->_col == RED)//uncle������uncle��ɫΪ��ɫ
				{
					grandfather->_col = RED;
					parent->_col = uncle->_col = BLACK;

					//���ϵ���
					cur = grandfather;
					parent = cur->_parent;
				} 
				//�ڶ����������
				else//uncle�����ڻ�uncle��ɫΪ��ɫ
				{
					//����������������������ת��ɵڶ�������ٽ��д���
					if (cur == parent->_right)
					{
						_RotateL(parent);
						//�ı�parent��cur����ָ���ָ��
						swap(parent,cur);
					}

					//����ڶ����������������ת���µĵڶ������
					parent->_col = BLACK;
					grandfather->_col = RED;
					_RotateR(grandfather);
					
					break;
				}
			} 
			else//grandfather->_right == parent
			{
				Node* uncle = grandfather->_left;

				if (uncle && uncle->_col == RED)
				{
					grandfather->_col = RED;
					parent->_col = uncle->_col = BLACK;

					//���ϵ���
					cur = grandfather;
					parent = cur->_parent;
				} 
				else
				{
					if (cur == parent->_left)
					{
						_RotateR(parent);
						swap(parent,cur);
					} 

					parent->_col = BLACK;
					grandfather->_col = RED;
					_RotateL(grandfather);

					break;
				}
			}
		}
		_root->_col = BLACK;//��֤ÿ�η���ǰ���ڵ����ɫ��Զ�Ǻ�ɫ
		return true;
	}

	bool IsBlance()
	{
		//��������������
		//1�����ڵ��Ǻ�ɫ��
		//2��û�������ĺ�ɫ�ڵ�
		//3���·�����ܳ������·��������
		//4��ÿ��·���ϵĺ�ɫ�ڵ���Ŀ��ͬ

		if (_root == NULL)
		{
			//����Ҳ��������������
			return true;
		}

		if (_root->_col == RED)
		{
			cout<<"���ڵ����ɫΪ�죺 "<<_root->_key<<endl;
			//�������һ������
			return false;
		}

		Node* cur = _root;
		int k = 0;
		while (cur)
		{
			if (cur->_col == BLACK)
			{
				++k;
			}
			//�ҳ�����һ��·���µĺ�ɫ�ڵ�
			cur = cur->_left;
		}

		int count = 0;
		return _IsBlance(_root,k,count);
	}
protected:
	bool _IsBlance(Node* root,const int k,int count)
	{
		if (root == NULL)
		{
			return true;
		}

		if (root->_parent && root->_col == RED && root->_parent->_col == RED)
		{
			cout<<"�������ĺ�ɫ�ڵ�: "<<root->_key<<endl;
			return false;
		}

		if (root->_col == BLACK)
		{
			++count;
		}
		if (root->_left == NULL && root->_right == NULL && k != count)
		{
			cout<<"��·���ϵĺ�ɫ�ڵ���Ŀ��һ��: "<<root->_key<<endl;
			return false;
		}

		return _IsBlance(root->_left,k,count) && _IsBlance(root->_right,k,count);
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

void test4()
{
	RBTree<int> rbt;  
	//int arr[] = {16,3,7,11,9,26,18,14,15};  
	int arr[] = {48,12,56,32,99,11,10,78,22};  
	int size = sizeof(arr)/sizeof(arr[0]);  

	for (int i = 0;i < size;i++)  
	{  
		rbt.Insert(arr[i]);  
		cout<<"IsBlance? "<<rbt.IsBlance()<<endl;  
	}  
	rbt.InOrder();  
	cout<<"IsBlance? "<<rbt.IsBlance()<<endl;  
}