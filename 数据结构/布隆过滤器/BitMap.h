#pragma once
#include<vector>

class BitMap
{
public:
	//range ��Χ
	BitMap(size_t range)
	{
		//size_t���ĸ��ֽڣ�ÿ���ֽ��а˸�λ
		//����5�൱�ڳ���32
		_bitmap.resize((range>>5) + 1);
	}

	void Set(size_t x)//0->1
	{
		//������ڵڼ�������
		size_t index = x/32;//�൱��x>>5

		//������ڵڼ���λ��
		size_t num = x%32;

		_bitmap[index] |= (1<<num);
	}

	void Reset(size_t x)//1->0
	{
		size_t index = x/32;
		size_t num = x%32;

		_bitmap[index] &= (~(1<< num));
	}

	bool Test(size_t x)//x�������
	{
		size_t index = x/32;
		size_t num = x%32;

		int ret = _bitmap[index] & (1<<num);

		if (ret)
		{
			return true;
		}
		else
			return false;
	}
private:
	vector<size_t> _bitmap;	
};