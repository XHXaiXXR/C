	void PrevOrderNR()
	{
		if (_root == NULL)
		{
			return;
		}

		stack<Node*> s;
		Node* cur = _root;
		s.push(cur);

		//ǰ�������˳���Ǹ����ң�����ջ���Ƚ���������ԣ����������ȴ��뵱ǰ�ڵ���ҽڵ㣬�ڴ��뵱ǰ�ڵ����ڵ㣬��������ջ��ʱ�򣬾����ȷ�����ڵ��ٷ����ҽڵ���
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