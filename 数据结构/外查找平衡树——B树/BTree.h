#pragma once

template<class K,int M>
struct BTreeNode
{
	K _key[M];//�����һ��λ����Ϊ�˷��㴦�����
	BTreeNode<K,M>* _subs[M+1];//�����һ��λ����Ϊ�˷��㴦�����
	BTreeNode<K,M>* _parent;
	size_t _size;//���˼����ؼ���

	//���캯��
	BTreeNode()
		:_parent(NULL)
		,_size(0)
	{
		for (size_t i = 0;i < M;i++)
		{
			_key[i] = K();
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
	BTree()//���캯��
		:_root(NULL)
	{}
	pair<Node*,int> Find(const K& key)
	{
		Node* parent = NULL;
		Node* cur = _root;

		while (cur)
		{
			size_t i = 0;
			for (i = 0;i < cur->_size;)
			{
				if (cur->_key[i] == key)
				{
					return pair<Node*,int>(cur,i);
				} 
				else if (cur->_key[i] > key)
				{
					break;
				}
				else
				{
					i++;
				}
			}
			parent = cur;
			cur = cur->_subs[i];
		}
		return pair<Node*,int>(parent,-1);//_root == NULL ������·���
		                                  //�Ҳ���������·���
	}
	bool Insert(const K& key)
	{
		//��һ�����ݲ�������
		if (_root == NULL)
		{
			_root = new Node;
			_root->_key[0] = key;
			_root->_size = 1;
			return true;
		}

		pair<Node*,int> ret = Find(key);
		if (ret.second != -1)
		{
			//����keyֵ�Ѿ����ڣ���������룬���󷵻�
			return false;
		}

		Node* cur = ret.first;
		K newkey = key;
		Node* sub = NULL;
		while (1)
		{
			InsertKey(cur,newkey,sub);
			if (cur->_size < M)
			{
				return true;
			}
			//����
			int div = M / 2;
			Node* tmp = new Node;//�ȴ���һ���µĽ��
			int index = 0;
			size_t i = 0;
			for (i = div + 1;i <cur->_size;i++)
			{
				//�����Ұ���������ݵ��½��
				tmp->_key[index++] = cur->_key[i];
				tmp->_size++;
				cur->_key[i] = K();
			}
			index = 0;
			for (i = div+1;i<cur->_size;i++)
			{
				//�����Ұ�����ĺ��ӽ�㵽�½��
				tmp->_subs[index++] = cur->_subs[i];
				if (cur->_subs[i])
				{
					cur->_subs[i]->_parent = tmp;
				}
			}

			cur->_size = cur->_size - tmp->_size - 1;//��λ��������
			if (cur->_parent == NULL)
			{
				_root = new Node;

				_root->_key[0] = cur->_key[div];
				cur->_key[div] = K();
				
				_root->_subs[0] = cur;
				cur->_parent = _root;
				_root->_subs[1] = tmp;
				tmp->_parent = _root;
				
				_root->_size = 1;
				
				return true;
			}
			else
			{
				newkey = cur->_key[div];
				cur->_key[div] = K();
				cur = cur->_parent;
				sub = tmp;
			}
		}
		return true;//ֻҪ������while��1������ѭ������һ���з���ֵ���ˣ�
		            //����ķ���ֵ��û�������
	}
	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
private:
	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		size_t i = 0;
		for (i = 0;i < root->_size;i++)
		{
			_InOrder(root->_subs[i]);
			cout<<root->_key[i]<<" ";
		}
		_InOrder(root->_subs[i]);
	}
	void InsertKey(Node* cur,const K& key,Node* sub)
	{
		int end = cur->_size-1;//��endָ�����ݵ����һ��λ��
		while (end >= 0)
		{
			if (cur->_key[end] > key)
			{
				cur->_key[end+1] = cur->_key[end];
				cur->_subs[end+2] = cur->_subs[end+1];
				end--;
			}
			else
			{
				//end->_key < key
				break;
			}
		}
		cur->_key[end+1] = key;
		cur->_subs[end+2] = sub;
		if (sub)
		{
			//������Ӵ���
			sub->_parent = cur;
		}
		cur->_size++;
	}
protected:
	Node* _root;
};