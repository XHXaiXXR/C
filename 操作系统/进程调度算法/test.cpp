#include<iostream>
using namespace std;
#include <stdio.h>
#include <vector>
#include<algorithm>

struct ServeContent
{
	int _name;					//������
	int _arrivetime;			//����ʱ��
	int _runingtime;			//����ʱ�䣨���У�
	int _priority;				//���ȼ���������ֵԽ�ͣ����ȼ�Լ�ߣ�
	int _intomemory;			//�����ڴ�ʱ��
	int _finish;				//���ʱ��
	double _revolve;				//��תʱ��
	double _weightrevolve;		//��Ȩ��תʱ��

	ServeContent()
		:_name(int())
		,_arrivetime(int())
		,_runingtime(int())
		,_priority(int())
		,_intomemory(int())
		,_finish(int())
		,_revolve(int())
		,_weightrevolve(double())
	{}
};


class Serve
{
	typedef ServeContent sc;
public:
	Serve(const int size = int())
	{
		_arr.resize(size);
	}

	//�����ȷ���
	void FCFS()
	{
		Insert();

		_sort_arrivetime();//���ݵ���ʱ����������ȵ��ȷ���

		for (size_t i = 0;i < _arr.size();++i)
		{
			if (i == 0)
				_arr[i]._intomemory = 0;
			else
				_arr[i]._intomemory = _arr[i-1]._intomemory + _arr[i-1]._runingtime;

			_arr[i]._finish = _arr[i]._runingtime + _arr[i]._intomemory;	//���ʱ�� = ��ʼִ��ʱ�� + �������У�ʱ��
			_arr[i]._revolve = _arr[i]._finish - _arr[i]._arrivetime;		//��תʱ�� = ���ʱ�� - ����ʱ��
			_arr[i]._weightrevolve = _arr[i]._revolve / _arr[i]._runingtime;//��Ȩ��תʱ�� = ��תʱ�� / ����ʱ��
		}

		Display();
	}

	//����ҵ����
	void SJF()
	{
		Insert();
		_sort_arrivetime();

		vector<sc>::iterator it = _arr.begin();

		_arr[0]._intomemory = 0;
		_arr[0]._finish = _arr[0]._runingtime + _arr[0]._intomemory;	//���ʱ�� = ��ʼִ��ʱ�� + �������У�ʱ��
		_arr[0]._revolve = _arr[0]._finish - _arr[0]._arrivetime;		//��תʱ�� = ���ʱ�� - ����ʱ��
		_arr[0]._weightrevolve = _arr[0]._revolve / _arr[0]._runingtime;//��Ȩ��תʱ�� = ��תʱ�� / ����ʱ��

		for (size_t i = 1;i < _arr.size();++i)
		{
			vector<sc>::iterator cur = it + 1;

			while (cur != _arr.end())
			{
				if (cur->_arrivetime > it->_finish)
				{
					break;
				}

				++cur;
			}

			struct Less
			{
				bool operator()(const sc& left,const sc right)
				{
					return left._runingtime < right._runingtime;
				}
			};

			sort(it+1,cur,Less());

			_arr[i]._intomemory = _arr[i-1]._intomemory + _arr[i-1]._runingtime;
			_arr[i]._finish = _arr[i]._runingtime + _arr[i]._intomemory;	//���ʱ�� = ��ʼִ��ʱ�� + �������У�ʱ��
			_arr[i]._revolve = _arr[i]._finish - _arr[i]._arrivetime;		//��תʱ�� = ���ʱ�� - ����ʱ��
			_arr[i]._weightrevolve = _arr[i]._revolve / _arr[i]._runingtime;//��Ȩ��תʱ�� = ��תʱ�� / ����ʱ��

			++it;
		}

		Display();
	}

