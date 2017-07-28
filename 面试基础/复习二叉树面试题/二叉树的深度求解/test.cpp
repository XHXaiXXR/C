	//非递归求二叉树的深度
	int HeightNR()
	{
		if (_root == NULL)
		{
			return 0 ;
		}

		stack<Node*> s;
		Node* cur = _root;
		Node* prev = NULL;
		size_t height = 0;

		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();
			if (top->_right == NULL || top->_right == prev)
			{
				if (height < s.size())
				{
					height = s.size();
				}
				prev = top;
				s.pop();
			} 
			else
			{
				cur = top->_right;
			}
		}

		return height;
	}
	//二叉树的求深度（递归）
	int HeightR()
	{
		return _HeightR(_root);
	}
protected:
	int _HeightR(Node* root)
	{
		if (root == NULL)
		{
			return 0;
		}

		int leftH = _HeightR(root->_left)+1;
		int rightH = _HeightR(root->_right)+1;

		return leftH > rightH ? leftH : rightH;
	}