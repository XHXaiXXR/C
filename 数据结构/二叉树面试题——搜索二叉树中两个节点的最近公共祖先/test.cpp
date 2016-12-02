void test2()
{
	int arr[] = {5,3,4,1,7,8,2,6,0,9};
	size_t size = sizeof(arr)/sizeof(arr[0]);

	SearchBinaryTree<int> bst;
	for(size_t i = 0;i < size;i++)
	{
		bst.Insert(arr[i]);
	}
	bst.InOrder();

	typedef SearchBinaryTreeNode<int> Node;
	Node* cur = bst.GetCommonRoot(4,7);//5
	cout<<cur->_key<<endl;
	cur = bst.GetCommonRoot(0,5);//5
	cout<<cur->_key<<endl;
	cur = bst.GetCommonRoot(1,4);//3
	cout<<cur->_key<<endl;
	cur = bst.GetCommonRoot(9,6);//7
	cout<<cur->_key<<endl;
}


	Node* Find(Node* root,const K& key)
	{
		Node* cur = root;

		while (cur)
		{
			if(cur->_key > key)
				cur = cur->_left;
			else if (cur->_key < key)
				cur = cur->_right;
			else
				return cur;
		}

		return NULL;
	}

	Node* GetCommonRoot(const K& x1,const K& x2)
	{
		Node* newx1 = Find(_root,x1);
		Node* newx2 = Find(_root,x2);

		Node* cur = _GetCommonRoot(_root,newx1,newx2);
		
		return cur;
	}
protected:
	Node* _GetCommonRoot(Node* root,Node* x1,Node* x2)
	{
		if (x1 == NULL || x2 == NULL)
			return NULL;

		if (root == x1 || root == x2)
			return root;

		if(root->_key < x1->_key && root->_key < x2->_key)
			_GetCommonRoot(root->_right,x1,x2);
		else if(root->_key > x1->_key && root->_key > x2->_key)
			_GetCommonRoot(root->_left,x1,x2);
		else
			return root;
	}