#pragma once
#include <iostream>
using namespace std;

template<class V,class W>
class GrapMartex
{
public:
	GrapMartex(const V* arr,size_t size,bool isDirection)
		:_size(size)
		,_isDirection(isDirection)
	{
		_v = new V[_size];
		_w = new W*[_size];

		for (size_t i = 0;i < _size;++i)
		{
			_v[i] = arr[i];
			_w[i] = new W[_size];
		}

		//初始化二维数组
		for (size_t i = 0;i < _size;++i)
		{
			for (size_t j = 0;j < _size;++j)
			{
				_w[i][j] = 0;
			}
		}
	}
	void AddEdge(const V& src,const V& dect,const W& w)
	{
		int newsrc = _GetIndex(src);
		int newdect = _GetIndex(dect);
		
		//判断是否是有向图，有向图添加一条边，无向图添加两条边
		if (_isDirection == true)
		{
			_w[newsrc][newdect] = w;
		} 
		else
		{
			_w[newsrc][newdect] = w;
			_w[newdect][newsrc] = w;
		}
	}

	void Display()
	{
		for (size_t i = 0;i < _size;++i)
		{
			for (size_t j = 0;j < _size;++j)
			{
				cout<<_w[i][j]<<" ";
			}
			cout<<endl;
		}
	}
protected:
	int _GetIndex(const V& v)
	{
		for (size_t i = 0;i < _size;++i)
		{
			if (_v[i] == v)
			{
				//返回位置的下标
				return i;
			}
		}

		return -1;//找不到对应的下标
	}
private:
	V* _v;//顶点集合
	W** _w;//边集合、权值集合
	size_t _size;//顶点个数
	bool _isDirection;//判断是否是有向图
};

void Test()  
{  
	GrapMartex<char,int> g("ABCDE",5,false);  
	g.AddEdge('B','C',10);  
	g.AddEdge('B','D',20);  
	g.AddEdge('B','E',30);  
	g.AddEdge('C','E',40);  
	g.AddEdge('D','A',10);  
	g.AddEdge('A','E',20);  

	g.Display();  
}  