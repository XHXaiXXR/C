#pragma once
#include <vector>

template<class V,class W>
class GraphLinkEdge
{
public:
	GraphLinkEdge(size_t str,size_t dect,const W& w)
		:_str(str)
		,_dect(dect)
		,_w(w)
		,_next(NULL)
	{}
	size_t _str;
	size_t _dect;
	W _w;
	GraphLinkEdge<V,W>* _next;
};

template<class V,class W>
class GraphLink
{
public:
	GraphLink(const V* arr,size_t size,bool isDirection)
		:_isDirection(isDirection)
	{
		_vertexs.resize(size);
		_egdes.resize(size);
		for (int i = 0;i < size;i++)
		{
			_vertexs[i] = arr[i];
		}
	}
	void AddEdge(const V& str,const V& dect,const W& w)
	{
		size_t newstr = _GetIndex(str);
		size_t newdect = _GetIndex(dect);

		if (_isDirection)
		{
			//有向图   添加一条边
			_AddEdge(newstr,newdect,w);
		} 
		else
		{
			//无向图  添加两条边
			_AddEdge(newstr,newdect,w);
			_AddEdge(newdect,newstr,w);
		}
	}
	void  Display()
	{
		for (int i = 0;i < _vertexs.size();i++)
		{
			cout<<_vertexs[i]<<"["<<i<<"]->";
			GraphLinkEdge<V,W>* begin = _egdes[i];

			while (begin)
			{
				cout<<begin->_w<<"["<<begin->_dect<<"]"<<"->";
				begin = begin->_next;
			}
			cout<<"NULL"<<endl;
		}
		cout<<endl;
	}
private:
	size_t _GetIndex(const V& v)
	{
		for (int i = 0;i < _vertexs.size();i++)
		{
			if (_vertexs[i] == v)
			{
				return i;
			}
		}
		return -1;
	}
	void _AddEdge(size_t str,size_t dect,const W& w)
	{
		GraphLinkEdge<V,W>* tmp = new GraphLinkEdge<V,W>(str,dect,w);

		//这里选择了头插的方式
		tmp->_next = _egdes[str];
		_egdes[str] = tmp;
	}
private:
	vector<V> _vertexs;//顶点集合
	vector<GraphLinkEdge<V,W>*> _egdes;//邻接表存储边
	bool _isDirection;
};