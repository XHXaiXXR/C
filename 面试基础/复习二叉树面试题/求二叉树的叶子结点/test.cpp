	int LeafNodeSize()
	{
		if (_root == NULL)
		{
			return 0;
		}
		size_t size = 0;
		_LeafNodeSize(_root, size);

		return size;
	}
protected:
	void _LeafNodeSize(Node* root, size_t& size)
	{
		if (root == NULL)
		{
			return;
		}

		_LeafNodeSize(root->_left, size);
		_LeafNodeSize(root->_right, size);

		if (root->_left == NULL && root->_right == NULL)
		{
			++size;
		}
	}