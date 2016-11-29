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
		//开辟空间
		_marix = new W*[size];

		for(int i = 0;i < size;++i)
		{
			_vertexs[i] = vertexs[i];
			_marix[i] = new W[size];
		}

		//初始化数组
		for(int i = 0;i < size;++i)
		{
			for(int j = 0;j < size;++j)
			{
				_marix[i][j] = 0;
			}
		}
	}
	//给二维数组开辟了空间就一定要手动写上析构函数
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
	V* _vertexs;	//顶点
	W** _marix;		//存储边权值的矩阵
	size_t _size;	//顶点的数量
	bool _isDirected;//是否是有向图
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