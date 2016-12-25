#pragma once
#include <string>

typedef long long INT64;
#define UN_INT64 0xCCCCCCCCCCCCCCCC
#define MAX_INT64 0x7FFFFFFFFFFFFFFF
#define MIN_INT64 0x8000000000000000

class BigData
{
public:
	BigData(const INT64 value);
	BigData(const char* str);
	BigData operator+(const BigData& bigData);
	BigData operator-(const BigData& bigData);
	BigData operator*(const BigData& bigData);
	friend std::ostream& operator<<(std::ostream& _cout,const BigData& bigData);

private:
	std::string _Add(std::string left,std::string right);
	std::string _Sub(std::string left,std::string right);
	std::string _Mul(std::string left,std::string right);	
	bool _IsINT64OverFlow()const;
	int _Compare(std::string left,std::string right);
private:
	INT64 _value;
	std::string _strData;
};