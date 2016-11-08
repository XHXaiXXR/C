#include <iostream>
using namespace std;
#include "BloomFilter.h"
#include <string>

void test()
{
	char* str1 = "1ile:///C:/Users/xjh/AppData/Local/Temp/360zip$Temp/360$0/%E5%AD%97%E7%AC%A6%E4%B8%B2%E5%93%88%E5%B8%8C%E7%AE%97%E6%B3%95/%E5%90%84%E7%A7%8D%E5%AD%97%E7%AC%A6%E4%B8%B2Hash%E5%87%BD%E6%95%B0%20-%20clq%20-%20%E5%8D%9A%E5%AE%A2%E5%9B%AD.html";
	char* str2 = "2ile:///C:/Users/xjh/AppData/Local/Temp/360zip$Temp/360$0/%E5%AD%97%E7%AC%A6%E4%B8%B2%E5%93%88%E5%B8%8C%E7%AE%97%E6%B3%95/%E5%90%84%E7%A7%8D%E5%AD%97%E7%AC%A6%E4%B8%B2Hash%E5%87%BD%E6%95%B0%20-%20clq%20-%20%E5%8D%9A%E5%AE%A2%E5%9B%AD.html";
	char* str3 = "3ile:///C:/Users/xjh/AppData/Local/Temp/360zip$Temp/360$0/%E5%AD%97%E7%AC%A6%E4%B8%B2%E5%93%88%E5%B8%8C%E7%AE%97%E6%B3%95/%E5%90%84%E7%A7%8D%E5%AD%97%E7%AC%A6%E4%B8%B2Hash%E5%87%BD%E6%95%B0%20-%20clq%20-%20%E5%8D%9A%E5%AE%A2%E5%9B%AD.html";
	char* str4 = "4ile:///C:/Users/xjh/AppData/Local/Temp/360zip$Temp/360$0/%E5%AD%97%E7%AC%A6%E4%B8%B2%E5%93%88%E5%B8%8C%E7%AE%97%E6%B3%95/%E5%90%84%E7%A7%8D%E5%AD%97%E7%AC%A6%E4%B8%B2Hash%E5%87%BD%E6%95%B0%20-%20clq%20-%20%E5%8D%9A%E5%AE%A2%E5%9B%AD.html";

	BloomFiter<> bf(5);
	bf.SetBloom(str1);
	bf.SetBloom(str2);
	bf.SetBloom(str3);
	cout<<bf.TestBloom(str1)<<endl;
	cout<<bf.TestBloom(str2)<<endl;
	cout<<bf.TestBloom(str3)<<endl;
	cout<<bf.TestBloom(str4)<<endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}