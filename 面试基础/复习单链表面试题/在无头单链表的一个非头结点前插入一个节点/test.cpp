	void InsertNodePrev(Node* cur, int data)
	{
		if (NULL == cur)
		{
			return ;
		}

		//����һ����Ҫ������Ľڵ�
		Node* node = new Node(data);

		//���Ҫ��ͷ����ǰ�����һ���ڵ�Ļ���ͷ����ָ�����Ҫ���ı�
		if (_head == cur)
		{
			node->_next = cur;
			_head = node;
			return;
		}

		//�ڵ�ǰ�ڵ�ĺ������һ���½�㣬�ڽ��½���ֵ�͵�ǰ�ڵ��ֵ�Ի��Ϳ�����
		node->_next = cur->_next;
		cur->_next = node;
		swap(cur->_data, node->_data);

		return;
	}