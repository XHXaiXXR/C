#define _CRT_SECURE_NO_WARNINGS 1
#include "LRUCache.h"

void Test()
{
	LRUCache<int, char> lru(10);
	lru.LRUCacheSet(1,'a');
	lru.LRUCacheSet(2, 'b');	
	lru.LRUCacheSet(3, 'c');
	lru.LRUCacheSet(4, 'd');
	lru.LRUCacheSet(5, 'e');
	lru.LRUCacheSet(6, 'f');
	lru.LRUCacheSet(7, 'g');
	//访问已经存在的缓存
	lru.LRUCacheSet(3, 'c');
	lru.LRUCacheSet(4, 'd');
	//测试哈希拉链法
	lru.LRUCacheSet(16, 't');
	//将哈希表的其他位置存满
	lru.LRUCacheSet(10, 'w');
	lru.LRUCacheSet(8, 'o');
	//哈希表已经满了，需要删除最早缓存进来的缓存单元，新插入最新加入的缓存单元
	lru.LRUCacheSet(9, 'p');

	char c = 0;

	cout << lru.LRUCacheGet(3,c) << endl;
	cout<<"c = "<<c<<endl;
	cout << lru.LRUCacheGet(2,c) << endl;
	cout<<"c = "<<c<<endl;
	cout << lru.LRUCacheGet(3,c) << endl;
	cout<<"c = "<<c<<endl;
	cout << lru.LRUCacheGet(1,c) << endl;
	cout<<"c = "<<c<<endl;
	cout << lru.LRUCacheGet(8,c) << endl;
	cout<<"c = "<<c<<endl;
	cout<<lru.LRUCacheGet(6,c) <<endl;
	cout<<"c = "<<c<<endl;

}

int main()
{
	Test();
	system("pause");
	return 0;
}