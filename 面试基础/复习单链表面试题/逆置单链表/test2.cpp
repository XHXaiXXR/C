	//���õ�����ͷ�巨��
	void ReverseList2()
	{
		if (_head == NULL || _head->_next == NULL)
		{
			//�������ֻ��һ���ڵ��������Ҫ����
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