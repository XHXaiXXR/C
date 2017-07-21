bool CheckStack(vector<int> arrin, vector<int> arrout)
{
	if(arrin.size() != arrin.size())
	{
		return false;
	}

	stack<int> s;

	int j = 0;
	for (int i = 0;i < arrin.size();i++)
	{
		s.push(arrin[i]);

		if (!s.empty() && s.top() == arrout[j])
		{
			s.pop();
			++j;

			while (!s.empty() && s.top() == arrout[j])
			{
				++j;
				s.pop();
			}
		}
	}

	if (j == arrout.size())
	{
		return true;
	}
	else
	{
		return false;
	}
}