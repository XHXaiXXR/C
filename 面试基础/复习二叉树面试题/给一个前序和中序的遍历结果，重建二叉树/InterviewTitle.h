#pragma once

template<class T>
struct BinaryTreeNode{
	T _data;
	BinaryTreeNode* _left;
	BinaryTreeNode* _right;

	BinaryTreeNode(const T data = T())
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

	void Construct(T* prev,T* in,int size)
	{
		if (prev == NULL || in == NULL || size <= 0)
		{
			return;
		}

		_root =  ConstructCore(prev,prev+size-1,in,in+size-1);
	}
	void Inorder()
	{
		_Inorder(_root);
		cout<<endl;
	}
protected:
	void _Inorder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		_Inorder(root->_left);
		cout<<root->_data<<" ";
		_Inorder(root->_right);
	}
	Node* ConstructCore(T* startprev,T* endprev,T* startin,T* endin)
	{
		Node* root = new Node(*startprev);

		if (startprev == endprev)
		{
			if (*startprev == *endprev)
			{
				return root;
			}

			return NULL;
		}

		T* rootin = startin;
		//找到中序遍历当前的根节点
		while (startin <=  endin && *rootin != root->_data)
		{
			++rootin;
		}

		int size = rootin - startin;
		int* leftstartprevend = startprev + size;

		//构建左子树
		if (size > 0)
		{
			root->_left = ConstructCore(startprev+1, leftstartprevend, startin, rootin-1);
		}
		//构建右子树
		if (size < endprev - startprev)
		{
			root->_right = ConstructCore(leftstartprevend+1,endprev, rootin+1, endin);
		}

		return root;
	}
private:
	Node* _root;
};

void test()
{
	int Prevorder[] = {1,2,4,7,3,5,6,8};
	int Inorder[] = {4,7,2,1,5,3,8,6};
	int size = sizeof(Prevorder)/sizeof(Prevorder[0]);

	BinaryTree<int> t;
	t.Construct(Prevorder,Inorder,size);
	t.Inorder();
}