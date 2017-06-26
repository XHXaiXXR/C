public:
	void TailToHeadPrint()
	{
		_TailToHeadPrint(_head);
		cout<<endl;
	}
private:
	void _TailToHeadPrint(Node* cur)
	{
		if (cur == NULL)
		{
			return;
		}

		_TailToHeadPrint(cur->_next);
		cout<<cur->_data<<" ";
	}