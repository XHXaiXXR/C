	Node* FindMidNode()
	{
		Node* cur = _head;
		Node* prev = _head;

		while (cur && cur->_next)
		{
			prev = prev->_next;
			cur = cur->_next->_next;
		}

		return prev;
	}