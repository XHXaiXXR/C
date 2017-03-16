#pragma once

template<class T>
struct TreeNode
{
	T _data;
	TreeNode* _left;
	TreeNode* _right;

	TreeNode(T data = T())
		:_data(data)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class T>
class Tree
{
	typedef TreeNode<T> Node;
public:
	Tree()
		:_root(NULL)
	{}

	Tree(const T* arr,int size,const T invalid)
	{
		int index = 0;
		_root = _CreateTree(arr, size, invalid, index);
	}
	//Ç°Ðò±éÀú
	void PrevOrder()
	{
		_PrevOrder(_root);
		cout<<endl;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	void PostOrder()
	{
		_PostOrder(_root);
		cout<<endl;
	}
	size_t Size()
	{
		return _Size(_root);
	}
	size_t LeafSize()
	{
		return _LeafSize(_root);
	}
	size_t Depth()
	{
		return _Depth(_root);
	}
	size_t GetKLevel(int k)
	{
		return _GetKLevel(_root,k);
	}
	Node* FindNode(const T& data)
	{
		return _FindNode(_root,data);
	}
protected:
	Node* _FindNode(Node* root,const T& data)
	{
		if (root == NULL)
		{
			return NULL;
		}

		if (root->_data == data)
		{
			return root;
		}

		Node* ret = _FindNode(root->_left);
		if (ret != NULL)
		{
			return ret;
		}

		return _FindNode(root->_right);
	}
	size_t _GetKLevel(Node* root,int k)
	{
		if (root == NULL)
		{
			return 0;
		}
		if (k == 1)
		{
			return 1;
		}

		return _GetKLevel(root->_left, k-1) + _GetKLevel(root->_right, k-1);
	}
	size_t _Depth(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		return _Depth(root->_left) > _Depth(root->_right) ? _Depth(root->_left) + 1 : _Depth(root->_right) + 1;
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

		return _LeafSize(root->_left) + _LeafSize(root->_right);
	}
	size_t _Size(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		return _Size(root->_left) + _Size(root->_right) + 1;
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
	Node* _CreateTree(const T* arr,int size, const T invalid,int& index)
	{
		Node* root = NULL;
		if (arr[index] != invalid && index < size)
		{
			root = new Node(arr[index]);
			root->_left = _CreateTree(arr,size,invalid,++index);
			root->_right = _CreateTree(arr,size,invalid,++index);
		}
		return root;
	}
private:
	Node* _root;
};

void test()
{
	int arr[] = {1,2,3,'#','#',4,'#','#',5,6};
	int size = sizeof(arr)/sizeof(arr[0]);

	Tree<int> t(arr,size,'#');

	t.PrevOrder();
	t.InOrder();
	t.PostOrder();
	cout<<"size = "<<t.Size()<<endl;
	cout<<"Leafsize = "<<t.LeafSize()<<endl;
	cout<<"Depth = "<<t.Depth()<<endl;
	cout<<"KLevelSize = "<<t.GetKLevel(2)<<endl;
}












