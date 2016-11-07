#include<iostream>
using namespace std;
#include"bitset.h"

void test()
{
	BitMap bm(400);
	bm.Set(2);
	bm.Set(22);
	bm.Set(222);
	
	cout<<"set(2) set(22) set(222)"<<endl;
	cout<<"set(2) ? "<<bm.Test(2)<<endl;
	cout<<"set(22) ? "<<bm.Test(22)<<endl;
	cout<<"set(222) ? "<<bm.Test(222)<<endl;
	cout<<"set(3) ? "<<bm.Test(3)<<endl;

	bm.Reset(22);
	cout<<endl<<"reset(22)"<<endl;
	cout<<"set(2) ? "<<bm.Test(2)<<endl;
	cout<<"set(22) ? "<<bm.Test(22)<<endl;
	cout<<"set(222) ? "<<bm.Test(222)<<endl;
	cout<<"set(3) ? "<<bm.Test(3)<<endl;
}
int main()
{
	test();
	return 0;
}