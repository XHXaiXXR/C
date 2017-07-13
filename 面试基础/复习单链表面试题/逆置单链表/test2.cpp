	//逆置单链表（头插法）
	void ReverseList2()
	{
		if (_head == NULL || _head->_next == NULL)
		{
			//空链表和只有一个节点的链表不需要逆置
			return;
		}

		Node* cur = _head;
		Node* newhead = NULL;

		while (cur)
		{
			Node* tmp = cur;
			cur = cur->_next;
			tmp->_next = newhead;
			newhead = tmp;
		}

		_head = newhead;
	}