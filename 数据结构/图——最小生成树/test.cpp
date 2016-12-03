#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<assert.h>
#include "Heap.h"
#include "UnionFindFet.h"

template<class V,class W>
class GraphLink
{
public:
	struct Node
	{
		W _w;
		size_t _src;
		size_t _dst;
		Node* _next;

		Node(size_t src,size_t dst,const W& w)
			:_src(src)
			,_dst(dst)
			,_w(w)
			,_next(NULL)
		{}
	};
	GraphLink(V* vertexs,size_t size,bool isDirected = false)
		:_vertexs(vertexs,vertexs+size)
		,_isDirected(isDirected)
	{
		_table.resize(size);
	}
	GraphLink(bool isDirected)
		:_isDirected(isDirected)
	{}
public:
	void AddEdge(const V& src,const V& dst,const W& w)
	{
		size_t newsrc = _GetIndex(src);
		size_t newdst = _GetIndex(dst);

		if(_isDirected)
			_AddEdge(newsrc,newdst,w);
		else
		{
			_AddEdge(newsrc,newdst,w);
			_AddEdge(newdst,newsrc,w);
		}
	}
	void Display()
	{
		for(size_t i = 0;i < _vertexs.size();++i)
		{
			cout<<_vertexs[i]<<"["<<i<<"]->";
			Node* cur = _table[i];
			while(cur)
			{
				cout<<cur->_w<<"["<<cur->_dst<<"]->";
				cur = cur->_next;
			}
			cout<<"NULL"<<endl;
		}
	}
	//克鲁斯卡尔算法
	bool Kruskal(GraphLink<V,W>& mintree)
	{
		assert(_isDirected == false);
		mintree._vertexs = _vertexs;
		mintree._isDirected = _isDirected;
		mintree._table.resize(_vertexs.size());

		//仿函数，用权值来对堆进行建小堆
		struct Compare
		{
			bool operator()(Node* L,Node* R)
			{
				return L->_w < R->_w;
			}
		};

		Heap<Node*,Compare> minheap;
		for (size_t i = 0;i < _table.size();i++)
		{
			Node* cur = _table[i];
			while (cur)
			{
				//对无向图进行过滤，不让相同的边重复进入
				if (cur->_src < cur->_dst)
				{
					minheap.Push(cur);
				}
				
				cur = cur->_next;
			}
		}

		size_t n = 0;
		//使用并查集高效的判断是否成环
		UnionSet ufs(_vertexs.size());

		while (n < (_vertexs.size() - 1))
		{
			if(minheap.Empty())
				return false;

			Node* edge = minheap.Top();
			minheap.Pop();

			int root1 = ufs.FindRoot(edge->_src);
			int root2 = ufs.FindRoot(edge->_dst);

			if (root1 != root2)
			{
				ufs.UnionSetFrient(root1,root2);
				mintree._AddEdge(edge->_src,edge->_dst,edge->_w);
				++n;
			}
		}
		//打印最小生成树的顶点之间的边
		mintree._KruskalDisplay();
		return true;
	}
private:
	void _KruskalDisplay()
	{
		for (size_t i = 0;i < _table.size();++i)
		{
			Node* cur = _table[i];

			while (cur)
			{
				cout<<cur->_src<<"--"<<cur->_dst<<",";
				cur = cur->_next;
			}
		}
	}
	void _AddEdge(size_t src,size_t dst,const W& w)
	{
		Node* tmp = new Node(src,dst,w);

		tmp->_next = _table[src];
		_table[src] = tmp;
	}
	size_t _GetIndex(const V& v)
	{
		for(size_t i = 0;i < _vertexs.size();++i)
			if(_vertexs[i] == v)
				return i;

		assert(false);
	}
private:
	vector<V> _vertexs;
	vector<Node*> _table;
	bool _isDirected;
};

void test()
{
	string arr[] = {"A","B","C","D","E"};
	int size = sizeof(arr)/sizeof(arr[0]);

	GraphLink<string,int> gl(arr,size);
	gl.AddEdge("A","D",10);
	gl.AddEdge("D","B",20);
	gl.AddEdge("B","C",10);
	gl.AddEdge("C","E",40);
	gl.AddEdge("E","B",30);
	gl.AddEdge("E","A",20);
	gl.Display();

	GraphLink<string,int> g2(false);
	//最小生成树
	gl.Kruskal(g2);
}

int main()
{
	test();
	system("pause");
	return 0;
}