	//ʱ��Ƭ��ת
	void Robin()
	{
		Insert();

		cout<<"������ʱ��Ƭ��תʱ�䣺";
		int num = 0;
		cin>>num;

		if (num <= 0)
		{
			return;
		}

		_sort_arrivetime();

		vector<int> tmp(_arr.size());
		for (size_t i = 0;i < _arr.size();++i)
		{
			//����_runingtimeֵ����Ϊ��������޸�
			tmp[i] = _arr[i]._runingtime;
		}

		//��¼��ǰ�м�������
		int count = 0;
		//һ�����̽�����ʱ��Ƭ����Ϊ������PCB����¼����λ�õ���һ��λ��
		int key = 0;
		//��ǰʱ�����Ƿ��н��̽���
		int Y = 0;
		//ʱ����
		int time = 0;
		//������̵ĸ���
		int newcount = 0;
		do 
		{
			size_t i = Y;
			for (;i < _arr.size();++i)
			{
				//Ѱ�ҵ�ǰʱ�����Ƿ��н��̽���PCB
				if (time >= _arr[i]._arrivetime)
					++count;
				else
					break;
			}
			
			if (count == 0)
			{
				//���û�н��̽���Ļ���ʱ��Ҫ����
				time += num;
			} 
			else
			{
				newcount = count;
				Y = i;
			}
			int begin = key;

			while (newcount--)
			{
				time += num;
				_arr[begin]._runingtime -= num;

				if (_arr[begin]._runingtime == 0)
				{
					_arr[begin]._finish = time;
					--count;
					++key;
				} 
				else if(_arr[begin]._runingtime < 0)
				{
					_arr[begin]._finish = time + _arr[begin]._runingtime;
				}

				++begin;
			}
		} while (count > 0);

		for (size_t i = 0;i < _arr.size();++i)
		{
			//��֮ǰ�����_runingtimeֵ���¸�ֵ������
			_arr[i]._runingtime = tmp[i];

			if (i == 0)
			{
				_arr[0]._intomemory =0;
			} 
			else
			{
				_arr[i]._intomemory = _arr[i-1]._intomemory + _arr[i-1]._runingtime;
			}

			_arr[i]._revolve = _arr[i]._finish - _arr[i]._arrivetime;		//��תʱ�� = ���ʱ�� - ����ʱ��
			_arr[i]._weightrevolve = _arr[i]._revolve / _arr[i]._runingtime;//��Ȩ��תʱ�� = ��תʱ�� / ����ʱ��
		}

		Display();
	}

	void Insert()
	{
		int flag = 0;
		cout<<"�Ƿ�����ȼ�����Ҫ�󣿣��ǡ�������1���񡪡�����0����"<<endl;
		cin>>flag;

		if (flag == 0)
		{
			cout<<"��ֱ����룺"<<endl;
			cout<<"������   ����ʱ��   ����ʱ��"<<endl;
			for (size_t i = 0;i < _arr.size();++i)
			{
				cin>>_arr[i]._name>>_arr[i]._arrivetime>>_arr[i]._runingtime;
			}
		} 
		else if(flag == 1)
		{
			cout<<"��ֱ����룺"<<endl;
			cout<<"������	����ʱ��	����ʱ��	���ȼ���"<<endl;
			for (size_t i = 0;i < _arr.size();++i)
			{
				cin>>_arr[i]._name>>_arr[i]._arrivetime>>_arr[i]._runingtime>>_arr[i]._priority;
			}
		}
	}
	void Display()
	{
		cout<<"******************************************************************************************************************************************"<<endl;
		printf("������\t\t����ʱ��\t����ʱ��\t�����ڴ�ʱ��\t���ȼ���\t���ʱ��\t��תʱ��\t\t��Ȩ��תʱ��\n");
		cout<<"******************************************************************************************************************************************"<<endl;

		for (size_t i = 0;i < _arr.size();++i)
		{
			printf("%2d\t\t%2d\t\t%2d\t\t%2d\t\t%2d\t\t%2d\t\t%2f\t\t%2f\n",_arr[i]._name,_arr[i]._arrivetime,_arr[i]._runingtime,
				_arr[i]._intomemory,_arr[i]._priority,_arr[i]._finish,_arr[i]._revolve,_arr[i]._weightrevolve);
		}
		cout<<"******************************************************************************************************************************************"<<endl;

	}
protected:
	void _sort_arrivetime()
	{
		for (size_t i = 0;i < _arr.size() - 1;++i)//����
		{
			for (size_t j = 0;j < _arr.size() - 1 - i;++j)//����
			{
				if (_arr[j]._arrivetime > _arr[j+1]._arrivetime)
				{
					swap(_arr[j],_arr[j+1]);
				}
			}
		}
	}
private:
	vector<sc> _arr;
};

void test()
{
	cout<<"�������̣� "<<endl;
	int n = 0;
	cin>>n;
	Serve s(n);
	//s.FCFS();	//�����ȷ����㷨
	//s.SJF();	//����ҵ����
	s.Robin();	//ʱ��Ƭ��ת
}
int main()
{
	test();
	system("pause");
	return 0;
}