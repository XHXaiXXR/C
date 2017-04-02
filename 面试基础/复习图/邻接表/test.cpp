#include <iostream>
using namespace std;

#include <vector>

template<class V ,class W>
struct GraphLinkNode
{
	size_t _src;
	size_t _dect;
	W _w;
	GraphLinkNode<V, W>* _next;

	GraphLinkNode(size_t src, size_t dect, const W& w)
		:_src(src)
		,_dect(dect)
		,_w(w)
		,_next(NULL)
	{}
};

template<class V, class W>
class GraphLink
{
public:
	GraphLink(){}
	GraphLink(const V* arr, size_t size, bool isDirection)
		:_isDirection(isDirection)
	{
		_v.resize(size);
		_egdes.resize(size);

		for (size_t i = 0;i < size;++i)
		{
			_v[i] = arr[i];
		}
	}

	void AddEdge(const V& src,const V& dect,const W& w)
	{
		int newsrc = _GetIndex(src);
		int newdect = _GetIndex(dect);

		if (_isDirection == true)
		{
			_AddEgde(newsrc,newdect,w);
		} 
		else
		{
			_AddEgde(newsrc,newdect,w);
			_AddEgde(newdect,newsrc,w);
		}
	}
	void Display()
	{
		for (size_t i = 0;i < _v.size();++i)
		{
			cout<<_v[i]<<"["<<i<<"]->";
			GraphLinkNode<V,W>* cur = _egdes[i];

			while (cur)
			{
				cout<<cur->_w<<"["<<cur->_dect<<"]->";
				cur = cur->_next;
			}
			cout<<"NULL"<<endl;
		}
	}
protected:
	void _AddEgde(size_t src,size_t dect,const W& w)
	{
		GraphLinkNode<V,W>* tmp = new GraphLinkNode<V, W>(src,dect,w);

		//头插
		tmp->_next = _egdes[src];
		_egdes[src] = tmp;
	}
	int _GetIndex(const V& v)
	{
		for (size_t i = 0;i < _v.size();++i)
		{
			if (_v[i] == v)
			{
				return i;
			}
		}
		return -1;
	}
private:
	vector<V> _v;//顶点集合
	vector<GraphLinkNode<V, W>*> _egdes;//邻接表存储边
	bool _isDirection;
};

void Test1()
{
	GraphLink<char,int> g("ABCDE",5,false);  
	g.AddEdge('B','C',10);  
	g.AddEdge('B','D',20);  
	g.AddEdge('B','E',30);  
	g.AddEdge('C','E',40);  
	g.AddEdge('D','A',10);  
	g.AddEdge('A','E',20);  

	g.Display();  
}

int main()
{
	Test1();
	system("pause");
	return 0;
}