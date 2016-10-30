#include<iostream>
using namespace std;

enum COLOUR
{
	BLACK,
	RED,
};

template<class K,class V>
struct RBTreeNode
{
	K _key;
	V _value;
	COLOUR _col;
	RBTreeNode<K,V>* _left;
	RBTreeNode<K,V>* _right;
	RBTreeNode<K,V>* _parent;

	RBTreeNode(const K& key,const V& value)
		:_key(key)
		,_value(value)
		,_col(RED)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
	{}
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
		if(_root == NULL)
		{
			_root = new Node(key,value);
			_root->_col = BLACK;
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

		//��ɫ����
		while(cur != _root && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;

			if(parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				
				//��һ����� uncle������Ϊ��ɫ
				if(uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				//�ڶ��ֺ͵��������
				//uncle������/uncle������Ϊ��ɫ
				else
				{
					//�ȴ�����������
					if(cur == parent->_right)
					{
						//���parent��������
						_L_Roteta(parent);
						swap(parent,cur);
					}
					//��������������������ɵڶ������
					//�͵ڶ������һ����
					_R_Roteta(grandfather);
					grandfather->_col = RED;
					parent->_col = BLACK;

					break;
				}
			}
			else//parent == grandfather->_right
			{
				Node* uncle = grandfather->_left;
				
				//��һ����� uncle������Ϊ��
				if(uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					
					cur = grandfather;
					parent = cur->_parent;
				}
				//�ڶ�������͵��������
				//uncle������/uncle������Ϊ��ɫ
				else
				{
					//�ȴ�����������
					if(cur == parent->_left)
					{
						_R_Roteta(parent);
						swap(parent,cur);
					}
					//�������������Ϊ�ڶ������
					//ͳһ����ڶ������
					_L_Roteta(grandfather);
					parent->_col = BLACK;
					grandfather->_col = RED;

					break;
				}
			}
		}
		
		_root->_col = BLACK;
		return true;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	//�ж�һ�����Ƿ��Ǻ����
	bool IsBlance()
	{
		//����Ҳ��һ�ú����
		if(_root == NULL)
			return true;

		//���ڵ����ɫ�Ƿ��Ǻ�ɫ
		if(_root->_col != BLACK)
			return false;

		//��������һ��·����ɫ�ڵ�ĸ���
		Node* cur = _root;
		size_t blackcount = 0;
		while(cur)
		{
			if(cur->_col == BLACK)
				++blackcount;
			
			cur = cur->_left;
		}

		size_t k = 0;
		return _IsBlance(_root,k,blackcount);
	}
protected:
	bool _IsBlance(Node* root,size_t k,const size_t blackcount)
	{
		if(root == NULL)
			return true;
		
		//������ϲ�����������������ڵ�
		if(root->_col == RED && root->_parent->_col == RED)
		{
			cout<<"������������ڵ�"<<root->_key<<endl;
			return false;
		}

		//���㵱ǰ·���º�ɫ�ڵ�ĸ���
		if(root->_col == BLACK)
			++k;
		
		//ÿ��·���º�ɫ�ڵ����Ŀ��ͬ
		if(root->_left == NULL && root->_right == NULL)
		{
			if(k != blackcount)
			{
				cout<<"��ɫ�ڵ����Ŀ����ͬ"<<root->_key<<endl;
				return false;
			}
		}
		return _IsBlance(root->_left,k,blackcount)\
			&& _IsBlance(root->_right,k,blackcount);
	}
	void _InOrder(Node* root)
	{
		if(root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout<<root->_key<<"("<<root->_col<<") ";
		_InOrder(root->_right);
	}
	void _L_Roteta(Node* parent)
	{
		Node* ppNode = parent->_parent;
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if(subRL)
			subRL->_parent = parent;
		subR->_left = parent;
		parent->_parent = subR;

		if(ppNode)
		{
			if(ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;

			subR->_parent = ppNode;
		}
		else
		{
			_root = subR;
			subR->_parent = NULL;
		}
	}
	void _R_Roteta(Node* parent)
	{
		Node* ppNode = parent->_parent;
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if(subLR)
			subLR->_parent = parent;
		subL->_right = parent;
		parent->_parent = subL;

		if(ppNode)
		{
			if(ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;

			subL->_parent = ppNode;
		}
		else
		{
			_root = subL;
			subL->_parent = NULL;
		}
	}
	
private:
	Node* _root;
};

void test()
{
	RBTree<int,int> rbt;
	int arr[] = {16,3,7,11,9,26,18,14,15};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	
	for(int i = 0;i < size;i++)
	{
		rbt.Insert(arr[i],i);
		cout<<"Isblance? "<<rbt.IsBlance()<<endl;;
	}
	rbt.InOrder();
}

int main()
{
	test();
	return 0;
}