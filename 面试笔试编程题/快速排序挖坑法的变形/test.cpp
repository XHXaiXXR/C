#include<iostream>
using namespace std;
#include<vector>

int Find(vector<bool> flag)
{
	for (size_t i = 0;i < flag.size();++i)
	{
		if (flag[i] == false)
		{
			return i;
		}
	}

	return -1;
}

vector<char> SwapSort(vector<char> arr,vector<int> pos,int n)
{
	int count = 0;//��¼�����Ĵ���������ѭ������
	vector<bool> flag(n,false);//��Ǹ�λ���Ƿ��Ѿ�����

	for(int i = 0;(i < n) && (count < n); )
	{
		int tmp = arr[i];	//�ڿӱ��浱ǰֵ
		int newi = i;		//���ڵ�ǰpos[newi]�Ƿ����i���Ա㽫����������tmp���ֵ������ǰҪ����ֵ��λ�ã�index��λ�ã�

		while(++count < n)
		{
			int index = newi;		//��¼ÿ�ε�ǰλ�ý������±�

			//��ǰλ�ú���Ҫ������λ���ص�������Ҫ����
			if(newi == pos[newi])
			{
				flag[newi] = true;	//�Ѹ�λ�ñ�ǳ��ѽ�������Ϣ
				i = Find(flag);		//Ѱ��һ��û�н�����־���±�
				tmp = arr[i];		//��ǰ�±���֮�󽻻����ж��ᱻ���ǣ���Ҫ��������
				newi = i;			//newi��Ҫ���¸�ֵ
			}
			else
			{
				arr[newi] = arr[pos[newi]];	//����Ҫ�ŵ����ݸ��ǵ���ǰλ��
				flag[newi] = true;			//����Ѿ�����
				newi = pos[newi];			//newiÿ�ζ���ת��pos[newi]��λ���ظ��������ϲ���

				//�����λ�����ϴ�ѭ��֮ǰ����tmp��λ�ã�˵�����λ�õ�ֵ֮ǰ�Ѿ������ǵ���tmp��ֵ����ԭʼ������
				if (newi == i)
				{
					arr[index] = tmp;		//indexָ����ǵ�ǰλ�ã���ԭ������������ֵ���ڵ�ǰλ��
					i = Find(flag);			//����Ѱ��һ��û�б���ǽ�������λ��

					//ȫ���������
					if (i == -1)
					{
						return arr;
					}

					tmp = arr[i];
					newi = i;
				}
			}
		}
		arr[newi] = tmp;	//ѭ�������Ժ����һ��newi��λ��û�б���ֵ���ʶ���һ�������Ĳ���
	}
	return arr;
}
void test()
{
	char arr[] = {'A','B','C','D','E'};

	//int pos[] = {3,0,1,4,2};//D A B E C
	//int pos[] = {3,0,2,1,4};//D A C B E
	//int pos[] = {4,0,2,1,3};//E A C B D
	int pos[] = {3,4,1,0,2};//D E B A C

	int size1 = sizeof(arr)/sizeof(arr[0]);
	int size2 = sizeof(pos)/sizeof(pos[0]);

	if(size1 == size2)
	{
		vector<char> parr(arr,arr + size1);
		vector<int> ppos(pos,pos + size2);

		parr = SwapSort(parr,ppos,size1);

		for (int i = 0;i < parr.size();++i)
		{
			cout<<parr[i]<<" ";
		}
		cout<<endl;
	}
	else
		cout<<"������������鲻ƥ��"<<endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}