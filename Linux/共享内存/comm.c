#include"comm.h"

static int CommShm(int flg)
{
	key_t _k = ftok(PATHNAME, PROJID);
	if(_k < 0)
	{
		perror("ftok");
		return -1;
	}

	int shm_id = shmget(_k, SIZE, flg);
	if(shm_id < 0)
	{
		perror("shmget");
		return -2;
	}

	return shm_id;
}

//创建共享内存
int CreateShm()
{
	return CommShm(IPC_CREAT | IPC_EXCL | 0666);
}
//获取共享内存
int GetShm()
{
	return CommShm(IPC_CREAT);
}
//将共享内存挂接到指定内存
void* AtShm(int shm_id)
{
	return shmat(shm_id, NULL, 0);
}
//去关联
int DtShm(const void* shmaddr)
{
	return shmdt(shmaddr);
}
//销毁共享内存
int DestoryShm(int shm_id)
{
	int ret = shmctl(shm_id, IPC_RMID, NULL);
	if(ret < 0)
	{
		perror("shmctl");
		return -3;
	}

	return 0;
}
