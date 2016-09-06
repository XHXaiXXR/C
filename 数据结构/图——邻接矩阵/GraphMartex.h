#pragma once
#include <assert.h>

template<class V,class W>
class GraphMartex//�ٽӾ���
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

		//��ʼ������
		for (int k = 0;k < _size;k++)
		{
			for (int z = 0;z < _size;z++)
			{
				_martex[k][z] = 0;
			}
		}
	}
	//�ٽӾ��������Ȩֵ
	void AddEdge(const V& src,const W& dect,const W& w)
	{
		size_t newstr = GetIndex(src);
		size_t newdect = GetIndex(dect);

		assert(newstr != -1);
		assert(newdect != -1);

		if (_isDirection)
		{
			//����ͼ   ��Ӷ�ӦA->B��һ���ߵ�Ȩ��
			_martex[newstr][newdect] = w;
		} 
		else
		{
			//����ͼ   ���A->B��B->A�����ߵ�Ȩ��
			_martex[newstr][newdect] = w;
			_martex[newdect][newstr] = w;
		}
	}
	//��ӡͼ
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
				//���ض�Ӧ�ĵ�ǰ���±�
				return i;
			}
		}
		//�Ҳ�������һ���Ƿ�ֵ
		return -1;
	}
private:
	V* _vertexs;//���㼯��
	W** _martex;//�߼���
	size_t _size;//�������
	bool _isDirection;//�ж��Ƿ�Ϊ����ͼ
};