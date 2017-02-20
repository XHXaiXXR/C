#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<pthread.h>
typedef struct _node
{
	int data;
	struct n_ode *next;
}node_t, *node_p, **node_pp;

pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;//初始化锁
pthread_cond_t mycond = PTHREAD_COND_INITIALIZER;//初始化

node_p AllocNode(int data)
{
	node_p node = (node_p)malloc(sizeof(node_t));
	if(NULL == node)
	{
		perror("malloc");
		return NULL;
	}

	node->data = data;
	node->next = NULL;

	return node;
}

void InitList(node_pp _h)
{
	*_h = AllocNode(0);
}

void PushFrond(node_p list,int data)
{
	assert(list);

	node_p new_node = AllocNode(data);
	new_node->next = list->next;
	list->next = new_node;
}

int IsEmpty(node_p list)
{
	if( NULL == list->next)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void DelNode(node_p node)
{
	assert(node);
	free(node);
}

void PopFrond(node_p list,int* data)
{
	assert(list);
	assert(data);

	if( IsEmpty(list) )
	{
		printf("list is empty...\n");
		return ;
	}
	
	node_p delnode = list->next;
	list->next = delnode->next;
	*data = delnode->data;

	DelNode(delnode);
}

void DestroyList(node_p list)
{
	assert(list);
	
	int data = 0;
	while( !IsEmpty(list))
	{
		PopFrond(list,&data);			
	}

	DelNode(list);
}

void ShowList(node_p list)
{
	node_p node = list->next;
	while(node)
	{
		printf("%d ",node->data);
		node = node->next;
	}

	printf("\n");
}


void* thread_product(void* arg)
{
	node_p head = (node_p)arg;

	while(1)
	{
		usleep(123456);

		pthread_mutex_lock(&mylock);

		int data = rand()%10000;
		PushFrond(head,data);
		printf("product done,data is : %d\n",data);
	
		pthread_mutex_unlock(&mylock);

		//生产出一个产品以后，唤醒一个消费者,通知消费者来取产品
		pthread_cond_signal(&mycond);//signal(唤醒一个)，broadcast(唤醒多个)
	}
}

void* thread_consumer(void* arg)
{
	node_p node = (node_p)arg;
	int data = 0;

	while(1)
	{
		pthread_mutex_lock(&mylock);
		
		if(IsEmpty(node))
		{
			//如果链表为空的话，那么等待生产者至少生产一个产品的时候，才去取产品
			pthread_cond_wait(&mycond, &mylock);
		}

		PopFrond(node,&data);
		printf("consumer done,data is : %d\n",data);
		
		pthread_mutex_unlock(&mylock);
	}
}

int main()
{
	//用链表充当中间场所
	node_p head = NULL;
	InitList(&head);
	
	//线程ID
	pthread_t tid1;
	pthread_t tid2;

	//创建线程
	int ret1 = pthread_create(&tid1, NULL, thread_product, (void*)head);//创建生产者线程
	int ret2 = pthread_create(&tid2, NULL, thread_consumer, (void*)head);//创建消费者线程
	
	if(ret1 < 0 || ret2 < 0)
	{
		perror("pthread_create");
		return -1;
	}

	//等待线程
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	DestroyList(head);
	pthread_mutex_destroy(&mylock);
	pthread_cond_destroy(&mycond);
	
	
	//node_p head = NULL;
	//InitList(&head);

	//int i = 0;
	//for( ; i < 10; ++i)
	//{
	//	PushFrond(head, i);
	//	ShowList(head);
	//	sleep(1);
	//}

	//int data = 0;
	//for( ; i >= 5; --i)
	//{
	//	PopFrond(head, &data);
	//	ShowList(head);
	//	sleep(1);
	//}

	//DestroyList(head);
	//ShowList(head);

	return 0;
}
