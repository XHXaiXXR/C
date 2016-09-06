#pragma once
#include <assert.h>

template<class V,class W>
class GraphMartex//临接矩阵
{
public:
	GraphMartex(const V* arr,size_t size,bool isDirection)
		:_size(size)
		,_isDirection(isDirection)
	{
		_martex = new W*[size];
		_vertexs = new V[size];

		for (int i = 0;i < _size;i++)
		{
			_vertexs[i] = arr[i];
			_martex[i] = new W[size];
		}

		//初始化数组
		for (int k = 0;k < _size;k++)
		{
			for (int z = 0;z < _size;z++)
			{
				_martex[k][z] = 0;
			}
		}
	}
	//临接矩阵中添加权值
	void AddEdge(const V& src,const W& dect,const W& w)
	{
		size_t newstr = GetIndex(src);
		size_t newdect = GetIndex(dect);

		assert(newstr != -1);
		assert(newdect != -1);

		if (_isDirection)
		{
			//有向图   添加对应A->B的一条边的权重
			_martex[newstr][newdect] = w;
		} 
		else
		{
			//无向图   添加A->B和B->A两条边的权重
			_martex[newstr][newdect] = w;
			_martex[newdect][newstr] = w;
		}
	}
	//打印图
	void Display()
	{
		for (int k = 0;k < _size;k++)
		{
			cout<<_vertexs[k]<<"  ";
		}
		cout<<endl;
		int j = 0;
		int i = 0;
		for (i = 0;i < _size;i++)
		{
			for (j = 0;j < _size;j++)
			{
				cout<<_martex[i][j]<<"  ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
private:
	size_t GetIndex(const V& v)
	{
		for (int i = 0;i < _size;i++)
		{
			if (_vertexs[i] == v)
			{
				//返回对应的当前的下标
				return i;
			}
		}
		//找不到返回一个非法值
		return -1;
	}
private:
	V* _vertexs;//顶点集合
	W** _martex;//边集合
	size_t _size;//顶点个数
	bool _isDirection;//判断是否为有向图
};