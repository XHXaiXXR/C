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
	//�����Ѿ����ڵĻ���
	lru.LRUCacheSet(3, 'c');
	lru.LRUCacheSet(4, 'd');
	//���Թ�ϣ������
	lru.LRUCacheSet(16, 't');
	//����ϣ�������λ�ô���
	lru.LRUCacheSet(10, 'w');
	lru.LRUCacheSet(8, 'o');
	//��ϣ���Ѿ����ˣ���Ҫɾ�����绺������Ļ��浥Ԫ���²������¼���Ļ��浥Ԫ
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