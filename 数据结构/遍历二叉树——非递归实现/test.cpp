#include<iostream>
using namespace std;
#include<stack>
#include<queue>

template<class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;

	BinaryTreeNode(const T& data = T())
		:_data(data)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(const T* arr,size_t size,const T& invalid)
	{
		size_t index = 0;
		_root = _GreateTree(arr,size,index,invalid);
	}
	~BinaryTree()
	{
		_Destory(_root);
	}
	BinaryTree(const BinaryTree<T>& bt)
	{
		_root = _Copy(bt._root);
	}
	BinaryTree& operator=(const BinaryTree<T>& bt)
	{
		if(this != &bt)
		{
			BinaryTree<T> bt2(bt);
			swap(_root,bt2._root);
		}
		return *this;
	}

	void PrevOrder()
	{
		_PrevOrder(_root);
		cout<<endl;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
	void PostOrder()
	{
		_PostOrder(_root);
		cout<<endl;
	}
	size_t Size()
	{
		size_t count = _Size(_root);
		return count;
	}
	size_t Depth()
	{
		size_t depth = _Depth(_root);
		return depth;
	}
	size_t LeafSize()
	{
		size_t count = _LeafSize(_root);
		return count;
	}
	void PrevOrderNonR()//stack
	{
		stack<Node*> s;
		Node* cur = _root;

		while(cur || !s.empty())
		{
			while(cur)
			{
				cout<<cur->_data<<" ";
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();
			s.pop();
			cur = top->_right;
		}
		cout<<endl;
	}
	void InOrderNonR()//stack
	{
		stack<Node*> s;
		Node* cur = _root;

		while(cur || !s.empty())
		{
			while(cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			
			Node* top = s.top();
			cout<<top->_data<<" ";
			s.pop();
			cur = top->_right;
		}
		cout<<endl;
	}

	void PostOrderNonR()//stack
	{
		stack<Node*> s;
		Node* cur = _root;
		Node* prev = NULL;

		while(cur || !s.empty())
		{
			while(cur)
			{
				s.push(cur);
				cur = cur->_left;
			}

			Node* top = s.top();
			if(top->_right == NULL || top->_right == prev)
			{
				cout<<top->_data<<" ";
				s.pop();
				prev = top;
			}
			else
			{
				cur = top->_right;
			}
		}
		cout<<endl;
	}

	void LayerOrderNonR()//queue
	{
		queue<Node*> q;
		Node* cur = _root;
		if(cur)
		{
			q.push(cur);
		}

		while(!q.empty())
		{
			Node* front = q.front();
			cout<<front->_data<<" ";
			q.pop();

			if(front->_left)
			{
				q.push(front->_left);
			}
			if(front->_right)
			{
				q.push(front->_right);
			}
		}
		cout<<endl;
	}
protected:
	size_t _LeafSize(Node* root)
	{
		size_t count = 0;

		if(root->_left == NULL && root->_right == NULL)
		{
			count++;
			return count;
		}
		if(root->_left)
		{
			count += _LeafSize(root->_left);
		}
		if(root->_right)
		{
			count += _LeafSize(root->_right);
		}
		return count;
	}
	size_t _Depth(Node* root)
	{
		if(root == NULL)
		{
			return 0;
		}

		size_t leftcount = _Depth(root->_left) + 1;
		size_t rightcount = _Depth(root->_right) + 1;

		return leftcount > rightcount ? leftcount : rightcount;
	}
	size_t _Size(Node* root)
	{
		if(root == NULL)
		{
			return 0;
		}
		
		return 1 + _Size(root->_left) + _Size(root->_right);
	}
	Node* _Copy(Node* root)
	{
		if(root == NULL)
		{
			return NULL;
		}
		
		//Node* cur = new Node(root);
		_Copy(root->_left);
		_Copy(root->_right);
		
		return root;
	}
	void _Destory(Node* root)
	{
		if(root == NULL)
		{
			return;
		}

		Node* del = root;
	
		_Destory(root->_left);
		_Destory(root->_right);
		delete del;
	}
	void _PostOrder(Node* root)
	{
		if(root == NULL)
		{
			return;
		}

		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout<<root->_data<<" ";
	}
	void _InOrder(Node* root)
	{
		if(root == NULL)
		{
			return;
		}

		_InOrder(root->_left);
		cout<<root->_data<<" ";
		_InOrder(root->_right);
	}
	void _PrevOrder(Node* root)
	{
		if(root == NULL)
		{
			return;
		}

		cout<<root->_data<<" ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}
	Node* _GreateTree(const T* arr,size_t size,size_t& index,const T& invalid)
	{
		Node* root = NULL;

		if((index < size) && (arr[index] != invalid))
		{
			root = new Node(arr[index]);

			root->_left = _GreateTree(arr,size,++index,invalid);
			root->_right = _GreateTree(arr,size,++index,invalid);
		}

		return root;
	}
private:
	Node* _root;
};
void test()
{
	int arr[10] = {1,2,3,'#','#',4,'#','#',5,6};
	int size = sizeof(arr)/sizeof(arr[0]);

	BinaryTree<int> bt(arr,size,'#');
	bt.PrevOrder();
	bt.PrevOrderNonR();
	bt.InOrder();
	bt.InOrderNonR();
	bt.PostOrder();
	bt.PostOrderNonR();
	bt.LayerOrderNonR();
	cout<<"size: "<<bt.Size()<<endl;
	cout<<"depth: "<<bt.Depth()<<endl;
	cout<<"leafsize: "<<bt.LeafSize()<<endl;

	BinaryTree<int> bt2(bt);
	bt2.PrevOrder();
	bt2.PrevOrderNonR();

	BinaryTree<int> bt3;
	bt3 = bt;
	bt3.PrevOrder();
	bt3.PrevOrderNonR();
}
int main()
{
	test();
	return 0;
}