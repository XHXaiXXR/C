#pragma once

template<class T>
class BinaryTreeNode
{
public:
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;

	BinaryTreeNode(const T& data)
		:_data(data)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(const T* a,size_t size,const T& invalid)//invalidΪ�Ƿ�ֵ
	{
		size_t inder = 0;
		_root = _GreateTree(a,size,invalid,inder);
	}
	void PrevOrder()//ǰ�����
	{
		_PrevOrder(_root);
		cout<<endl;
	}
	void InOrder()//�������
	{
		_InOrder(_root);
		cout<<endl;
	}
	void PostOrder()//�������
	{
		_PostOrder(_root);
		cout<<endl;
	}
	size_t Size()//�ڵ�ĸ���
	{
		return _Size(_root);
	}
	size_t LeafSize()//Ҷ�ӽڵ�ĸ���
	{
		return _LeafSize(_root);
	}
	size_t Depth()//�������ĸ߶�
	{
		return _Depth(_root);
	}
	size_t GetKLevel(size_t k)//��k��Ҷ�ӽڵ�ĸ���
	{
		return _GetKLevel(_root,k);
	}
	Node* Find(const T& data)//Ѱ��ĳ���ڵ�
	{
		return _Find(_root,data);
	}
protected:
	Node* _Find(Node* root,const T& data)
	{
		if (root == NULL)
		{
			return NULL;
		}

		if (root->_data == data)
		{
			return root;
		}

		//���������н���Ѱ��
		Node* ret = _Find(root->_left,data);
		if (ret)
		{
			return ret;
		}
		//��ȥ�����н���Ѱ��
		return _Find(root->_right,data);
	}
	size_t _GetKLevel(Node* root,size_t k)
	{
		if (root == NULL)
		{
			return 0;
		}

		if (k == 1)
		{
			return 1;
		}
		return _GetKLevel(root->_left,k-1) + _GetKLevel(root->_right,k-1);//֮ǰ��k-1д����k--�����³������
	}
	size_t _Depth(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		return _Depth(root->_left) > _Depth(root->_right) ? _Depth(root->_left)+1 : _Depth(root->_right)+1;//��Ŀ�����
	}
	size_t _LeafSize(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		if (root->_left == NULL && root->_right == NULL)
		{
			return 1;
		}

		return _LeafSize(root->_left)+_LeafSize(root->_right);
	}
	size_t _Size(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		return _Size(root->_left)+_Size(root->_right)+1;
	}
	void _PostOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout<<root->_data<<" ";
	}
	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);
	}
	void _PrevOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		cout<<root->_data<<" ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}
	Node* _GreateTree(const T* a,size_t size,const T& invalid,size_t& inder)//��Ҫ�ı��inder��ֵ������Ҫ������
	{
		Node* root = NULL;
		if (a[inder] != invalid && inder < size)
		{
			root = new Node(a[inder]);
			root->_left = _GreateTree(a,size,invalid,++inder);
			root->_right = _GreateTree(a,size,invalid,++inder);
		}
		return root;//���ظ��ڵ�
	}
private:
	Node* _root;
};
