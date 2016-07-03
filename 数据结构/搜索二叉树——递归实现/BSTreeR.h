#pragma once

template<class K,class V>
class BSTreeRNode
{
public:
	K _key;
	V _value;

	BSTreeRNode<K,V>* _left;
	BSTreeRNode<K,V>* _right;

	BSTreeRNode(const K& key,const V& value)
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class K,class V>
class BSTreeR
{
	typedef BSTreeRNode<K,V> Node;
public:
	BSTreeR()
		:_root(NULL)
	{}
	bool Insert(const K& key,const V& value)
	{
		return _Insert(_root,key,value);
	}

	Node* Find(const K& key)
	{
		return _Find(_root,key);
	}

	bool ReMove(const K& key)
	{
		return _ReMove(_root,key);
	}

	void IrOrder()
	{
		return _InOrder(_root); 
	}
private:
	bool _ReMove(Node*& root,const K& key)//ɾ���ڵ����һ���µ��������Ըı�������Ҫ������
	{
		if (root == NULL)
		{
			return false;
		}
		
		if (root->_key > key)
		{
			_ReMove(root->_left,key);
		} 
		else if (root->_key < key)
		{
			_ReMove(root->_right,key);
		}
		else//root->_key == key �ҵ��ˣ��������ɾ������
		{
			if (root->_left == NULL)
			{
				root = root->_right;
			} 
			else if (root->_right == NULL)
			{
				root = root->_left;
			}
			else //root->_left != NULL && root->_right != NULL
			{
				Node* parent = root;
				Node* subRight = root->_right;//subRightΪɾ���ڵ���Һ���

				while (subRight->_left)//Ѱ��ɾ���ڵ��Һ��ӵ�����ڵ�
				{
					parent = subRight;
					subRight = subRight->_left;
				}

				root->_key = subRight->_key;
				root->_value = subRight->_value;

				if (parent->_left == subRight)
				{
					parent->_left = subRight->_right;
				} 
				else //parent->_right == subRight
				{
					parent->_right = subRight->_right;
				}

				delete subRight;
				return true;
			}
		}
		return false;
	}

	Node* _Find(Node* root,const K& key)
	{
		if (root == NULL)
		{
			return NULL;
		}

		if (root->_key > key)
		{
			_Find(root->_left,key);
		} 
		else if (root->_key < key)
		{
			_Find(root->_right,key);
		}
		else
		{
			return root;
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

	bool _Insert(Node*& root,const K& key,const V& value)//����Ҫ��root�����ã���Ϊ�ں���������Ҫ�޸�root��ֵ
	{
		if (root == NULL)
		{
			root = new Node(key,value);
			return true;
		}

		if (root->_key > key)
		{
			_Insert(root->_left,key,value);//�տ�ʼд��ʱ��ǰ��û�м�return������
		} 
		else if (root->_key < key)
		{
			_Insert(root->_right,key,value);
		}
		else //root->_key == key
		{
			return false;
		}
	}
private:
	Node* _root;
};


