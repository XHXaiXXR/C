#include"comm.h"

static int CommSemSet(int nums, int flag)//static使函数不暴露给外面
{
	key_t _k = ftok(PATHNAME,PROJID);
	if(_k < 0)
	{
		perror("ftok");
		return -1;
	}
	
	int sem_id = semget(_k, nums, flag);
	if(sem_id < 0)
	{
		perror("semget");
		return -2;
	}

	return sem_id;
}

//创建信号量集
int CreateSemSet(int nums)
{
	return CommSemSet(nums, IPC_CREAT | IPC_EXCL | 0666);
}

//初始化信号量集
int InitSemSet(int sem_id, int which)
{
	union semun un;
	un.val = 1;
	int ret = semctl(sem_id, which, SETVAL, un);//设置初始值
	if(ret < 0)
	{
		perror("semctl");
		return -5;
	}

	return 0;
}

//获取信号量集
int GetSemSet()
{
	return CommSemSet(0, IPC_CREAT);//参数也可以是（0，0）
}

static int SemOp(int sem_id,int which,int op)
{
	struct sembuf s;//库中已经有sembuf了，我们直接用就可以了
	s.sem_num = which;//对哪一个信号量（编号）进行操作
	s.sem_op = op;//进行什么操作（P（-1）或V（+1）操作）
	s.sem_flg = 0;//???
	
	int ret = semop(sem_id, &s,1);//第三个参数为操作信号量集中的个数
	if(ret < 0)
	{
		perror("semop");
		return -4;
	}
	
	return 0;
}

//P操作
int P(int sem_id, int which)
{
	return SemOp(sem_id, which, -1);//P操作-1
}

//V操作
int V(int sem_id, int which)
{
	return SemOp(sem_id, which, 1);//V操作+1
}

//销毁信号量集
int DestorySemSet(int sem_id)
{
	int ret = semctl(sem_id, 0, IPC_RMID);//由于我这里写的信号量集里面只有一个信号量，信号量集就像是数组一样，都是从0开始编号的。第二个参数是删除信号量集的编号，故这里写0
	if(ret < 0)
	{
		perror("semctl");
		return -3;
	}

	return 0;
}























