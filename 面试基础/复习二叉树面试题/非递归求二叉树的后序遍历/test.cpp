void PostOrderNR()
	{
		if (_root == NULL)
		{
			return ;
		}
		stack<Node*> s;
		Node* cur = _root;
		Node* prev = NULL;

		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			if (s.top()->_right == NULL || s.top()->_right == prev)
			{
				cout<<s.top()->_data<<" ";
				prev = s.top();
				s.pop();
			} 
			else
			{
				cur = s.top()->_right;
			}
		}
		cout<<endl;
	}
	void PostOrder()
	{
		_PostOrder(_root);
		cout<<endl;
	}
protected:
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