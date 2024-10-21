#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

// 信号量集合的下标
#define SEM_MUTEX 0   // 互斥锁
#define SEM_EMPTY 1   // 空位信号量
#define SEM_FULL  2   // 资源信号量

// 共享仓库的路径
#define STORE_PATH "./store"
#define STORE_CAPACITY 100

// 初始化信号量集
int init_semaphores(key_t key);

// P操作：信号量-1
void semaphore_p(int sem_id, int sem_num);

// V操作：信号量+1
void semaphore_v(int sem_id, int sem_num);

#endif

