#pragma once
#include <string>

typedef long long INT64;
#define UN_INT64 0

class BigData
{
public:
	BigData(const INT64 value);
	BigData(const char* str);

	friend std::ostream& operator<<(std::ostream& _cout,const BigData& bigData);

private:
	bool _IsINT64OverFlow()const;
private:
	INT64 _value;
	std::string _strData;
};