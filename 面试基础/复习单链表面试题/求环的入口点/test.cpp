	// �󻷵���ڵ�
	Node* ListLoopEntryPoint()
	{
		Node* node1 = IsListCarryLoop();
		if (node1 == NULL)
		{
			cout<<"����û�д���"<<endl;
			return NULL;
		}

		Node* head = _head;
		while (head != node1)
		{
			head = head->_next;
			node1 = node1->_next;
		}

		return head;//head == node1
	}
	
	//�ж������Ƿ����,�����ڻ��������Ľڵ�
	Node* IsListCarryLoop()
	{
		Node* cur = _head;
		Node* prev = _head;

		while (cur && cur->_next)
		{
			prev = prev->_next;
			cur = cur->_next->_next;

			if (prev == cur)
			{
				return cur;
			}
		}

		return NULL;
	}