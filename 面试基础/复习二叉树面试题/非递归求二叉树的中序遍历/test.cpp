	void InOrderNR2()
	{
		if (_root == NULL)
		{
			return;
		}
		
		stack<Node*> s;
		Node* cur = _root;

		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();
			cout<<top->_data<<" ";
			s.pop();

			cur = top->_right;
		}
		cout<<endl;
	}
	void InOrderNR1()
	{
		if (_root == NULL)
		{
			return;
		}
		
		Node* cur = _root;
		Node* prev = cur;
		stack<Node*> s;
		s.push(cur);

		while (!s.empty())
		{
			Node* top = s.top();

			while (top->_left && top->_left != prev)
			{
				top = top->_left;
				prev = top;
				s.push(top);
			}

			cout<<top->_data<<" ";
			s.pop();

			if (top->_right)
			{
				prev = top;
				s.push(top->_right);
			}
		}

		cout<<endl;
	}
	void InOrder()
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