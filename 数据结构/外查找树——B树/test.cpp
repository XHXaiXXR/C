#include<iostream>
using namespace std;
#include <utility>

//template<class K,class V>
//struct Pair
//{
//	K first;
//	V second;
//};

template<class K,int M>
struct BTreeNode
{
	K _keys[M];                   //�ؼ�������
	BTreeNode<K,M>* _subs[M+1];   //���ӽڵ��ָ������

	BTreeNode<K,M>* _parent;      
	size_t _size;                  //�ؼ��ֵĸ���

	BTreeNode()
		:_parent(NULL)
		,_size(0)
	{
		for(int i = 0;i < M;i++)
		{
			_keys[i] = 0;
			_subs[i] = NULL;
		}
		_subs[M] = NULL;
	}
};

template<class K,int M>
class BTree
{
	typedef BTreeNode<K,M> Node;
public:
	BTree()
		:_root(NULL)
	{}

	pair<Node*,int> Find(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;
	
		while(cur)
		{
			size_t i = 0;
			while(i < cur->_size)
			{
				if(cur->_keys[i] < key)
					++i;
				else if(cur->_keys[i] > key)
					break;
				else
					return pair<Node*,int>(cur,i);
			}
			parent = cur;
			cur = cur->_subs[i];
		}
	
		return pair<Node*,int>(parent,-1);
	}
	
	bool Insert(const K& key)
	{
		if(_root == NULL)
		{
			_root = new Node;
			_root->_keys[0] = key;
			_root->_size = 1;
			return true;
		}

		pair<Node*,int> ret = Find(key);
		//���keyֵ���ڣ��򲻽��в���
		if(ret.second != -1)
			return false;

		//�����ڣ����в���
		Node* cur = ret.first;
		Node* sub = NULL;
		K newkey = key;

		while(1)
		{
			_InsertKey(cur,newkey,sub);

			//����ɹ��Ҳ���Ҫ����
			if(cur->_size < M)
				return true;

			//����
			size_t mid = cur->_size/2;
			Node* righttmp = new Node;//�´���һ���½ڵ㣬���ڴ���Ұ�����
			size_t j = 0;

			//�Ұ������keyֵ����
			for(size_t i = mid+1;i < cur->_size;i++)
			{
				righttmp->_keys[j] = cur->_keys[i];
				righttmp->_size++;
				cur->_keys[i] = K();
				j++;
			}
			//�Ұ������subsֵ����
			j = 0;
			for(size_t i = mid+1;i < cur->_size+1;i++)
			{
				righttmp->_subs[j] = cur->_subs[i];
				if(righttmp->_subs[j])
					righttmp->_subs[j]->_parent = righttmp;
				++j;
				cur->_subs[i] = NULL;
			}

			//�������Ĺؼ�����Ŀ�����ı�
			cur->_size -= (1 + righttmp->_size);

			if(cur->_parent == NULL)
			{
				_root = new Node;
				_root->_keys[0] = cur->_keys[mid];
				_root->_size++;

				_root->_subs[0] = cur;
				cur->_parent = _root;
				_root->_subs[1] = righttmp;
				righttmp->_parent = _root;

				cur->_keys[mid] = K();

				return true;
			}
			else
			{
				newkey = cur->_keys[mid];
				cur->_keys[mid] = K();

				cur = cur->_parent;
				sub = righttmp;
			}
		}
	}
protected:
	void _InsertKey(Node* cur,int key,Node* sub)
	{
		int i = cur->_size - 1;

		while(i >= 0)
		{
			if(cur->_keys[i] < key)
				break;
			else
			{
				cur->_keys[i+1] = cur->_keys[i];
				cur->_subs[i+2] = cur->_subs[i+1];
			}
			--i;
		}

		cur->_keys[i+1] = key;
		cur->_subs[i+2] = sub;
		if(sub)
			sub->_parent = cur;

		cur->_size++;
	}
private:
	Node* _root;
};

void test()
{
	int arr[] = {53, 75, 139, 49, 145, 36, 101};	int size = sizeof(arr)/sizeof(arr[0]);

	BTree<int,3> bt;
	for (int i = 0;i < size;i++)
	{
		bt.Insert(arr[i]);
	}
}

int main()
{
	test();
	system("pause");
	return 0;
}