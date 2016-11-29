#include<iostream>
using namespace std;
#include<string>
#include<assert.h>
#include<stdio.h>

template<class V,class W>
class GraphMarix
{
public:
	GraphMarix(V* vertexs,size_t size,const W& invlid = W(),bool isDirected = false)
		:_vertexs(new V[size])
		,_size(size)
		,_isDirected(isDirected)
	{
		//���ٿռ�
		_marix = new W*[size];

		for(int i = 0;i < size;++i)
		{
			_vertexs[i] = vertexs[i];
			_marix[i] = new W[size];
		}

		//��ʼ������
		for(int i = 0;i < size;++i)
		{
			for(int j = 0;j < size;++j)
			{
				_marix[i][j] = 0;
			}
		}
	}
	//����ά���鿪���˿ռ��һ��Ҫ�ֶ�д����������
	~GraphMarix()
	{
		delete[] _vertexs;

		for(int i = 0;i < _size;++i)
		{
			delete[] _marix[i];
		}

		delete[] _marix;
	}
public:
	void AddEdge(const V& src,const V& dst,const W& w)
	{
		size_t newsrc = _GetIndex(src);
		size_t newdst = _GetIndex(dst);
		
		_marix[newsrc][newdst] = w;
		if(_isDirected == false)
		{
			_marix[newdst][newsrc] = w;
		}
	}
	void Display()
	{
		for(int i = 0;i < _size;++i)
		{
			for(int j = 0;j < _size;++j)
			{
				//cout<<_marix[i][j]<<" ";
				printf("%3d\t",_marix[i][j]);
			}
			cout<<endl;
		}
	}
private:
	size_t _GetIndex(const V& v)
	{
		for(int i = 0;i < _size;++i)
		{
			if(_vertexs[i] == v)
				return i;
		}

		assert(false);
	}
private:
	V* _vertexs;	//����
	W** _marix;		//�洢��Ȩֵ�ľ���
	size_t _size;	//���������
	bool _isDirected;//�Ƿ�������ͼ
};

void test()
{
	string arr[] = {"A","B","C","D","E"};
	int size = sizeof(arr)/sizeof(arr[0]);
	GraphMarix<string,int> gm(arr,size);
	
	gm.AddEdge("A","D",10);
	gm.AddEdge("A","E",20);
	gm.AddEdge("B","C",10);
	gm.AddEdge("B","D",20);
	gm.AddEdge("C","E",40);
	gm.AddEdge("B","E",30);

	gm.Display();
}

int main()
{
	test();
	return 0;
}