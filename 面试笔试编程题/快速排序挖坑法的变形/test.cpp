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
	int count = 0;//记录交换的次数，控制循环次数
	vector<bool> flag(n,false);//标记该位置是否已经调整

	for(int i = 0;(i < n) && (count < n); )
	{
		int tmp = arr[i];	//挖坑保存当前值
		int newi = i;		//用于当前pos[newi]是否等于i，以便将保存起来的tmp这个值赋给当前要交换值的位置（index的位置）

		while(++count < n)
		{
			int index = newi;		//记录每次当前位置交换的下标

			//当前位置和需要交换的位置重叠，则不需要交换
			if(newi == pos[newi])
			{
				flag[newi] = true;	//把该位置标记成已交换的信息
				i = Find(flag);		//寻找一个没有交换标志的下标
				tmp = arr[i];		//当前下标在之后交换当中都会被覆盖，需要保存起来
				newi = i;			//newi需要重新赋值
			}
			else
			{
				arr[newi] = arr[pos[newi]];	//所需要放的数据覆盖掉当前位置
				flag[newi] = true;			//标记已经交换
				newi = pos[newi];			//newi每次都跳转到pos[newi]的位置重复进行以上操作

				//如果该位置是上次循环之前保存tmp的位置，说明这个位置的值之前已经被覆盖掉，tmp的值才是原始的数据
				if (newi == i)
				{
					arr[index] = tmp;		//index指向的是当前位置，把原来保存起来的值放在当前位置
					i = Find(flag);			//重新寻找一个没有被标记交换过的位置

					//全部调整完毕
					if (i == -1)
					{
						return arr;
					}

					tmp = arr[i];
					newi = i;
				}
			}
		}
		arr[newi] = tmp;	//循环出来以后，最后一个newi的位置没有被赋值，故多做一步这样的操作
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
		cout<<"数组和序列数组不匹配"<<endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}