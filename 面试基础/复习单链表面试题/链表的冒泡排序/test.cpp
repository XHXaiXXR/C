	void BubbingSort()
	{
		if (_head->_next == NULL)
		{
			//ֻ��һ���ڵ��ʱ����Ҫ����
			return;
		}

		Node* end = NULL;
		Node* cur = NULL;

		//���������������ڵ�
		do 
		{
			cur = _head;
			for (Node* node = cur->_next; node != end; )
			{
				if (node->_data < cur->_data)
				{
					swap(node->_data, cur->_data);
				}

				node = node->_next;
				cur = cur->_next;
			}

			end = cur;
		} while (cur != _head);
		
		return;
	}