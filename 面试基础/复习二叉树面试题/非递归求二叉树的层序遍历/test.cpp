void TierOrderQueue()
	{
		if (_root == NULL)
		{
			return ;
		}
		queue<Node*> q;
		Node* cur = _root;
		q.push(cur);

		while (!q.empty())
		{
			Node* front = q.front();
			q.pop();
			cout<<front->_data<<" ";

			if (front->_left)
			{
				q.push(front->_left);
			}
			if (front->_right)
			{
				q.push(front->_right);
			}
		}
		cout<<endl;
	}