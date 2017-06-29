	void InsertNodePrev(Node* cur, int data)
	{
		if (NULL == cur)
		{
			return ;
		}

		//创建一个需要被插入的节点
		Node* node = new Node(data);

		//如果要在头结点的前面插入一个节点的话，头结点的指向就需要被改变
		if (_head == cur)
		{
			node->_next = cur;
			_head = node;
			return;
		}

		//在当前节点的后面插入一个新结点，在将新结点的值和当前节点的值对换就可以了
		node->_next = cur->_next;
		cur->_next = node;
		swap(cur->_data, node->_data);

		return;
	}