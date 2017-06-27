	void RemoveNoHeadNode(Node* del)
	{
		if (NULL == del)
		{
			return ;
		}

		Node* delnew = del->_next;
		del->_data = delnew->_data;
		del->_next = delnew->_next;

		delete delnew;
		delnew = NULL;

		return;
	}
	Node* FindNode(int data)
	{
		Node* cur = _head;

		while (cur && cur->_data != data)
		{
			cur = cur->_next;
		}

		if (NULL == cur)
		{
			return NULL;
		} 
		else
		{
			return cur;
		}
	}