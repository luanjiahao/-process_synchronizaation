#include "semaphore.h"

// 初始化信号量
int init_semaphores(key_t key) {
    int sem_id = semget(key, 3, IPC_CREAT | 0666);
    if (sem_id == -1) {
        perror("semget");
        exit(1);
    }

    // 初始化互斥信号量为1（互斥锁）
    semctl(sem_id, SEM_MUTEX, SETVAL, 1);
    // 初始化空位信号量为STORE_CAPACITY
    semctl(sem_id, SEM_EMPTY, SETVAL, STORE_CAPACITY);
    // 初始化资源信号量为0
    semctl(sem_id, SEM_FULL, SETVAL, 0);

    return sem_id;
}

// P操作：信号量-1
void semaphore_p(int sem_id, int sem_num) {
    struct sembuf sb = {sem_num, -1, 0};
    semop(sem_id, &sb, 1);
}

// V操作：信号量+1
void semaphore_v(int sem_id, int sem_num) {
    struct sembuf sb = {sem_num, 1, 0};
    semop(sem_id, &sb, 1);
}

