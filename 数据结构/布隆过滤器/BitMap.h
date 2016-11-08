#pragma once
#include<vector>

class BitMap
{
public:
	//range 范围
	BitMap(size_t range)
	{
		//size_t有四个字节，每个字节有八个位
		//右移5相当于除以32
		_bitmap.resize((range>>5) + 1);
	}

	void Set(size_t x)//0->1
	{
		//先求出在第几个数上
		size_t index = x/32;//相当于x>>5

		//在求出在第几个位上
		size_t num = x%32;

		_bitmap[index] |= (1<<num);
	}

	void Reset(size_t x)//1->0
	{
		size_t index = x/32;
		size_t num = x%32;

		_bitmap[index] &= (~(1<< num));
	}

	bool Test(size_t x)//x存在与否
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