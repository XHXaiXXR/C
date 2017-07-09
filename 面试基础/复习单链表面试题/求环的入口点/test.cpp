	// 求环的入口点
	Node* ListLoopEntryPoint()
	{
		Node* node1 = IsListCarryLoop();
		if (node1 == NULL)
		{
			cout<<"链表没有带环"<<endl;
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
	
	//判断链表是否带环,返回在环里相遇的节点
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