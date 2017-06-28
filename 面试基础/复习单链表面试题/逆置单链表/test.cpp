	void ReverseList()
	{
		Node* p = _head;
		Node* q = NULL;
		Node* r = NULL;

		while (p)
		{
			q = p->_next;
			p->_next = r;
			r = p;
			p = q;
		}

		_head = r;
	}