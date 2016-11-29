#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<assert.h>

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
private:
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
	gl.AddEdge("A","E",20);
	gl.AddEdge("B","C",10);
	gl.AddEdge("B","D",20);
	gl.AddEdge("B","E",30);
	gl.AddEdge("C","E",40);

	gl.Display();
}

int main()
{
	test();
	system("pause");
	return 0;
}