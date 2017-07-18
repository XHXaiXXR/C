	void PrevOrderNR()
	{
		if (_root == NULL)
		{
			return;
		}

		stack<Node*> s;
		Node* cur = _root;
		s.push(cur);

		//前序遍历的顺序是根左右，由于栈是先进后出的特性，所有我们先存入当前节点的右节点，在存入当前节点的左节点，这样当出栈的时候，就是先访问左节点再访问右节点了
		while ( !s.empty() )
		{
			Node* top = s.top();
			cout<<top->_data<<" ";			
			s.pop();

			if (top->_right)
			{
				s.push(top->_right);
			}
			if (top->_left)
			{
				s.push(top->_left);
			}
		}
		cout<<endl;
	}
	void PrevOrder()
	{
		_PrevOrder(_root);
		cout<<endl;
	}
protected:
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