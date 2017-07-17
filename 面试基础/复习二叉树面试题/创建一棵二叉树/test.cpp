	Tree(const T* arr, size_t size, T invalid)
	{
		size_t index = 0;
		_root = _CreatTree(arr, size, invalid, index);
	}
protected:
	Node* _CreatTree(const T* arr, size_t size, T invalid, size_t& index)
	{
		Node* root = NULL;
		if (index < size && arr[index] != invalid)
		{
			root = new Node(arr[index]);
			root->_left = _CreatTree(arr, size, invalid, ++index);
			root->_right = _CreatTree(arr, size, invalid, ++index);
		}
		return root;
	}