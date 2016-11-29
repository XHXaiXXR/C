#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<assert.h>
#include<queue>

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
	//深度优先遍历
	void DFS(const V& v)
	{
		vector<bool> visited(_vertexs.size(),false);

		_DFS(_GetIndex(v),visited);

		cout<<"NULL"<<endl;
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
	//广度优先遍历
	void BFS(const V& v)
	{
		size_t index = _GetIndex(v);
		vector<bool> visited(_vertexs.size(),false);
		queue<size_t> q;
		q.push(index);

		while(!q.empty())
		{
			size_t front = q.front();
			q.pop();

			if(visited[front] == false)
			{
				cout<<_vertexs[front]<<"["<<front<<"]->";
				visited[front] = true;
			}

			Node* cur = _table[front];
			while(cur)
			{
				if(visited[cur->_dst] == false)
					q.push(cur->_dst);

				cur = cur->_next;
			}
		}
		cout<<"NULL"<<endl;
	}
private:
	void _DFS(size_t src,vector<bool>& visited)
	{
		cout<<_vertexs[src]<<"["<<src<<"]->";
		visited[src] = true;
		Node* cur = _table[src];

		while(cur)
		{
			if(visited[cur->_dst] == false)
				_DFS(cur->_dst,visited);

			cur = cur->_next;
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
	gl.AddEdge("A","E",20);
	gl.AddEdge("B","C",10);
	gl.AddEdge("B","D",20);
	gl.AddEdge("B","E",30);
	gl.AddEdge("C","E",40);

	gl.Display();

	//深度优先遍历
	gl.DFS("A");
	//广度优先遍历
	gl.BFS("A");
}

int main()
{
	test();
	system("pause");
	return 0;
}