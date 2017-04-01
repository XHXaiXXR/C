#pragma once

template<class K, int M>
struct BTreeNode
{
	K _key[M];//�ؼ��֣��ؼ������M-1�������￪��M���ռ���Ϊ�˷��ѷ���
	BTreeNode<K, M>* _sub[M+1];//���ӣ��������M����ͬ����Ϊ�˷��ѷ���࿪����һ���ռ�
	BTreeNode<K, M>* _parent;//���ڼ�¼���ӷ����Ժ��ָ��
	size_t _size;//�ؼ��ֵĸ���

	BTreeNode()
		:_parent(NULL)
		,_size(0)
	{
		for (size_t i = 0;i < M;i++)
		{
			_key[i] = K();
			_sub[i] = NULL;
		}
		_sub[M] = NULL;
	}
};

template<class K, int M>
class BTree
{
	typedef BTreeNode<K, M> Node;
public:
	BTree()
		:_root(NULL)
	{}
	pair<Node*, int> Find(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;

		while (cur)
		{
			size_t i = 0;
			for (i = 0;i < cur->_size;)
			{
				if (cur->_key[i] == key)
				{
					return pair<Node*, int>(cur, i);
				}
				else if (cur->_key[i] < key)
				{
					++i;
				}
				else//cur->_key > key
				{
					break;
				}
			}
			parent = cur;
			cur = cur->_sub[i];
		}

		return pair<Node*, int>(parent, -1);
	}
	bool Insert(const K& key)
	{
		if (_root == NULL)
		{
			_root = new Node;
			_root->_key[0] = key;
			_root->_size = 1;
			return true;
		}

		pair<Node*, int> ret = Find(key);
		if (ret.second != -1)
		{
			//�Ѿ����ڣ��ǾͲ���Ҫ������
			return false;
		}

		Node* cur = ret.first;
		K newkey = key;
		Node* sub = NULL;

		while (1)
		{
			_InsertKey(cur, sub, newkey);

			if (cur->_size < M)
			{
				//�ɹ����벢�Ҳ���Ҫ���ѣ���ô�ɹ�����
				return true;
			}

			//B���йؼ������ֻ����M-1�����ߵ�����˵����ʱcur�Ĺؼ����Ѿ���M���ˣ���ʱ����Ҫ����
			int div = M / 2;//���м�ֵ���±�
			Node* tmp = new Node;//���ڴ�ŷ��ѵ��Ұ�����
			int index = 0;
			size_t i= 0;
			for (i = div + 1;i < cur->_size;i++)
			{
				//�����Ұ�����Ĺؼ���
				tmp->_key[index++] = cur->_key[i];
				cur->_key[i] = K();
				tmp->_size++;
			}
			index = 0;
			for (i = div + 1;i <= cur->_size;i++)
			{
				//�����Ұ�����ĺ���
				tmp->_sub[index++] = cur->_sub[i];
				if (cur->_sub[i])
				{
					cur->_sub[i]->_parent = tmp;
				}
			}

			cur->_size = cur->_size - tmp->_size - 1;//����cur�ؼ��ֵ�����������ؼ��ֵ���ֵ�����һ����һ��Ϊ�˽��м���������ȡ

			if (cur->_parent == NULL)
			{
				//˵���Ѿ��������˸��ڵ�
				_root = new Node;
				_root->_key[0] = cur->_key[div];
				cur->_key[div] = K();

				_root->_sub[0] = cur;
				cur->_parent = _root;
				_root->_sub[1] = tmp;
				tmp->_parent = _root;

				_root->_size = 1;

				return true;
			} 
			else
			{
				newkey = cur->_key[div];
				cur->_key[div] = K();
				cur = cur->_parent;//���ϵ���
				sub = tmp;
			}
		}

		return true;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
protected:
	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}

		int i = 0;
		for (i = 0;i < root->_size;i++)
		{
			_InOrder(root->_sub[i]);
			cout<<root->_key[i]<<" ";
		}
		_InOrder(root->_sub[i]);
	}
	void _InsertKey(Node* cur, Node* sub, const K& key)
	{
		//����ֻ�����봦���������Ƿ���Ҫ���ѵ����

		int end = cur->_size - 1;//�ҵ����һ���ؼ���
		
		while (end >= 0 && cur->_key[end] > key)
		{
			cur->_key[end + 1] = cur->_key[end];
			cur->_sub[end + 2] = cur->_sub[end + 1];
			end--;
		}
		cur->_key[end + 1] = key;
		cur->_sub[end + 2] = sub;
		if (sub)
		{
			sub->_parent = cur;
		}

		//���һ��Ҫ�ǵùؼ��ֵ���ֵ��һ
		cur->_size++;
	}
private:
	Node* _root;
};

void test()
{   
	BTree<int,3> bt;  
	int arr[] = {53,75,139,49,145,36,101};  
	int size = sizeof(arr)/sizeof(arr[0]);  
	for (size_t i = 0;i < size;i++)  
	{  
		bt.Insert(arr[i]);  
	}  
	bt.InOrder();  
}