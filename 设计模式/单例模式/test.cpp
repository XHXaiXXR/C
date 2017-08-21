#include<iostream>
using namespace std;
#include<pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
class Mutex
{
public:
	Mutex()
	{
		pthread_mutex_lock(&mutex);
	}
	~Mutex()
	{
		pthread_mutex_unlock(&mutex);
	}
};
class Singleton
{
public:
	static Singleton* GetInstance()
	{
		if(NULL == _instance)
		{
			Mutex mt;
			if(NULL == _instance)
			{
				_instance = new Singleton();
			}
		}
		return _instance;
	}
	static void DeleteInstance()
	{
		if(NULL != _instance)
		{
			delete _instance;
			_instance = NULL;
		}
	}
private:
	Singleton(){}
	Singleton(const Singleton &);
	Singleton& operator=(const Singleton &);

	static Singleton* _instance;
};
Singleton* Singleton::_instance = NULL;

int main()
{
	Singleton* slt1 = Singleton::GetInstance();
	cout<<"slt1 = "<<slt1<<endl;
	Singleton* slt2 = Singleton::GetInstance();
	cout<<"slt2 = "<<slt2<<endl;
	Singleton* slt3 = Singleton::GetInstance();
	cout<<"slt3 = "<<slt3<<endl;
	
	Singleton::DeleteInstance();
	Singleton::DeleteInstance();
	Singleton::DeleteInstance();

	return 0;
}
