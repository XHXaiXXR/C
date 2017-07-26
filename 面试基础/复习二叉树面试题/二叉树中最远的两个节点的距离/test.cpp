	int GetFarDistance()
	{
		int distance = -1;
		_Height(_root,distance);
		return distance;
	}
protected:
	int _Height(Node* root, int& distance)
	{
		if (root == NULL)
		{
			return 0;
		}

		int leftH = _Height(root->_left);
		int rightH = _Height(root->_right);

		if (leftH+rightH > distance)
		{
			distance = leftH + rightH;
		}

		return leftH > rightH ? leftH+1 : rightH+1;
	}