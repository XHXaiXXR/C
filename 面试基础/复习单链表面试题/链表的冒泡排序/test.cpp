	void BubbingSort()
	{
		if (_head->_next == NULL)
		{
			//只有一个节点的时候不需要排序
			return;
		}

		Node* end = NULL;
		Node* cur = NULL;

		//这里至少有两个节点
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